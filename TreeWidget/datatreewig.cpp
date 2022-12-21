#include "datatreewig.h"
#include "ui_datatreewig.h"
#include <QDebug>
#include <QMenu>
#include <QStyleFactory>
#include <QMessageBox>


DataTreeWig::DataTreeWig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTreeWig)
{
    ui->setupUi(this);

    model = new TreeModel(ui->treeView);


    //by likun start
    //设置可多选
    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);


    //by likun end
    m_pTableViewSortFilterModelBase = new TableViewSortFilterModelBase(this);
    m_pTableViewSortFilterModelBase->setSourceModel(model);
    ui->treeView->setModel(m_pTableViewSortFilterModelBase);
    connect(model,&QAbstractItemModel::dataChanged,this,&DataTreeWig::slotDataChanged);
    ui->treeView->setStyle(QStyleFactory::create("Fusion"));
    ui->treeView->expandAll();
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint& )), this, SLOT(slotTreeViewDataMenu(const QPoint&)));

}

DataTreeWig::~DataTreeWig()
{
    if(model)
    {
        model->clear();
        delete model;
        model = nullptr;
    }

    if(m_pTableViewSortFilterModelBase)
    {
        delete m_pTableViewSortFilterModelBase;
        m_pTableViewSortFilterModelBase = nullptr;
    }
    delete ui;
}

void DataTreeWig::setMonitorFile(const QString &monitorFile)
{
    if(monitorFile.isEmpty()||openFiles.contains(monitorFile))
        return;
    openFiles.append(monitorFile);
    model->loadExcelModelData(monitorFile);//加载excel文件数据
    ui->treeView->viewport()->update();
}

void DataTreeWig::setVVFile(const QString &workSpacePath,const QString &vvfile)
{
    if(vvfile.isEmpty()||openFiles.contains(vvfile))
        return;
    openFiles.append(vvfile);
    model->loadXmlModelData(workSpacePath,vvfile);//加载测试脚本文件数据
    ui->treeView->viewport()->update();
}

void DataTreeWig::setExpandAll()
{
    ui->treeView->expandAll();
    ui->treeView->viewport()->update();
}

void DataTreeWig::slotDataChanged(const QModelIndex &top, const QModelIndex &bottom)
{
    TreeItem *curItem = model->getItem(top);
    setItemIsCheck(curItem,curItem->isChecked());
    emit signalNodeItem(curItem);
}

void DataTreeWig::on_lineEdit_textChanged(const QString &arg1)
{
    //Qt::CaseSensitive: Qt::CaseInsensitive //大小写区分
    QRegExp regExp(ui->lineEdit->text(), Qt::CaseInsensitive, QRegExp::RegExp);
    m_pTableViewSortFilterModelBase->setFilterRegExp(regExp);
    ui->treeView->expandAll();
}

