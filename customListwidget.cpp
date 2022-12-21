#include "customListwidget.h"
#include <QApplication>
#include <QDrag>
#include <QKeyEvent>
#include <QMimeData>
#include "QDebug"


customListwidget::customListwidget(QWidget *parent) : QListWidget(parent)
{

    this->setAcceptDrops(true);
    this->setMouseTracking(true);
    this->setDragEnabled(true);
    this->setStyleSheet("QListWidget{border:1px solid black; color:black; }"
                        "QListWidget{background-color: rgb(160,160, 160); }"
                         "QListWidget::Item{padding-top:-2px; padding-bottom:-1px;}"
                         "QListWidget::Item:hover{background:skyblue;padding-top:0px; padding-bottom:0px; }"
                         "QListWidget::item:selected:!active{active{border-width:1px;background:white; }");


}

customListwidget::~customListwidget()
{
        qDebug()<<"enter";
}

// 接收放置后添加一项
void customListwidget::dropEvent(QDropEvent *event)
{
    if(event->mouseButtons() == Qt::LeftButton)
    {
        auto curItem = this->item(this->currentRow());//当前拖动的item

        //MdiChildWidgetBase *curWidget =(MdiChildWidgetBase *)this->itemWidget(curItem);//当前拖动的窗口
        MdiChildWidgetBase *curWidget =qobject_cast<MdiChildWidgetBase*>(this->itemWidget(curItem));
        QSize curWidget_size=QSize(curWidget->width(),curWidget->height());
        QPoint  endPos = event->pos();//得到鼠标移动后的坐标
        QListWidgetItem *itemRow = itemAt(endPos);//通过endPos获取鼠标位置所在的行
        int rowCount = row(itemRow);//移动后的item

        int targetCount = this->currentRow();
        if(rowCount == targetCount || rowCount == -1)
           return;
        MdiChildWidgetBase *targetWidget = (MdiChildWidgetBase *)this->itemWidget(this->item(rowCount));//拖动后的窗口

        QListWidgetItem *newitem = new QListWidgetItem();
        newitem->setData(Qt::UserRole + 1,QVariant::fromValue(curWidget->getCurWidgetId()));
        newitem->setSizeHint(curWidget_size);
        newitem->setBackground(QColor(Qt::white));
        QListWidgetItem *targetitem = new QListWidgetItem();
        targetitem->setData(Qt::UserRole + 1,QVariant::fromValue(targetWidget->getCurWidgetId()));
        targetitem->setSizeHint(curWidget_size);
        targetitem->setBackground(QColor(Qt::white));//不加这一段代码界面看起来会变小一点

        insertItem(rowCount,newitem);
        insertItem(targetCount,targetitem);
        this->setItemWidget(newitem,curWidget);
        delete curItem;
        this->setItemWidget(targetitem,targetWidget);
        delete itemRow;
         setSpacing(4);

        //by lk start
        items.insert(curWidget->getCurWidgetId(),newitem);
        items.insert(targetWidget->getCurWidgetId(),targetitem);
        //by lk end
    }
    else if(event->mouseButtons() == Qt::RightButton)
    {
        MdiChildWidgetBase *curWidget = (MdiChildWidgetBase *)this->itemWidget(this->item(this->currentRow()));//当前拖动的窗口
        if(curWidget)
        {
            QListWidgetItem *itemRow = itemAt(event->pos());//通过endPos获取鼠标位置所在的行
            if(itemRow)
            {
                int rowCount = row(itemRow);
                if(rowCount == -1 || rowCount == this->currentRow())
                {
                    return;
                }
                MdiChildWidgetBase *targetWidget = (MdiChildWidgetBase *)this->itemWidget(this->item(rowCount));//拖动后的窗口
                if(targetWidget)
                {

                    if((curWidget->curveNumber()+targetWidget->curveNumber())>8)//两边图表的曲线总数大于8时不让合并
                    {
                        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("曲线数量超上限，无法合并"));
                        QLOG_WARN()<<QStringLiteral("合并曲线图失败");
                        return;
                    }
                    QHash<QString,QCPGraph*>graphs= curWidget->getCurPlotGraph();
                    for (auto index=graphs.begin();index!=graphs.end();index++)
                    {

                        QCPDataRange dataRange = index.value()->data()->dataRange();
//                        QVector<QPointF> data;
//                        for(int k=dataRange.begin();k<dataRange.end();k++)
//                        {
//                            QString str_key = QString::number(index.value()->data()->at(k)->key);
//                            QString str_value = QString::number(index.value()->data()->at(k)->value);
//                            data.append(QPointF(index.value()->data()->at(k)->key,index.value()->data()->at(k)->value));
//                        }
                        QVector<QPointF> data=index.value()->property("tick").value<QVector<QPointF>>();
                        QVector<double>timePoint;
                        for(int k=dataRange.begin();k<dataRange.end();k++)
                        {
                                timePoint.append(index.value()->data()->at(k)->key);
                        }
                       targetWidget->setTreeItemData(index.key(),index.value()->name(),data,timePoint);
                       QLOG_INFO() <<QStringLiteral("合并%1曲线图成功").arg(index.value()->name());
                    }
                    QListWidgetItem *currentitem = this->takeItem(this->currentRow());
                    items.remove(curWidget->getCurWidgetId());
                    delete currentitem;
                }
            }
        }
    }
}

