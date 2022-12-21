#include "dataTableWig.h"
#include "ui_dataTableWig.h"


dataTableWig::dataTableWig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dataTableWig)
    ,customGraph(nullptr)
    ,customPlot(nullptr)
    ,m_CurrentWindowId("")
    ,unit(1)
{
    ui->setupUi(this);

    //设置表的格式
    QStringList list={QStringLiteral("x值(单位:s)"),QStringLiteral("Tick值"),QStringLiteral("y值")};
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    //ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{""color: black;padding-left: 6px;border: 2px solid #6c6c6c;}");
    ui->tableWidget->setHorizontalHeaderLabels(list);

    //by lk start
    //设置表格不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置默认精度为2位小数
    ui->doubleSpinBox_end->setDecimals(2);
    ui->doubleSpinBox_start->setDecimals(2);
    //by lk end
    ui->comboBox->setProperty("unit",0);

    ui->groupBox_2->setEnabled(false);
}

dataTableWig::~dataTableWig()
{
    delete ui;
}

void dataTableWig::addGraphData(XxwCustomPlot *plot,QCPGraph *graphData)
{
    if(graphData && plot)
    {
        //ui->comboBox->setCurrentIndex(1);
        //double tickTimeRatio=graphData->property("tickTimeRatio").toDouble();

        customPlot = plot;
        customGraph = graphData;
        auto data = graphData->data()->mData;
        //遍历数据
        int linecolume=1;
       auto gDate=graphData->property("tick").value<QVector<QPointF>>();
        foreach (auto var, data)
        {
            QString str_key = QString::number(var.key,'g',12);
            QString str_value = QString::number(var.value,'f',6);
            ui->tableWidget->setRowCount(linecolume);

            //ui->tableWidget->setItem(linecolume-1,0,new QTableWidgetItem(QString::number(str_key.toInt() * 0.02)));
            ui->tableWidget->setItem(linecolume-1,0,new QTableWidgetItem(QString::number(str_key.toDouble())));//时间（单位:s）;
            ui->tableWidget->item(linecolume-1,0)->setTextAlignment(Qt::AlignCenter);

            //ui->tableWidget->setItem(linecolume-1,1,new QTableWidgetItem(str_key));
            //ui->tableWidget->setItem(linecolume-1,1,new QTableWidgetItem(QString::number(str_key.toDouble()*tickTimeRatio*1000*1000*1000)));
            ui->tableWidget->setItem(linecolume-1,1,new QTableWidgetItem(QString::number(gDate.at(linecolume-1).x())));
            ui->tableWidget->item(linecolume-1,1)->setTextAlignment(Qt::AlignCenter);

            ui->tableWidget->setItem(linecolume-1,2,new QTableWidgetItem(str_value));
            ui->tableWidget->item(linecolume-1,2)->setTextAlignment(Qt::AlignCenter);
            linecolume++;
        }
        ui->groupBox_2->setEnabled(true);
        //ui->comboBox->setCurrentIndex(0);
    }
}

void dataTableWig::addTracerItems(double x, double y)
{
    QCPItemTracer *m_tracer = new QCPItemTracer(customPlot);
    m_tracer->setSelectable(false);
    m_tracer->setStyle(QCPItemTracer::tsCircle);
    m_tracer->setPen(QPen(Qt::red,3));
    m_tracer->setBrush(Qt::SolidPattern);
    m_tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
    m_tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    m_tracer->setSize(7);
    m_tracer->position->setCoords(x,y);//位置
    customPlot->addTracerItems(m_tracer);
}

void dataTableWig::setcurWidgetId(QString id)
{
    m_CurrentWindowId = id;
}

QString dataTableWig::getCurWidgetId()
{
    return m_CurrentWindowId;
}

void dataTableWig::ClearTabData()
{
//    //by likun start
//    //将单位下拉框置为ms
    ui->comboBox->setCurrentIndex(0);
//    //by likun end
    //ui->tableWidget->clear();
    ui->tableWidget->clearContents();
    m_CurrentWindowId.clear();
}