void DataTreeWig::slotTreeViewDataMenu(const QPoint &pos)
{
    QMenu menu;
    if(!ui->treeView->indexAt(pos).data().isNull())
    {

        //by lk start
        //如果是根节点，增加一个删除节点的操作
        if(!ui->treeView->indexAt(pos).parent().isValid())//顶层节点独有操作
        {
            QAction* removeNode = new QAction(&menu);
            removeNode->setText(QStringLiteral("删除当前节点"));
            //connect(removeNode,&QAction::trigger,this,&DataTreeWig::slotremoveNode);
            connect(removeNode, SIGNAL(triggered()), this, SLOT(slotremoveNode()));
            menu.addAction(removeNode);
        }
        else //叶子节点独有操作
        {
            QAction *locationChart=new QAction(&menu);
            locationChart->setText(QStringLiteral("定位到曲线图"));
            connect(locationChart, SIGNAL(triggered()), this, SLOT(locationChart()));
            menu.addAction(locationChart);

            //此功能有一点缺陷，暂时不开放
//            QAction *FullScreenWindow=new QAction(&menu);
//            FullScreenWindow->setText(QStringLiteral("全屏显示曲线图"));
//            connect(FullScreenWindow, SIGNAL(triggered()), this,SLOT(FullScreenWindow()));
//            menu.addAction(FullScreenWindow);
        }
        //通用操作
        //清空所有节点
        QAction* removeAllNode = new QAction(&menu);
        removeAllNode ->setText(QStringLiteral("删除所有节点"));
        connect(removeAllNode, SIGNAL(triggered()), this, SLOT(slotremoveAllNode()));
        menu.addAction(removeAllNode);


        QAction *openChart=new QAction(&menu);
        openChart->setText(QStringLiteral("打开曲线图"));
        connect(openChart, SIGNAL(triggered()), this, SLOT(openSelectItem()));
        menu.addAction(openChart);



        QAction *closeChart=new QAction(&menu);
        closeChart->setText(QStringLiteral("关闭曲线图"));
        connect(closeChart, SIGNAL(triggered()), this, SLOT(closeSelectItem()));
        menu.addAction(closeChart);

        //by lk end


        QAction* ExpandNode = new QAction(&menu);
        ExpandNode ->setText(QStringLiteral("展开节点"));
        ExpandNode->setIcon(QIcon(":/images/expandNode.png"));
        connect(ExpandNode, SIGNAL(triggered()), this, SLOT(slotExpandNode()));
        menu.addAction(ExpandNode);

        QAction* PackUpNode = new QAction(&menu);
        PackUpNode ->setText(QStringLiteral("收起节点"));
        PackUpNode->setIcon(QIcon(":/images/PackUpNode.png"));
        connect(PackUpNode, SIGNAL(triggered()), this, SLOT(slotPackUpNode()));
        menu.addAction(PackUpNode);

        menu.exec(QCursor::pos());
    }
}

void DataTreeWig::slotExpandNode()
{
    QModelIndex curIndex = ui->treeView->currentIndex();
    QModelIndex index = curIndex.sibling(curIndex.row(), 0);
    manageNode(index,false);
}

void DataTreeWig::slotPackUpNode()
{
    QModelIndex curIndex = ui->treeView->currentIndex();
    QModelIndex index = curIndex.sibling(curIndex.row(), 0);
    manageNode(index,true);
}

void DataTreeWig::slotremoveNode()
{
    QModelIndex curIndex = ui->treeView->currentIndex();
    QModelIndex index = curIndex.sibling(curIndex.row(), 0);
    int itemCount = m_pTableViewSortFilterModelBase->rowCount(index);

    //先将该节点下所有子节点置为非选中状态
    for(int row = 0; row < itemCount; ++row)
    {
        QModelIndex Index_ = index.child(row,0);
        m_pTableViewSortFilterModelBase->setData(Index_,Qt::Unchecked,Qt::CheckStateRole);

    }

   //通过一下方式获取源model的item
   QModelIndex sourceIndex=m_pTableViewSortFilterModelBase->mapToSource(index);
   TreeItem *item=model->getItem(sourceIndex);
   openFiles.removeAll(item->getFilePath());

   //此行代码是为了保证uuidAndItem里的数据被正常移除
   model->removeRows(0,itemCount,sourceIndex);
   //从数据树中移除该节点
  model->removeRows(sourceIndex.row(),1);

}

void DataTreeWig::slotremoveAllNode()
{
    //先清除所有选中的节点
          //发一个立即执行的槽函数的信号
    emit signalActionClearAllWidget();
    //删除模型中所有数据
    model->clear();
    openFiles.clear();
}

void DataTreeWig::manageNode(QModelIndex index, bool flag)
{
    if(!m_pTableViewSortFilterModelBase->hasChildren(index))
    {
        return;
    }
    else
    {
        if(flag)
        {
            ui->treeView->collapse(index);
        }
        else
        {
            ui->treeView->expand(index);
        }
        int itemCount = m_pTableViewSortFilterModelBase->rowCount(index);
        for(int row = 0; row < itemCount; ++row)
        {
            QModelIndex Index = index.child(row,0);
            manageNode(Index, flag);
        }
    }
}

