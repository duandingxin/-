#include "MainWindow.h"

#include "ui_MainWindow.h"
#include "DockWidget/NXDockWidgetTabButton.h"
#include "DockWidget/NXDockWidgetTabBar.h"
#include "DockWidget/NXDockWidget.h"

#include <QHBoxLayout>
#include "DockWidget/NXDockWidget.h"
#include <QTextEdit>
#include <QListWidgetItem>
#include <QListWidget>
#include <QTreeWidget>
#include <QListView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QMdiArea>
#include <QStyleFactory>
#include <QStringListModel>


/**
 * @brief dockAreaToToolBarArea 根据dock的区域位置返回主界面的相对方向
 * @param area
 * @return
 */
static Qt::ToolBarArea dockAreaToToolBarArea(Qt::DockWidgetArea area)
{
    switch(area)
    {
        case Qt::LeftDockWidgetArea: return Qt::LeftToolBarArea;
        case Qt::RightDockWidgetArea: return Qt::RightToolBarArea;
        case Qt::TopDockWidgetArea: return Qt::TopToolBarArea;
        case Qt::BottomDockWidgetArea: return Qt::BottomToolBarArea;
        default:
            return Qt::ToolBarArea(INIT_NUM);
    }
}

MainWindow::MainWindow(QString workspace, QWidget *parent):
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_menuWindows(nullptr)
    , m_dockWidget(nullptr)
    , m_workSpacePath(workspace)
    , m_CentralWidgetId("")
    , m_horstationMax(INIT_HORSTATION)
    , m_verticalMax(INIT_VERTICAL)
{
    ui->setupUi(this);

    GlobalCurveState::getInstance()->releaseGlobalCurveState();

    //初始化窗口
    InitWidget();

    //初始化连接
    InitConnect();

    //默认为全局模式
    slot_AllMode();
}

MainWindow::~MainWindow()
{
    QsLogging::Logger::destroyInstance();
    if(centralWidget_)
    {
        slotActionClearAllWidget();
    }
    if(m_datatreewig)
    {
        delete m_datatreewig;
        m_datatreewig = nullptr;
    }

    if(m_dataTableWig)
    {
        delete m_dataTableWig;
        m_dataTableWig = nullptr;
    }

    if(centralWidget_)
    {
        delete centralWidget_;
        centralWidget_ = nullptr;
    }

    if(stackedWidget_)
    {
        delete stackedWidget_;
        stackedWidget_ = nullptr;
    }

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QsLogging::Logger::destroyInstance();
    if(centralWidget_)
    {
        slotActionClearAllWidget();
    }
    if(m_datatreewig)
    {
        delete m_datatreewig;
        m_datatreewig = nullptr;
    }

    if(m_dataTableWig)
    {
        delete m_dataTableWig;
        m_dataTableWig = nullptr;
    }

    if(centralWidget_)
    {
        delete centralWidget_;
        centralWidget_ = nullptr;
    }

    if(stackedWidget_)
    {
        delete stackedWidget_;
        stackedWidget_ = nullptr;
    }
    return QMainWindow::closeEvent(e);
}

void MainWindow::InitWidget()
{
    // 初始化日志机制
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加QObject为目的地
    QsLogging::DestinationPtr objectDestination(QsLogging::DestinationFactory::MakeFunctorDestination(this, SLOT(slotWriteLog(QString,int))));
    logger.addDestination(objectDestination);

    addToolBarBreak();
    createDockWidgetBar(Qt::LeftDockWidgetArea);
    createDockWidgetBar(Qt::RightDockWidgetArea);
    createDockWidgetBar(Qt::TopDockWidgetArea);
    createDockWidgetBar(Qt::BottomDockWidgetArea);

    //by lk start
    ui->toolBar->insertAction(ui->action_AllMode,ui->action_XML);
    ui->toolBar->insertAction(ui->action_XML,ui->action_Excel);
    ui->toolBar->insertSeparator(ui->action_AllMode);
    //by lk  end

    //添加状态栏，显示状态信息
    m_statusBarWidget = new StatusBarWidget(this);
    ui->statusBar->addWidget(m_statusBarWidget);


    //------------------------------------------------------------------------
    // 数据导航树窗口
    //------------------------------------------------------------------------
    NXDockWidget* fileDockWidget = new NXDockWidget(QStringLiteral("数据导航树"));
    this->addDockWidget(Qt::LeftDockWidgetArea, fileDockWidget);
    m_datatreewig = new DataTreeWig(this);
    fileDockWidget->setWidget(m_datatreewig);



    //------------------------------------------------------------------------
    // 数据信号窗口
    //------------------------------------------------------------------------
    NXDockWidget* strListDockWidget = new NXDockWidget(QStringLiteral("曲线数据"));
    this->addDockWidget(Qt::RightDockWidgetArea, strListDockWidget);
    m_dataTableWig = new dataTableWig();
    strListDockWidget->setWidget(m_dataTableWig);

    //------------------------------------------------------------------------
    // 设置窗口
    //------------------------------------------------------------------------
    //暂时屏蔽属性面板
    NXDockWidget* toolBoxDockWidget = new NXDockWidget(QStringLiteral("属性面板"));
    m_chartConfigWig = new chartConfigWig();
    toolBoxDockWidget->setWidget(m_chartConfigWig);
    this->addDockWidget(Qt::RightDockWidgetArea, toolBoxDockWidget);


    //------------------------------------------------------------------------
    // 日志输出窗口
    //------------------------------------------------------------------------
    NXDockWidget* outputDockWidget = new NXDockWidget(QStringLiteral("日志输出"));
    this->addDockWidget(Qt::BottomDockWidgetArea, outputDockWidget);
    textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    //by likun start
    //增加一个清空日志栏的操作
    textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QMenu *menu=textEdit->createStandardContextMenu();
    QAction *clearAction=new QAction(menu);
    clearAction->setText(QStringLiteral("清空日志"));
    connect(clearAction,&QAction::triggered,[=]
    {
        textEdit->clear();
    });
    menu->clear();
    menu->addAction(clearAction);

    connect(textEdit,&QTextEdit::customContextMenuRequested,[=]
    {
        menu->exec(QCursor::pos());
    });
    //by likun end
    outputDockWidget->setWidget(textEdit);

    //主窗口中心工作区域
    centralWidget_ = new customListwidget();
    centralWidget_->setWrapping(true);						//自动换行
    centralWidget_->setFlow(QListView::LeftToRight);        //从左到右布局
    centralWidget_->setMovement(QListView::Snap);
    centralWidget_->setWidgethorstationMax(m_horstationMax);

    stackedWidget_=new QStackedWidget(this);
    stackedWidget_->addWidget(centralWidget_);

    this->setCentralWidget(stackedWidget_);
    stackedWidget_->setCurrentWidget(centralWidget_);
    this->tabifyDockWidget(strListDockWidget,toolBoxDockWidget);//放到一起，实现tab页展示
    strListDockWidget->raise();

    // 打印日志
    QLOG_INFO() << QStringLiteral("初始化窗口成功");
//    QLOG_WARN() << "4-warn msg";
//    QLOG_ERROR() << "5-error msg";
//    QLOG_FATAL()  << "6-fatal msg";
//    QLOG_TRACE() << QStringLiteral();
//    QLOG_DEBUG() << "2-debug msg";
}