void dataTableWig::on_btn_locatorData_clicked()
{
    if(customPlot == nullptr || customGraph == nullptr || m_CurrentWindowId == "")
        return;

    //by likun start
    //定位前先清空数据
    on_btnClearTracer_clicked();
    //by likun end


    bool isEnd = false;
    if(ui->doubleSpinBox_start->value()==ui->doubleSpinBox_start->maximum())
        isEnd = true;

    double beginXpos=ui->doubleSpinBox_start->value();

    double endXPos=ui->doubleSpinBox_end->value();



    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();
        if(beginXpos > col_0.toDouble())
            continue;
        else
        {
            beginXpos = col_0.toDouble();
            break;
        }
    }

    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();

        if(endXPos > col_0.toDouble())
            continue;
        else if(endXPos == col_0.toDouble())
        {
            endXPos = col_0.toDouble();
            break;
        }
        else
        {
           // endXPos = col_0.toDouble();
            if(row<1)
            {
                return;
            }
            endXPos=ui->tableWidget->item(row-1,0)->text().toDouble();
            break;
        }
    }

    //by likun start

    //定位点时先将单位转换为秒
//    beginXpos=unitConversionToS(beginXpos);
//    endXPos=unitConversionToS(endXPos);
    //
    if(beginXpos>endXPos)
    {
      QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("起始位置不能大于结束位置"));
    }
    //by likun end

    //获得x轴坐标位置对应的曲线上y的值
    auto data = customGraph->data()->mData;//会出现指针悬挂
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
            addTracerItems(varValue.key,varValue.value);
        }
        else if (isInsert && varValue.key > endXPos)
        {
            break;
        }
    }

    customPlot->replot(QCustomPlot::rpQueuedReplot);

    if(ui->radioButton_globar->isChecked())
    {
        emit sig_SendlocatorData(beginXpos,endXPos);
    }
}

void dataTableWig::on_btnClearTracer_clicked()
{
    if(customPlot == nullptr || customGraph == nullptr || m_CurrentWindowId == "")
        return;
    foreach (auto var, customPlot->getAllData())
    {
        customPlot->removeItem(var);
    }
    customPlot->clearTracerItems();
    customPlot->replot(QCustomPlot::rpQueuedReplot);

    if(ui->radioButton_globar->isChecked())
    {
        emit sig_ClearlocatorData();
    }
}

void dataTableWig::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if(customPlot == nullptr || customGraph == nullptr || m_CurrentWindowId == "")
        return;
    if(item)
    {
        auto key = ui->tableWidget->item(item->row(),0)->text();
        auto value = ui->tableWidget->item(item->row(),2)->text();
        addTracerItems(key.toDouble(),value.toDouble());
        customPlot->replot(QCustomPlot::rpQueuedReplot);
    }
}

void dataTableWig::on_comboBox_currentIndexChanged(int index)
{
    //这个地方应该能优化
    QString unitStr = "ms";
    if(index == 0)
    {
        unitStr = "s";
        calculatorUnit(unit);
        calculatorUnitMS(unit);
        calculatorUnitUS(unit);
        calculatorUnitNS(unit);
        ui->doubleSpinBox_start->setMaximum(9999999999999.99);
        ui->doubleSpinBox_end->setMaximum(9999999999999.99);
        ui->doubleSpinBox_start->setDecimals(2);
        ui->doubleSpinBox_end->setDecimals(2);
    }
    else if(index == 1)
    {
        unitStr = "ms";
        calculatorUnit(unit);
        calculatorUnitMS(unit);
        calculatorUnitUS(unit);
        calculatorUnitNS(unit);
        ui->doubleSpinBox_start->setMaximum(9999999999999.99);
        ui->doubleSpinBox_end->setMaximum(9999999999999.99);
        ui->doubleSpinBox_end->setDecimals(2);
        ui->doubleSpinBox_start->setDecimals(2);
    }
    else if(index == 2)
    {
        unitStr = "us";
        calculatorUnit(unit);
        calculatorUnitMS(unit);
        calculatorUnitUS(unit);
        calculatorUnitNS(unit);
        ui->doubleSpinBox_start->setMaximum(9999999999999.99);
        ui->doubleSpinBox_end->setMaximum(9999999999999.99);
        ui->doubleSpinBox_end->setDecimals(2);
        ui->doubleSpinBox_start->setDecimals(2);
    }
    else if(index == 3)
    {
        unitStr = "ns";
        calculatorUnit(unit);
        calculatorUnitMS(unit);
        calculatorUnitUS(unit);
        calculatorUnitNS(unit);
        ui->doubleSpinBox_start->setMaximum(999999999999999);
        ui->doubleSpinBox_end->setMaximum(999999999999999);
        ui->doubleSpinBox_end->setDecimals(0);
        ui->doubleSpinBox_start->setDecimals(0);
    }

    unit = index;
    QStringList list={QStringLiteral("x值(单位:%1)").arg(unitStr),QStringLiteral("Tick值"),QStringLiteral("y值")};
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //同步改变图的单位

    if(customGraph&&customGraph->data())
    {
        double  t= unitConversion(ui->comboBox->property("unit").toInt(),index);
        auto data=customGraph->data()->mData;
        QVector<double>x;
        QVector<double>y;
        foreach(auto var,data)
        {
               x.append(var.key*t);
               y.append(var.value);
        }
        customGraph->data()->removeAfter(0.0);
        customGraph->addData(x,y);
        customPlot->update();
    }
    ui->comboBox->setProperty("unit",index);








}