void DataTreeWig::clearCheckState()
{
    if(model)
    {
        model->clearCheckState();
        ui->treeView->viewport()->update();
    }
}

void DataTreeWig::cancelItemcheck(QString uuId)
{
   model->cancelItemcheck(uuId);
   ui->treeView->viewport()->update();
}



void DataTreeWig::on_treeView_doubleClicked(const QModelIndex &index)
{
    if(!index.parent().isValid())
    {
        return;
    }

   QModelIndex sourceIndex=m_pTableViewSortFilterModelBase->mapToSource(index);
   if(model->getItem(sourceIndex)->isChecked())
   {
       //model->setData(sourceIndex,Qt::Unchecked,Qt::CheckStateRole);
       //这样些不会造成节点收缩
       m_pTableViewSortFilterModelBase->setData(index,Qt::Unchecked,Qt::CheckStateRole);
   }
   else
   {
       //model->setData(sourceIndex,Qt::Checked,Qt::CheckStateRole);
       m_pTableViewSortFilterModelBase->setData(index,Qt::Checked,Qt::CheckStateRole);
   }

}

void DataTreeWig::openSelectItem()
{
     QModelIndexList indexList=ui->treeView->selectionModel()->selectedIndexes();
     foreach(auto index,indexList)
     {
         //增加提示信息
         QList<QVariantMap> resData;
         getCheckedItemData(resData);
         if(resData.count()>=20)
         {
             QMessageBox::information(nullptr,QStringLiteral("提示"),QStringLiteral("打开的曲线图不能超过20个"));
             return;
         }
         m_pTableViewSortFilterModelBase->setData(index,Qt::Checked,Qt::CheckStateRole);
     }


}

void DataTreeWig::closeSelectItem()
{
    QModelIndexList indexList=ui->treeView->selectionModel()->selectedIndexes();
    foreach(auto index,indexList)
    {
        m_pTableViewSortFilterModelBase->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
}

void DataTreeWig::locationChart()
{
    TreeItem *curItem=getModelItemByFilterIndex(ui->treeView->currentIndex());
    QString uuid=curItem->getNodeData().value(CHARTID).toString();
    emit signallocationChart(uuid);
}

void DataTreeWig::FullScreenWindow()
{
    //先将状态设置为选中状态
    QModelIndex curIndex=ui->treeView->currentIndex();
    if(m_pTableViewSortFilterModelBase->data(curIndex,Qt::CheckStateRole)==Qt::Unchecked)
    {
        m_pTableViewSortFilterModelBase->setData(curIndex,Qt::Checked,Qt::CheckStateRole);
    }

    TreeItem *curItem=getModelItemByFilterIndex(curIndex);
    QString uuid=curItem->getNodeData().value(CHARTID).toString();
    emit signalFullScreenWindow(uuid);
}

void DataTreeWig::setItemIsCheck(TreeItem *item, bool isCheck)
{

    if(item->parent()==nullptr)//顶层节点无需判定
    {
        return ;
    }
    TreeItem * parentItem=item->parent();
    for (int childIndex=0;childIndex<parentItem->childCount();childIndex++)
    {

        if((parentItem->child(childIndex)->isChecked()&&isCheck)
                ||(!(parentItem->child(childIndex)->isChecked()||isCheck))
                )
        {

            if(childIndex==(parentItem->childCount()-1))
            {
                parentItem->setCheckState(isCheck);
                //递归调用
                setItemIsCheck(parentItem,isCheck);
            }
        }
        else
        {
            break;
        }
    }
    ui->treeView->viewport()->update();
}

void DataTreeWig::getCheckedItemData(QList<QVariantMap> &resData)
{
    if(model)
    {
        model->getCheckedItemData(resData);
    }
}

TreeItem *DataTreeWig::getModelItemByFilterIndex(QModelIndex index)
{
    QModelIndex sourceIndex=m_pTableViewSortFilterModelBase->mapToSource(index);
    return  model->getItem(sourceIndex);
}