void MainWindow::InitConnect()
{
    connect(ui->action_Excel,&QAction::triggered,this,&MainWindow::slotOpenExcel);
    connect(ui->action_XML,&QAction::triggered,this,&MainWindow::slotOpenXml);
    connect(m_datatreewig,&DataTreeWig::signalNodeItem,this,&MainWindow::slotNodeItem);

    //by lk start
    connect(m_datatreewig,&DataTreeWig::signalActionClearAllWidget,this,&MainWindow::slotActionClearAllWidget);
    connect(centralWidget_,&customListwidget::signalSetTreeItemUnchecked,this,&MainWindow::slotSetTreeItemUnchecked);
    connect(m_datatreewig,&DataTreeWig::signallocationChart,this,&MainWindow::slotlocationChart);
    connect(m_datatreewig,&DataTreeWig::signalFullScreenWindow,this,&MainWindow::slot_RecvFullScreenWindow);
    connect(centralWidget_,&customListwidget::sigRearrange,this,&MainWindow::sltsetSetWidgetNumber);
    //by lk end

    connect(ui->action_AllMode,&QAction::triggered,this,&MainWindow::slot_AllMode);
    connect(ui->action_oneMode,&QAction::triggered,this,&MainWindow::slot_oneMode);
    connect(ui->action_restore,&QAction::triggered,this,&MainWindow::slotActionRestoreZoom);
    connect(ui->action_CurveAdaptation,&QAction::triggered,this,&MainWindow::slotAction_CurveAdaptation);
    connect(ui->actionzoomIn,&QAction::triggered,this,&MainWindow::slotActionzoomIn);
    connect(ui->actionzoomOut,&QAction::triggered,this,&MainWindow::slotActionzoomOut);
    connect(ui->action_savePNG,&QAction::triggered,this,&MainWindow::slotAction_savePNG);
    connect(ui->actionClearAllWidget,&QAction::triggered,this,&MainWindow::slotActionClearAllWidget);
    connect(ui->action_setWidgetNumber,&QAction::triggered,this,&MainWindow::slotSetWidgetNumber);
    connect(m_dataTableWig,&dataTableWig::sig_SendlocatorData,this,&MainWindow::slot_SendlocatorData);
    connect(m_dataTableWig,&dataTableWig::sig_ClearlocatorData,this,&MainWindow::slot_ClearlocatorData);
    QLOG_INFO() <<QStringLiteral("初始化连接成功");
}

