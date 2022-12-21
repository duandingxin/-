#include <QFileInfo>
#include <QStringList>
#include <QTextStream>

#include "treeitem.h"
#include "datavisualizationanalysislib_global.h"
#include "waittingdlg.h"
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QApplication>


#define StartPos 2
#define TickPos 1
#define TimePos 2

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
    // 默认全部不选择
    m_checked = false;
}

TreeItem::~TreeItem()
{
    m_MonitorData.timePoint.clear();
    m_MonitorData.pointContainer.clear();
    m_NodeData.clear();
    itemData.clear();
    m_MonitorDataContainer.clear();
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

bool TreeItem::isChecked()
{
	return m_checked;
}

bool TreeItem::read(const QString &monitor_file)
{
    WaittingDlg dlg;
    dlg.setWindowModality(Qt::ApplicationModal);
    dlg.show();

   QFuture<bool>future=QtConcurrent::run(this,&TreeItem::readData,monitor_file);

   while (future.isRunning())
   {
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
   }

   return future.result();
}

bool TreeItem::readData(const QString &monitor_file)
{
    m_MonitorDataContainer.clear();
    QFile file(monitor_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QFileInfo fileinfo(monitor_file);
    m_fileName = fileinfo.completeBaseName();

    QTextStream in(&file);
    in.setCodec("GBK");
    QString line = in.readLine();
    QStringList titles = line.split("," , QString::KeepEmptyParts);
    if(titles.size() < 3) return false;
    QString data_line = in.readLine();
    if(data_line.split("," , QString::KeepEmptyParts).size()<2)
    {
        return  false;
    }
    QVector<QVector<QPointF>> total_data(data_line.split("," , QString::KeepEmptyParts).size()-StartPos, QVector<QPointF>());
    QVector<QVector<double>>total_data_time(data_line.split("," , QString::KeepEmptyParts).size()-StartPos, QVector<double>());
    while (!data_line.isNull())
    {
        QStringList data = data_line.split("," , QString::KeepEmptyParts);

        if(data.size() <3) continue;
        for (int i = StartPos; i < data.size(); ++i)
        {
            QString x = data.at(TickPos);
            QString y = data.at(i);
            QString time=data.at(TimePos);
            if(y=="-" || y == ""){
                continue;
            }
            total_data[i-StartPos].append(QPointF(x.toULongLong(), y.toDouble()));
            total_data_time[i-StartPos].append(time.toULongLong());
        }

        data_line = in.readLine();
    }



    m_tickNs = 0;

    for (int i = StartPos; i < titles.size(); ++i)
    {
        if(i == StartPos && total_data[i-StartPos].size() > 2)
        {
            double tick_interval = total_data[i-StartPos].at(1).x() - total_data[i-StartPos].at(0).x();//tick
            double time_interval = total_data[i-StartPos].at(1).y() - total_data[i-StartPos].at(0).y();//tick
            m_tickNs = time_interval/tick_interval;
        }
        if(titles.at(i).isNull() || titles.at(i) == "")
            continue;
        MonitorData monitorData;
        monitorData.name = titles.at(i);
        monitorData.pointContainer = total_data[i-StartPos];
        monitorData.timePoint=total_data_time[i-StartPos];
        m_MonitorDataContainer.append(monitorData);
    }

    if(m_MonitorDataContainer.isEmpty())
    {
        return false;
    }
    else
    {
        return  true;
    }
}

const QString &TreeItem::getFileName()
{
    return m_fileName;
}

double TreeItem::getTickNs() const
{
    return m_tickNs;
}

QList<MonitorData> TreeItem::getMonitorDataContainer() const
{
    return m_MonitorDataContainer;
}

MonitorData TreeItem::getMonitorData()
{
    return m_MonitorData;
}

void TreeItem::setMonitorData(MonitorData &data)
{
    m_MonitorData = data;
}

void TreeItem::setFileName(QString name)
{
    m_fileName = name;
}

void TreeItem::settickNs(double number)
{
    m_tickNs = number;
}

void TreeItem::setNodeData(QVariantMap data)
{
    m_NodeData = data;
}

QVariantMap TreeItem::getNodeData()
{
    return m_NodeData;
}

bool TreeItem::removeChildren(int row, int count, QHash<QString, TreeItem *> &uuidAndItem)
{

    int oldCount=childItems.count();
    for(int index=0;index<count;index++)
    {
        //移除
        QString uuid=childItems.at(row)->getNodeData().value(CHARTID).toString();
        //释放内存
        delete childItems.at(row);
        uuidAndItem.remove(uuid);
        childItems.removeAt(row);
    }
    int newCount=childItems.count();
    int diff=oldCount-newCount;
    if(diff==count)
    {
        return  true;
    }
    else
    {
        return  false;
    }
}

void TreeItem::setfilePath(QString filepath)
{
    m_filepath=filepath;
}

QString TreeItem::getFilePath()
{
    return m_filepath;
}

void TreeItem::clearTreeData()
{
    for(int index=0;index<childItems.count();index++)
    {
        //释放内存
        delete childItems.at(index);
        childItems.removeAt(index);
    }
    itemData.clear();
}

void TreeItem::setCheckState(bool state)
{
    m_checked = state;
}
