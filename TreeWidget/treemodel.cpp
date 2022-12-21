#include <QtGui>
#include "treemodel.h"
#include <QMessageBox>
#include "QsLog.h"
#include <QProgressBar>
#include "waittingdlg.h"


TreeModel::TreeModel(QObject *parent):
    QAbstractItemModel(parent)
    ,rootItem(nullptr)
{
    QList<QVariant> rootData;
    rootData << QStringLiteral("文件名称");
    rootItem = new TreeItem(rootData);
    checkItems.clear();
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role==Qt::CheckStateRole && index.column()==0)
	{
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		if (value==Qt::Unchecked)
		{
            if(checkItems.contains(item->getNodeData().value(CHARTID).toString()))
            {
                checkItems.remove(item->getNodeData().value(CHARTID).toString());
            }
			item->setCheckState(false);
			emit(dataChanged(index, index));
		}
		else if(value==Qt::Checked)
		{
            if(checkItems.count() >= MAX_NODE)
            {
                //增加提示信息
                QMessageBox::information(nullptr,QStringLiteral("提示"),QStringLiteral("打开的曲线图不能超过20个"));
                return true;
            }
            else
            {
                checkItems.insert(item->getNodeData().value(CHARTID).toString(),item);
                item->setCheckState(true);
                emit(dataChanged(index, index));
            }
		}
		int childCount = rowCount(index);
		if (childCount > 0)
		{
			//判断是否有子节点
			for (int i=0; i<childCount; i++)
			{
                if(checkItems.count() >= MAX_NODE)
                {
                    QMessageBox::information(nullptr,QStringLiteral("提示"),QStringLiteral("打开的曲线图不能超过20个"));
                    return  true;
                }
				//获得子节点的index
				QModelIndex child = this->index(i, 0, index);
				//递归，改变子节点的checkbox状态
				setData(child, value, Qt::CheckStateRole);
			}
		}
	}

	return true;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

	//判断显示的对象是checkbox，并且位于第一列
	if (role==Qt::CheckStateRole && index.column()==0)
		return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

	if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力  
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;  

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::loadExcelModelData(const QString &monitorFile)
{
    if(monitorFile.isEmpty())
        return;
    if(!rootItem->read(monitorFile))
    {
        QMessageBox::information(nullptr,QStringLiteral("提示"),QStringLiteral("数据读取失败或无数据"));
                return;
    }



    beginResetModel();
    QString fileName = rootItem->getFileName();
    QList<QVariant> data;
    data << fileName;
    TreeItem *ItemNode = new TreeItem(data, rootItem);

    //by likun start
    //记录文件路径
    ItemNode->setfilePath(monitorFile);
    //by likun end


    foreach (auto varInfo, rootItem->getMonitorDataContainer())
    {

        QList<QVariant> dataName;
        dataName << varInfo.name;
        TreeItem *childItem = new TreeItem(dataName,ItemNode);
        if(childItem)
        {
            QVariantMap map;
            map.insert(CHARTNAME, varInfo.name);                  //图表名称
            map.insert(CHARTDATA, QVariant::fromValue(varInfo.pointContainer));  //曲线数据
            map.insert(FILENAME, fileName);                       //文件名
            map.insert(TICK_NS, rootItem->getTickNs());
            map.insert(CHARTID, QUuid::createUuid().toString());
            map.insert(TIME_POINT,QVariant::fromValue(varInfo.timePoint));//曲线数据
            //by lk start
            //记录tick和time的比值
            static double tickTimeRatio=0.0;
            if(varInfo.name=="time")//time就是第一个被遍历到的
            {
                if(varInfo.pointContainer.at(0).x()!=0.0)//第一个数据可能为零
                {
                    tickTimeRatio=varInfo.pointContainer.at(0).x()/varInfo.pointContainer.at(0).y();
                }
                else if(varInfo.pointContainer.count()>=1)
                {
                    tickTimeRatio=varInfo.pointContainer.at(1).x()/varInfo.pointContainer.at(1).y();
                }
                else
                {
                  QLOG_WARN() << QStringLiteral("文件%1加载失败").arg(fileName);
                }
            }
            //暂时还要用，别删
            map.insert(TICKTIMERATIO,tickTimeRatio);
            //by lk end


            childItem->setNodeData(map);
            ItemNode->appendChild(childItem);
            uuidAndItem.insert(map.value(CHARTID).toString(),childItem);
        }

    }
    rootItem->appendChild(ItemNode);
    endResetModel();
}

void TreeModel::loadXmlModelData(const QString& workSpacePath,const QString &vvFile)
{
    if(vvFile.isEmpty())
        return;
//    vv_preview_data_.reset(new VVPreviewData(workSpacePath, vvFile, this));
//    WaittingDlg dlg;
//    connect(vv_preview_data_.data(), &VVPreviewData::sigDataOk,&dlg,&WaittingDlg::close);
//    connect(vv_preview_data_.data(), &VVPreviewData::sigDataOk, this, &TreeModel::slotLoadData);
//    vv_preview_data_->start();
//    dlg.setWindowModality(Qt::ApplicationModal);
//    dlg.show();
}