MdiChildWidgetBase *MainWindow::createMdiChild(QString id)
{
    MdiChildWidgetBase *child = new MdiChildWidgetBase();
    QListWidgetItem *nitem = new QListWidgetItem();
    int width = INIT_NUM;//列的宽度
    if(m_horstationMax == (int)COLUMNS::COLUMNS_ONE)
        width = (centralWidget_->width() + m_horstationMax) - (m_horstationMax * 26) - 4;
    else if(m_horstationMax == (int)COLUMNS::COLUMNS_TWO)
        width = (centralWidget_->width() + m_horstationMax)  / m_horstationMax - (m_horstationMax * 10);
    else if(m_horstationMax == (int)COLUMNS::COLUMNS_THREE)
        width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 5);
    else if(m_horstationMax == (int)COLUMNS::COLUMNS_FOUR)
        width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 2) - 5;
    else if(m_horstationMax == (int)COLUMNS::COLUMNS_FIVE)
        width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 2) - 2;
    auto height = centralWidget_->height() / m_verticalMax - (m_verticalMax * 5);//行的高度
    nitem->setSizeHint(QSize(width,height));
    nitem->setBackground(QColor(Qt::white));
    nitem->setData(Qt::UserRole + 1,QVariant::fromValue(id));
    centralWidget_->setSpacing(4);
    centralWidget_->addListItem(id,nitem);
    centralWidget_->setItemWidget(nitem,child);

    //by likun start
    //信号连接
    child->setcurWidgetId(id);
    connect(child,SIGNAL(sig_SendPoint(QPoint)),this,SLOT(slot_RecvPoint(QPoint)));
    connect(child,SIGNAL(sig_updataGlobalState(bool)),this,SLOT(slotUpdataGlobalState(bool)));
    connect(child,SIGNAL(sig_SendWheel(QWheelEvent*)),this,SLOT(slot_RecvWheel(QWheelEvent*)));
    connect(child,SIGNAL(sig_SendMouseMove(QString,QMouseEvent*)), this, SLOT(slot_RecvMouseMove(QString,QMouseEvent*)));
    connect(child,SIGNAL(sig_SendMousePress(QString,QMouseEvent*)), this, SLOT(slot_RecvMousePress(QString,QMouseEvent*)));
    connect(child,SIGNAL(sig_SendMouseRelease(QString,QMouseEvent*)), this, SLOT(slot_RecvMouseRelease(QString,QMouseEvent*)));
    connect(child,SIGNAL(sig_SendSelectGraphData(XxwCustomPlot*,QCPGraph*)),this,SLOT(slot_RecvSelectGraphData(XxwCustomPlot*,QCPGraph*)));
    connect(child,SIGNAL(sig_SendFullScreenWindow(QString)),this,SLOT(slot_RecvFullScreenWindow(QString)));
    connect(child,SIGNAL(sig_SendCurveActionRestoreFull(QString)),this,SLOT(slot_CurveActionRestoreFull(QString)));
    connect(child,SIGNAL(sig_SendRangePos(QPoint,QPoint)),this,SLOT(slot_SendRangePos(QPoint,QPoint)));
    connect(child,SIGNAL(sig_SendCustomData(QString,QCPGraph*)),this,SLOT(slot_SendCustomData(QString,QCPGraph*)));
    connect(child,SIGNAL(sig_AddVerticalLine()),this,SLOT(slt_AddVerticalLine()));
    connect(child,SIGNAL(sig_RemoveVerticalLine()),this,SLOT(slt_RemoveVerticalLine()));
    connect(child->getCurPlotWidget(),SIGNAL(sigGlobalshowAllGraph()),this,SLOT(slotActionRestoreZoom()));
     connect(child->getCurPlotWidget(),SIGNAL(sigGlobalCurveAdaptation()),this,SLOT(slotAction_CurveAdaptation()));
    //by likun end

    return child;
}

void MainWindow::slotWriteLog(const QString &message, int level)
{
    QString str = message;
    if(level ==(int)LOGSTATE::LOGSTATE_INFO)
    {
        textEdit->setTextColor(QColor(Qt::black));
    }
    else if (level == (int)LOGSTATE::LOGSTATE_TRACE)
    {
        textEdit->setTextColor(QColor("gray"));
    }
    else if (level == (int)LOGSTATE::LOGSTATE_DEBUG)
    {
        textEdit->setTextColor(QColor(0, 0, 0));
    }
    else if (level == (int)LOGSTATE::LOGSTATE_WARN)
    {
        textEdit->setTextColor(QColor(255, 107, 107));
    }
    textEdit->append(message + "!");
}

void MainWindow::slot_SendCustomData(QString id, QCPGraph *graph)
{
    if(graph == nullptr || id == "")//没有数据的曲线也让拆分
        return;
    MdiChildWidgetBase *child = createMdiChild(id);//创建MDI子窗口

    auto data = graph->data()->mData;
    QVector<QPointF> customData=graph->property("tick").value<QVector<QPointF>>();
    QVector<double>timePoint;
    foreach (auto var, data)
    {
        timePoint.append(var.key);
    }
    child->setTreeItemData(id,graph->name(),customData,timePoint);//传入数据
    QLOG_INFO() <<QStringLiteral("拆分%1曲线图成功").arg(graph->name(),true);
}

void MainWindow::slotSetTreeItemUnchecked(QString uuid)
{
    m_datatreewig->cancelItemcheck(uuid);
}

void MainWindow::slotlocationChart(QString uuid)
{
    centralWidget_->locationChart(uuid);
}

void MainWindow::slt_AddVerticalLine()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            item->getCurPlotWidget()->AddVerticalLine();
        }
    }
}

void MainWindow::slt_RemoveVerticalLine()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            item->getCurPlotWidget()->RemoveVerticalLine();
        }
    }
}

void MainWindow::slotSetWidgetNumber()
{
    bool ok;
    int index = QInputDialog::getInt(centralWidget_, QStringLiteral("输入列数"),QStringLiteral("每一行展示窗口数:"), m_horstationMax, 1, 5, 1, &ok);
    if (ok)
    {
        m_horstationMax=index;
        sltsetSetWidgetNumber();
        centralWidget_->setWidgethorstationMax(m_horstationMax);
    }
    QLOG_INFO() <<QStringLiteral("设置窗口列:%1").arg(m_horstationMax);
}