void customListwidget::resizeEvent(QResizeEvent *event)
{

     emit sigRearrange();
    return QListWidget::resizeEvent(event);
}

void customListwidget::addListItem(QString id,QListWidgetItem *item)
{
    this->addItem(item);
    items.insert(id,item);
}

void customListwidget::insertListItem(QString id,int row ,QListWidgetItem *item)
{
    this->insertItem(row,item);
    items.insert(id,item);
}

void customListwidget::removeListItem(TreeItem *item)
{
    //这里可以优化，暂时这样写看成果
    foreach(auto var, items.keys())
    {
        MdiChildWidgetBase *widget = qobject_cast<MdiChildWidgetBase *>(this->itemWidget(items.value(var)));
        if(widget)
        {
            if(item->getNodeData().value(CHARTID).toString() == var)
            {
                 if(widget->getCurPlotGraph().count()>1)//该表中的线大于1，只删除线，不删除表
                 {
                     widget->removeGraph(var);
                     linesIdAndTickTimeRatio.remove(var);
                     //另一条线自动升级为主线
                     QString UUid=widget->getCurPlotGraph().cbegin().key();
                     widget->setcurWidgetId(UUid);
                     //QListWidgetItem *item=this->takeItem(row(items.value(var)));
                     QListWidgetItem *listItem=items.value(var);
                     items.remove(var);
                     items.insert(UUid,listItem);
                     break;
                 }
                 else
                 {
                     QListWidgetItem *currentitem = this->takeItem(row(items.value(var)));
                     items.remove(var);
                     linesIdAndTickTimeRatio.remove(var);
                     delete currentitem;
                     break;
                 }
            }
            //还要判断曲线图中是否存在该线
            else
            {
                QHash<QString,QCPGraph*>ccc=widget->getCurPlotGraph();
                if(widget->getCurPlotGraph().keys().contains(item->getNodeData().value(CHARTID).toString()))
                {
                    widget->removeGraph(item->getNodeData().value(CHARTID).toString());
                    linesIdAndTickTimeRatio.remove(item->getNodeData().value(CHARTID).toString());
                    break;
                }
            }
        }
    }
}

void customListwidget::removeListItem(QString id)
{
    foreach (auto var, items)
    {
        if(id == var->data(Qt::UserRole + 1).toString())
        {
            QListWidgetItem *currentitem = this->takeItem(row(var));
            linesIdAndTickTimeRatio.remove(id);
            items.remove(id);
            delete currentitem;
        }
    }
}

MdiChildWidgetBase *customListwidget::getCurWidgetId(QString id)
{
    if(!items.isEmpty())
    {
        MdiChildWidgetBase *widget = dynamic_cast<MdiChildWidgetBase *>(this->itemWidget(items.value(id)));
        return widget;
    }
    return nullptr;
}

QHash<QString, QListWidgetItem *> customListwidget::getItems()
{
    return items;
}

QListWidgetItem *customListwidget::getCurItem(QString id)
{
    foreach (auto var, items.keys())
    {
        if(var == id)
        {
            return items.value(var);
        }
    }
    return nullptr;
}

void customListwidget::locationChart(QString id)
{
   QListWidgetItem *item =items.value(id);
   if(item)
   {
       setCurrentItem(item,QItemSelectionModel::ClearAndSelect);
   }

}

void customListwidget::addGraphIdAndTickTimeRatio(QString id, double TickTimeRatio)
{
    linesIdAndTickTimeRatio.insert(id,TickTimeRatio);
}

QHash<QString, double> customListwidget::getAllGraphIdAndTickTimeRatio()
{
    return linesIdAndTickTimeRatio;
}

QList<MdiChildWidgetBase *> customListwidget::getBeginEndItem()
{
    QList<MdiChildWidgetBase *> items;
    QModelIndex beginIndex = indexAt(QPoint(4,4));//当前窗口的起始位置
    if(beginIndex.isValid())
    {
        int begin = beginIndex.row();
        int end = horstationMax * INIT_HORSTATION;
        for (int index = begin;index <=  (begin + end) ;index++)
        {
            MdiChildWidgetBase *widget = (MdiChildWidgetBase *)this->itemWidget(this->item(index));
            if(widget)
                items.append(widget);
        }
        return items;
    }
    else
    {
        return items;
    }
}

void customListwidget::setWidgethorstationMax(int maxNum)
{
    horstationMax = maxNum;
}