void TreeModel::slotLoadData(QString filePath,long long tick_ns_)
{

//    MsgData_t msg_data = vv_preview_data_->getMsgData();
//    QString base_name = vv_preview_data_->getBaseName();
//    if(msg_data.isEmpty())//无数据
//    {
//        QMessageBox::information(nullptr,QStringLiteral("提示"),QStringLiteral("数据读取失败或无数据"));
//        QLOG_WARN() << QStringLiteral("文件%1加载失败").arg(base_name);
//        return;
//    }

//    beginResetModel();
//    QList<QVariant> data;
//    data << base_name;
//    TreeItem *ItemNode = new TreeItem(data, rootItem);
//    ItemNode->setfilePath(filePath);
//    //by likun start
//    double tickTimeRatio=1.0/tick_ns_;

//    //by likun end


//    for(auto iter = msg_data.begin(); iter != msg_data.end(); ++iter)
//    {
//        QList<QVariant> data;
//        data << iter.key();
//        TreeItem * item = new TreeItem(data,ItemNode);
//        ItemNode->appendChild(item);

//        auto& sig_data = iter.value();
//        for(auto sig_iter = sig_data.begin(); sig_iter != sig_data.end(); ++sig_iter)
//        {
//            QList<QVariant> data;
//            data << sig_iter.key();
//            TreeItem * sub_item = new TreeItem(data,item);

//            QVector<double>timePoint;
//            foreach(auto point,sig_iter.value().data_)
//            {
//                timePoint.append(point.x()*tick_ns_);
//            }
//            QVariantMap map;
//            map.insert("name", sig_iter.key());     //信号名
//            map.insert("id", iter.key());           //msgid
//            map.insert(FILENAME, base_name);      //文件名
//            QString diagram_name = base_name +"/" + iter.key() + "/" + sig_iter.key();
//            map.insert(CHARTNAME, diagram_name);  //chart的title
//            map.insert(CHARTDATA, QVariant::fromValue(sig_iter.value().data_));   //端口(信号数据)
//            map.insert(TICK_NS, vv_preview_data_->getTick_ns());
//            map.insert(CHARTID, QUuid::createUuid().toString());
//            //暂时还要用，别删
//            map.insert(TICKTIMERATIO,tickTimeRatio);
//            map.insert(TIME_POINT,QVariant::fromValue(timePoint));
//            sub_item->setNodeData(map);
//            item->appendChild(sub_item);
//            uuidAndItem.insert(map.value(CHARTID).toString(),sub_item);
//        }
//    }
//    rootItem->appendChild(ItemNode);
//    endResetModel();
}

void TreeModel::setCheckedStrList(TreeItem *item, QList<QVariantMap> &checkedStrList)
{
	if (item->isChecked())
	{

        checkedStrList.append(item->getNodeData());
	}

	int childCount = item->childCount();
	if (childCount > 0)
	{
		// 判断是否有子节点
		for (int i=0; i<childCount; i++)
		{
			TreeItem *child = item->child(i);
			// 递归调用setCheckedStrList;
			setCheckedStrList(child, checkedStrList);
		}
	}
}

void TreeModel::getCheckedItemData(QList<QVariantMap>& resData)
{
    QList<QVariantMap> checkedStrList;
	setCheckedStrList(rootItem, checkedStrList);
	
    foreach (auto varItem, checkedStrList)
    {
        resData.append(varItem);
    }
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

TreeItem *TreeModel::getItem(QString uuid)
{
    return   uuidAndItem.value(uuid);
}

void TreeModel::cancelItemcheck(QString uuid)
{
    TreeItem *item=uuidAndItem.value(uuid);
    if(item)
    {
        item->setCheckState(false);
    }
}

void TreeModel::manageNodeCheckState(TreeItem *index, bool flag)
{
    if(index == nullptr)
        return;
    if(flag)
    {
        index->setCheckState(flag);
    }
    else
    {
        index->setCheckState(flag);
    }
    int itemCount = index->childCount();

    // 判断是否有子节点
    for (int i=0; i<itemCount; i++)
    {
        TreeItem *child = index->child(i);
        //递归调用
        manageNodeCheckState(child, flag);
    }
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{

    beginResetModel();
    bool isRemoreSuccess=false;
    if(!parent.isValid())
    {
        isRemoreSuccess=  rootItem->removeChildren(row,1,uuidAndItem);
    }
    else
    {
        TreeItem *item= rootItem->child(parent.row());
        isRemoreSuccess=  item->removeChildren(row,count,uuidAndItem);
    }
    endResetModel();
    return  isRemoreSuccess;
}

bool TreeModel::clear()
{
    if(rootItem)
    {
        beginResetModel();
        rootItem->removeChildren(0,rootItem->childCount(),uuidAndItem);
        checkItems.clear();
        endResetModel();
        return  true;
    }
    else
    {
        return  false;
    }

}

void TreeModel::clearCheckState()
{
    checkItems.clear();
    manageNodeCheckState(rootItem,false);
}