void MainWindow::sltsetSetWidgetNumber()
{
    int width = INIT_NUM;
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(curWidget)
        {
            if(m_horstationMax == (int)COLUMNS::COLUMNS_ONE)
                width = (centralWidget_->width() + m_horstationMax) - (m_horstationMax * 26) - 4;
            else if(m_horstationMax == (int)COLUMNS::COLUMNS_TWO)
                width = (centralWidget_->width() + m_horstationMax)  / m_horstationMax - (m_horstationMax * 10);
            else if(m_horstationMax == (int)COLUMNS::COLUMNS_THREE)
                width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 5);
            else if(m_horstationMax == (int)COLUMNS::COLUMNS_FOUR)
                width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 2) - 5;
            else if(m_horstationMax == (int)COLUMNS::COLUMNS_FIVE)
                width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 2) - 2;
            else
                width= (centralWidget_->width()  / m_horstationMax) - (m_horstationMax * 2) - 2;
            auto height = centralWidget_->height() / m_verticalMax - (m_verticalMax * 5);//行的高度
            curWidget->resize(QSize(width,height));
            varItem->setSizeHint(QSize(width,height));
        }
    }
}

void MainWindow::loadvvFile(const QString &vvfile)
{
    if(vvfile.isEmpty() == false)
        m_datatreewig->setVVFile(m_workSpacePath,vvfile);
}
void MainWindow::loadCSVFile(const QString &csvfile)
{
    if(csvfile.isEmpty() == false)
    {
        m_datatreewig->setMonitorFile(csvfile);
        m_datatreewig->setExpandAll();
        QLOG_INFO() <<QStringLiteral("打开Excel:%1文件成功").arg(csvfile);
    }
}
void MainWindow::slotOpenExcel()
{
    QStringList fileList=QFileDialog::getOpenFileNames(nullptr,QStringLiteral("选择csv格式记录文件"),qApp->applicationDirPath(),"*.csv *.xlsx");

    if(fileList.isEmpty() == false)
    {
        foreach(auto fileName,fileList)
        {
            m_datatreewig->setMonitorFile(fileName);
            m_datatreewig->setExpandAll();
            QLOG_INFO() <<QStringLiteral("打开Excel:%1文件成功").arg(fileName);
        }
    }
}

void MainWindow::slotOpenXml()
{
    QStringList fileList=QFileDialog::getOpenFileNames(nullptr,QStringLiteral("选择测试脚本"),qApp->applicationDirPath() + "/testCase","*.xml");

    if(fileList.isEmpty() == false)
    {
        foreach(auto fileName,fileList)
        {
            m_datatreewig->setVVFile(m_workSpacePath,fileName);
            m_datatreewig->setExpandAll();
            QLOG_INFO() <<QStringLiteral("打开Xml:%1文件成功").arg(fileName);
        }
    }
}

void MainWindow::slotNodeItem(TreeItem *item)
{
    if(item == nullptr)
        return;

    if(item->isChecked())
    {

        QVariantMap map = item->getNodeData();//获取节点的数据
        if(map.isEmpty() || centralWidget_->getAllGraphIdAndTickTimeRatio().keys().contains(map.value(CHARTID).toString()))
            return;

        MdiChildWidgetBase *child = createMdiChild(map.value(CHARTID).toString());//创建MDI子窗口
        child->setTreeItemData(map.value(CHARTID).toString(),map.value(CHARTNAME).toString(),map.value(CHARTDATA).value<QVector<QPointF>>(),map.value(TIME_POINT).value<QVector<double>>(),true);//传入数据
        centralWidget_->addGraphIdAndTickTimeRatio(map.value(CHARTID).toString(),map.value(TICKTIMERATIO).toDouble());
        QLOG_INFO() <<QStringLiteral("创建%1曲线图成功").arg(map.value(CHARTNAME).toString());
    }
    else
    {

        QLOG_WARN() << QStringLiteral("删除%1曲线图成功").arg(item->getNodeData().value(CHARTNAME).toString());
        if(item->getNodeData().value(CHARTID).toString() == m_dataTableWig->getCurWidgetId())
        {
            m_dataTableWig->ClearTabData();
        }
        centralWidget_->removeListItem(item);

        m_CentralWidgetId.clear();
    }
}

void MainWindow::slot_RecvPoint(QPoint pos)
{
    GlobalCurveState::getInstance()->setGlobalPos(pos);
    foreach (auto curWidget, centralWidget_->getBeginEndItem())
    {
        if(curWidget)
            curWidget->updataPoint();
    }

//    foreach (auto varItem, centralWidget_->getItems().values())
//    {
//        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
//        if(curWidget)
//            curWidget->updataPoint();
//    }
}

void MainWindow::slot_RecvWheel(QWheelEvent *event)
{
    GlobalCurveState::getInstance()->setGlobalWheelEvent(event);
    foreach (auto curWidget, centralWidget_->getBeginEndItem())
    {
        if(curWidget)
            curWidget->updataWheelEvent();
    }

//    foreach (auto varItem, centralWidget_->getItems().values())
//    {
//        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
//        if(curWidget)
//            curWidget->updataWheelEvent();
//    }
}