void dataTableWig::calculatorUnit(int index)
{
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();
        if(index == 0 && ui->comboBox->currentIndex() == 1)//s-ms
        {
            //ui->tableWidget->item(row,0)->setText(QString::number(col_0.toFloat() * 1000,'f',6));
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000,'f',6));
        }
        else if(index == 0 && ui->comboBox->currentIndex() == 2)//s-us
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000 * 1000,'f',6));
        }
        else if(index == 0 && ui->comboBox->currentIndex() == 3)//ns
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000 * 1000 * 1000,'f',6));
        }
    }
}

void dataTableWig::calculatorUnitMS(int index)
{
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();
        if(index == 1 && ui->comboBox->currentIndex() == 0)//ms-s
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000,'f',6));
        }
        else if(index == 1 && ui->comboBox->currentIndex() == 2)//ms-us
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000,'f',6));
        }
        else if(index == 1 && ui->comboBox->currentIndex() == 3)//ms-ns
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000 * 1000,'f',6));
        }
    }
}

void dataTableWig::calculatorUnitUS(int index)
{
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();
        if(index == 2 && ui->comboBox->currentIndex() == 0)//us-s
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000 / 1000,'f',6));
        }
        else if(index == 2 && ui->comboBox->currentIndex() == 1)//us-ms
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000,'f',6));
        }
        else if(index == 2 && ui->comboBox->currentIndex() == 3)//us-ns
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() * 1000,'f',6));
        }
    }
}

void dataTableWig::calculatorUnitNS(int index)
{
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString col_0 = ui->tableWidget->item(row,0)->text();//ms
        QString col_1 = ui->tableWidget->item(row,1)->text();//tick
        QString col_2 = ui->tableWidget->item(row,2)->text();
        if(index == 3 && ui->comboBox->currentIndex() == 0)//ns-s
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000 / 1000 / 1000,'f',6));
        }
        else if(index == 3 && ui->comboBox->currentIndex() == 1)//ns-ms
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000 / 1000,'f',6));
        }
        else if(index == 3 && ui->comboBox->currentIndex() == 2)//ns-us
        {
            ui->tableWidget->item(row,0)->setText(QString::number(col_0.toDouble() / 1000,'f',6));
        }
    }
}

double dataTableWig::unitConversionToS(double sourceData)
{
    switch (ui->comboBox->currentIndex())
    {
    case 3:
        sourceData=sourceData/1000;
    case 2:
        sourceData=sourceData/1000;
    case 1:
        sourceData=sourceData/1000;
    }
    return sourceData;
}

double dataTableWig::unitConversion(int sourceUnit, int targetUnit)
{
    double source=1;
    double target=1;
    switch (sourceUnit)
    {
      case 0:
            source=1;
        break;
      case 1:
        source=1000;
        break;
      case 2:
        source=1000000;
        break;
       case 3:
        source =1000000000;
        break;
    }
    switch (targetUnit)
    {
      case 0:
            target=1;
        break;
      case 1:
        target=1000;
        break;
      case 2:
        target=1000000;
        break;
       case 3:
        target =1000000000;
        break;
    }

    return  target/source;
}

//void dataTableWig::on_doubleSpinBox_end_valueChanged(double arg1)
//{
//    ui->doubleSpinBox_start->setMaximum(arg1);
//}



//void dataTableWig::on_doubleSpinBox_start_valueChanged(double arg1)
//{
//    ui->doubleSpinBox_end->setMinimum(arg1);
//}