void MainWindow::slot_RecvMouseMove(QString id,QMouseEvent *event)
{
    GlobalCurveState::getInstance()->setGlobalMouseMove(event);
    GlobalCurveState::getInstance()->setGlobalActiveWindowId(id);

    foreach (auto curWidget, centralWidget_->getBeginEndItem())
    {
        if(curWidget)
            curWidget->updataMouseMove();
    }

//    foreach (auto varItem, centralWidget_->getItems().values())
//    {
//        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
//        if(curWidget)
//            curWidget->updataMouseMove();
//    }
}

void MainWindow::slot_RecvMousePress(QString id,QMouseEvent *event)
{
    Q_UNUSED(id);
    GlobalCurveState::getInstance()->setGlobalMousePress(event);

    foreach (auto curWidget, centralWidget_->getBeginEndItem())
    {
        if(curWidget)
            curWidget->updataMousePress();
    }

    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(curWidget)
        {
            curWidget->updataMousePress();
        }
    }
}

void MainWindow::slot_RecvMouseRelease(QString id,QMouseEvent *event)
{
    Q_UNUSED(id);
    GlobalCurveState::getInstance()->setGlobalMouseRelease(event);

    foreach (auto curWidget, centralWidget_->getBeginEndItem())
    {
        if(curWidget)
            curWidget->updataMouseRelease();
    }


    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(curWidget)
            curWidget->updataMouseRelease();
    }
}

void MainWindow::slot_AllMode()
{
    GlobalCurveState::getInstance()->setGlobalState(true);
    m_statusBarWidget->setlabelWinModeStart(true);
    QLOG_INFO() <<QStringLiteral("开启全局窗口模式");
}

void MainWindow::slot_oneMode()
{
    GlobalCurveState::getInstance()->setGlobalState(false);
    m_statusBarWidget->setlabelWinModeStart(false);
    QLOG_INFO() <<QStringLiteral("开启单窗口模式");
}

void MainWindow::slotUpdataGlobalState(bool isTrue)
{
    m_statusBarWidget->setlabelWinModeStart(isTrue);

    if(!GlobalCurveState::getInstance()->getGlobalState())
    {
        resetPlotState(!isTrue);
    }
}

void MainWindow::slot_RecvSelectGraphData(XxwCustomPlot *plot,QCPGraph *graph)
{
    if(graph && plot)
    {
        //by likun start
        //添加之前先清空一下 (主要是解决表格数据和单位不匹配的问题)
        m_dataTableWig->ClearTabData();
        //by likun end
        //数据表格窗口
        m_statusBarWidget->setcustomName(graph->name());
        m_dataTableWig->setcurWidgetId(plot->getcurWidgetId());
        m_dataTableWig->addGraphData(plot,graph);

        //曲线设置窗口
        m_chartConfigWig->setGraph(plot,graph);
    }
}

void MainWindow::slot_RecvFullScreenWindow(QString id)
{
    if(m_CentralWidgetId == id)
        return;
    m_CentralWidgetId = id;
    MdiChildWidgetBase *itemWidget = centralWidget_->getCurWidgetId(id);

    stackedWidget_->addWidget(itemWidget);
    stackedWidget_->setCurrentWidget(itemWidget);

    GlobalCurveState::getInstance()->setGlobalWindows(true);
    GlobalCurveState::getInstance()->setGlobalState(false);
    m_statusBarWidget->setlabelWinModeStart(false);
    resetPlotState(true);
    QLOG_INFO() <<QStringLiteral("全屏显示");
}

void MainWindow::slot_CurveActionRestoreFull(QString id)
{
    GlobalCurveState::getInstance()->setGlobalWindows(false);
    if(m_CentralWidgetId.isEmpty())
        return;
      MdiChildWidgetBase *itemWidget = dynamic_cast<MdiChildWidgetBase *>(stackedWidget_->currentWidget());

    auto item = centralWidget_->getCurItem(id);
    QListWidgetItem *nitem = new QListWidgetItem();
    QSize sizeHint=item->sizeHint();
    nitem->setSizeHint(sizeHint);
    nitem->setBackground(QColor(Qt::white));
    nitem->setData(Qt::UserRole + 1,QVariant::fromValue(id));
    centralWidget_->insertListItem(id,centralWidget_->row(item),nitem);
    nitem->setSizeHint(sizeHint);

    centralWidget_->setItemWidget(nitem,itemWidget);
    stackedWidget_->setCurrentWidget(centralWidget_);

    m_CentralWidgetId.clear();
    delete item;
    QLOG_WARN() <<QStringLiteral("取消全屏显示");
}

void MainWindow::slot_SendRangePos(QPoint xpos, QPoint ypos)
{
    if(GlobalCurveState::getInstance()->getGlobalState())
    {
        foreach (auto varItem, centralWidget_->getItems().values())
        {
            MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
            if(curWidget)
                curWidget->setRange(xpos,ypos);
        }
    }
}

void MainWindow::slot_SendlocatorData(double begin, double end)
{
    //这里的代码可以优化， MdiChildWidgetBase内部已经有定位函数了
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plot = item->getCurPlot();
            for(int i=0;i<plot->graphCount();i++)
            {
                bool isEnd = false;
                if(end == 0)
                    isEnd = true;

                double beginXpos = begin;
                double endXPos = end;
                //获得x轴坐标位置对应的曲线上y的值
                auto data = plot->graph(i)->data()->mData;//会出现指针悬挂
                foreach (auto var, data)
                {
                    if(beginXpos > var.key)
                        continue;
                    else
                    {
                        beginXpos = var.key;
                        break;
                    }
                }

                bool isInsert = false;
                foreach (auto varValue, data)
                {
                    if(varValue.key == beginXpos)
                        isInsert = true;
                    if(isInsert && varValue.key <= endXPos)
                    {
                        addTracerItems(varValue.key,varValue.value,plot);
                    }
                    else if (isInsert && varValue.key > endXPos)
                    {
                        break;
                    }
                }
                plot->replot(QCustomPlot::rpQueuedReplot);
            }
        }
    }
}

void MainWindow::slot_ClearlocatorData()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plot = item->getCurPlot();
            foreach (auto var, plot->getAllData())
            {
                plot->removeItem(var);
            }
            plot->clearTracerItems();
            plot->replot(QCustomPlot::rpQueuedReplot);
        }
    }

}

void MainWindow::slotActionRestoreZoom()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plotWidget = item->getCurPlotWidget();
            if(plotWidget)
            {
                plotWidget->showAllGraph(true);
                plotWidget->getCurPlot()->replot(QCustomPlot::rpQueuedReplot);
            }
        }
    }
    QLOG_INFO() <<QStringLiteral("恢复全部窗口的缩放");
}

void MainWindow::slotAction_CurveAdaptation()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plotWidget = item->getCurPlotWidget();
            if(plotWidget)
            {
                plotWidget->CurveAdaptation();
                plotWidget->getCurPlot()->replot(QCustomPlot::rpQueuedReplot);
            }
        }
    }
    QLOG_INFO() <<QStringLiteral("曲线自适应场景");
}

void MainWindow::slotActionzoomIn()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plotWidget = item->getCurPlotWidget();
            if(plotWidget)
            {
                plotWidget->customZoomOut(2);
                plotWidget->getCurPlot()->replot(QCustomPlot::rpQueuedReplot);
            }
        }
    }
}

void MainWindow::slotActionzoomOut()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            auto plotWidget = item->getCurPlotWidget();
            if(plotWidget)
            {
                plotWidget->customZoomIn(2);
                plotWidget->getCurPlot()->replot(QCustomPlot::rpQueuedReplot);
            }
        }
    }
}

void MainWindow::slotActionClearAllWidget()
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            centralWidget_->removeListItem(item->getCurWidgetId());
        }
    }
    if(m_datatreewig)
        m_datatreewig->clearCheckState();
    if(m_dataTableWig)
        m_dataTableWig->ClearTabData();
    QLOG_WARN() <<QStringLiteral("清空所有的窗口");
}

void MainWindow::slotAction_savePNG()
{
    QString filename = QFileDialog::getSaveFileName(this,QStringLiteral("保存图片"),"",tr("Images (*.png)")); //选择路径
    int index = INIT_NUM;
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *item = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(item)
        {
            ++index;
            auto plotWidget = item->getCurPlot();
            if(plotWidget)
            {
                if(plotWidget->savePng(QString("%1.png").arg(filename + QString::number(index)), PNG_WIDTH, PNG_HEIGHT))
                {
                     QLOG_INFO() <<QStringLiteral("另存为图片成功");
                }
                else
                {
                    QLOG_WARN() <<QStringLiteral("另存为图片失败");
                }
            }
        }
    }
}

void MainWindow::addTracerItems(double x, double y, XxwCustomPlot *plot)
{
    QCPItemTracer *m_tracer = new QCPItemTracer(plot);
    m_tracer->setSelectable(false);
    m_tracer->setStyle(QCPItemTracer::tsCircle);
    m_tracer->setPen(QPen(Qt::red,3));
    m_tracer->setBrush(Qt::SolidPattern);
    m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
    m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    m_tracer->setSize(7);
    m_tracer->position->setCoords(x,y);//位置
    plot->addTracerItems(m_tracer);
}

void MainWindow::createDockWidgetBar(Qt::DockWidgetArea area)
{
    if(m_dockWidgetBar.find(area) != std::end(m_dockWidgetBar)) {
        return;
    }

    NXDockWidgetTabBar* dockWidgetBar = new NXDockWidgetTabBar(area);
    m_dockWidgetBar[area] = dockWidgetBar;
    connect(dockWidgetBar, &NXDockWidgetTabBar::signal_dockWidgetButton_clicked, this, &MainWindow::showDockWidget);
    addToolBar(dockAreaToToolBarArea(area), dockWidgetBar);//工具栏添加到主窗口的指定区域
}

void MainWindow::dockWidgetUnpinned(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr) {
        return;
    }

    NXDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
    if(dockWidgetBar == nullptr) {
        return;
    }

    QList<QDockWidget*> dockWidgetList = tabifiedDockWidgets(dockWidget);
    dockWidgetList.push_back(dockWidget);

    std::for_each(std::begin(dockWidgetList), std::end(dockWidgetList), [&](QDockWidget* qDockWidget)
    {
        NXDockWidget* dockWidget = static_cast<NXDockWidget*>(qDockWidget);

        dockWidget->setState(DockWidgetState::Hidden);

        if(!dockWidget->isHidden())
        {
            dockWidgetBar->addDockWidget(dockWidget);

            dockWidget->setTabifiedDocks(dockWidgetList);

            QMainWindow::removeDockWidget(dockWidget);
        }
    } );

    if(dockWidget->getArea() == Qt::LeftDockWidgetArea)
    {
        getDockWidgetBar(Qt::TopDockWidgetArea)->insertSpacing();
        getDockWidgetBar(Qt::BottomDockWidgetArea)->insertSpacing();
    }
}

void MainWindow::dockWidgetPinned(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr) {
        return;
    }

    NXDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
    if(dockWidgetBar == nullptr) {
        return;
    }

    m_dockWidget = nullptr;

    std::vector<NXDockWidget*> dockWidgetList = dockWidget->getTabifiedDocks();
    dockWidgetList.push_back(dockWidget);

    NXDockWidget* prevDockWidget = nullptr;

    std::for_each(std::begin(dockWidgetList), std::end(dockWidgetList), [&](NXDockWidget* dockWidget)
    {
        if(dockWidgetBar->removeDockWidget(dockWidget))
        {
            if(prevDockWidget == nullptr) {
                QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
            }
            else {
                tabifyDockWidget(prevDockWidget, dockWidget);
            }

            prevDockWidget = dockWidget;

            dockWidget->setState(DockWidgetState::Docked);

            dockWidget->show();
        }
    } );

    dockWidget->raise();

    if((dockWidget->getArea() == Qt::LeftDockWidgetArea) &&
       dockWidgetBar->isHidden())
    {
        getDockWidgetBar(Qt::TopDockWidgetArea)->removeSpacing();
        getDockWidgetBar(Qt::BottomDockWidgetArea)->removeSpacing();
    }
}

void MainWindow::showDockWidget(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr) {
        return;
    }

    if(dockWidget->isHidden())
    {
        hideDockWidget(m_dockWidget);

        if(dockWidget->isFloating())
        {
            QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
            dockWidget->setFloating(false);

            QMainWindow::removeDockWidget(dockWidget);
        }
        adjustDockWidget(dockWidget);
        dockWidget->show();
        dockWidget->raise();
        dockWidget->setFocus();
        m_dockWidget = dockWidget;
    }
    else
    {
        hideDockWidget(dockWidget);
    }
}

bool MainWindow::event(QEvent* event)
{
    if(event->type() == QEvent::Resize)
    {
        hideDockWidget(m_dockWidget);
    }
    return QMainWindow::event(event);
}
//QDockWidget
void MainWindow::adjustDockWidget(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr) {
        return;
    }

    QRect rect = getDockWidgetsAreaRect();
    Qt::DockWidgetAreas area=dockWidget->getArea();
    switch( area )
    {
        case Qt::LeftDockWidgetArea: {
            dockWidget->setGeometry(rect.left(), rect.top(), dockWidget->width(), rect.height());
        }
        break;

        case Qt::TopDockWidgetArea: {
            dockWidget->setGeometry(rect.left(), rect.top(), rect.width(), dockWidget->height());
        }
        break;

        case Qt::RightDockWidgetArea: {
            dockWidget->setGeometry(rect.left() + rect.width() - dockWidget->width(), rect.top(), dockWidget->width(), rect.height());
        }
        break;

        case Qt::BottomDockWidgetArea: {
            dockWidget->setGeometry(rect.left(), rect.top() + rect.height() - dockWidget->height(), rect.width(), dockWidget->height());
        }
        break;
    }
}

NXDockWidgetTabBar* MainWindow::getDockWidgetBar(Qt::DockWidgetArea area)
{
    assert(m_dockWidgetBar.find(area) != std::end(m_dockWidgetBar));

    auto it = m_dockWidgetBar.find(area);
    if(it != std::end(m_dockWidgetBar)) {
        return it->second;
    }

    return nullptr;
}

void MainWindow::addDockWidget(Qt::DockWidgetArea area, NXDockWidget* dockWidget)
{
    addDockWidget(area, dockWidget, Qt::Vertical);
}

void MainWindow::addDockWidget(Qt::DockWidgetArea area, NXDockWidget* dockWidget, Qt::Orientation orientation)
{
    if(dockWidget == nullptr) {
        return;
    }

    connect(dockWidget, &NXDockWidget::signal_pinned, this, &MainWindow::dockWidgetPinned);
    connect(dockWidget, &NXDockWidget::signal_unpinned, this, &MainWindow::dockWidgetUnpinned);
    connect(dockWidget, &NXDockWidget::signal_docked, this, &MainWindow::dockWidgetDocked);
    connect(dockWidget, &NXDockWidget::signal_undocked, this, &MainWindow::dockWidgetUndocked);

    m_dockWidgets.push_back(dockWidget);

    QMainWindow::addDockWidget(area, dockWidget, orientation);

    if(m_menuWindows == nullptr)
    {
        m_menuWindows = menuBar()->addMenu(QStringLiteral("窗口部件"));
        connect(m_menuWindows, &QMenu::triggered, this, &MainWindow::menuWindows_triggered);
    }

    QString title = dockWidget->windowTitle();
    if(title.isEmpty()) {
        title = QObject::tr("Noname");
    }

    QAction* action = new QAction(title, m_menuWindows);
    m_menuWindows->addAction(action);

    dockWidget->setMenuAction(action);
}

void MainWindow::removeDockWidget(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr) {
        return;
    }

    auto it = std::find(m_dockWidgets.begin(), m_dockWidgets.end(), dockWidget);
    if(it == m_dockWidgets.end()) {
        return;
    }

    m_dockWidgets.erase(it);

    if(dockWidget->isMinimized()) {
        dockWidgetPinned(dockWidget);
    }

    QMainWindow::removeDockWidget(dockWidget);

    dockWidget->setParent(nullptr);


    QAction* action = dockWidget->getMenuAction();
    if(action != nullptr) {
        m_menuWindows->removeAction(action);
    }
}

void MainWindow::dockWidgetDocked(NXDockWidget* dockWidget)
{
    if(dockWidget == nullptr)
        return;
}

void MainWindow::dockWidgetUndocked(NXDockWidget* dockWidget)
{
    hideDockWidget(m_dockWidget);

    NXDockWidgetTabBar* dockWidgetBar = getDockWidgetBar(dockWidget->getArea());
    if(dockWidgetBar == nullptr)
        return;

    dockWidget->clearTabifiedDocks();

    if(dockWidgetBar->removeDockWidget(dockWidget))
    {
        if(!dockWidget->isFloating())
        {
            QMainWindow::addDockWidget(dockWidget->getArea(), dockWidget);
        }

        if((dockWidget->getArea() == Qt::LeftDockWidgetArea) && dockWidgetBar->isHidden())
        {
            getDockWidgetBar(Qt::TopDockWidgetArea)->removeSpacing();
            getDockWidgetBar(Qt::BottomDockWidgetArea)->removeSpacing();
        }

        dockWidget->show();
    }
}

std::list<NXDockWidget*> MainWindow::getDockWidgetListAtArea(Qt::DockWidgetArea area)
{
    std::list<NXDockWidget*> dockWidgetList;
    std::copy_if(std::begin(m_dockWidgets), std::end(m_dockWidgets), std::back_inserter(dockWidgetList), [area](const NXDockWidget* dockWidget) {
        return (dockWidget->getArea() == area) && (dockWidget->isDocked());
    });

    return dockWidgetList;
}

QRect MainWindow::getDockWidgetsAreaRect()
{
    int left = this->centralWidget_->x();
    std::list<NXDockWidget*> leftAreaDockWidgets = getDockWidgetListAtArea(Qt::LeftDockWidgetArea);
    std::for_each(std::begin(leftAreaDockWidgets), std::end(leftAreaDockWidgets), [&left](const NXDockWidget* dockWidget)
    {
        if((dockWidget->x() >= 0) && (dockWidget->width() > 0)) {
            left = std::min(left, dockWidget->x());
        }
    });

    int top = this->centralWidget_->y();
    std::list<NXDockWidget*> topAreaDockWidgets = getDockWidgetListAtArea(Qt::TopDockWidgetArea);
    std::for_each(std::begin(topAreaDockWidgets), std::end(topAreaDockWidgets), [&top](const NXDockWidget* dockWidget)
    {
        if((dockWidget->y() >= 0) && (dockWidget->height() > 0)) {
            top = std::min(top, dockWidget->y());
        }
    });

    int right = this->centralWidget_->x()+this->centralWidget_->width();
    std::list<NXDockWidget*> rightAreaDockWidgets = getDockWidgetListAtArea(Qt::RightDockWidgetArea);
    std::for_each(std::begin(rightAreaDockWidgets), std::end(rightAreaDockWidgets), [&right](const NXDockWidget* dockWidget)
    {
        if((dockWidget->x() >= 0) && (dockWidget->width() > 0)) {
            right = std::max(right, dockWidget->x() + dockWidget->width());
        }
    });

    int bottom = this->centralWidget_->y()+this->centralWidget_->height();
    std::list<NXDockWidget*> bottomAreaDockWidgets = getDockWidgetListAtArea(Qt::BottomDockWidgetArea);
    std::for_each(std::begin(bottomAreaDockWidgets), std::end(bottomAreaDockWidgets), [&bottom](const NXDockWidget* dockWidget)
    {
        if((dockWidget->y() >= 0) && (dockWidget->height() > 0)) {
            bottom = std::max(bottom, dockWidget->y() + dockWidget->height());
        }
    });

    return QRect(left, top, right-left, bottom-top);
}

void MainWindow::hideDockWidget(NXDockWidget* dockWidget)
{
    if((dockWidget == nullptr) || (dockWidget->isHidden())) {
        return;
    }

    m_dockWidget = nullptr;

    dockWidget->hide();
}

void MainWindow::menuWindows_triggered(QAction* action)
{
    auto it = std::find_if(m_dockWidgets.begin(), m_dockWidgets.end(), [&](NXDockWidget* dockWidget) {
        return (dockWidget->getMenuAction() == action);
    });
    if(it == m_dockWidgets.end()) {
        return;
    }

    NXDockWidget* dockWidget = *it;
    if(dockWidget->isHidden())
    {
        hideDockWidget(m_dockWidget);

        dockWidget->show();
        dockWidget->raise();
    }
    else if(dockWidget->isMinimized())
    {
        showDockWidget(dockWidget);
    }

    dockWidget->setFocus();
}

void MainWindow::resetPlotState(bool isTrue)
{
    foreach (auto varItem, centralWidget_->getItems().values())
    {
        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)centralWidget_->itemWidget(varItem);
        if(curWidget)
            curWidget->setResetPlotState(isTrue);
    }
}
