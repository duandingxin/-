#include "TableViewSortFilterModelBase.h"
#include <QVariant>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QDateTime>


TableViewSortFilterModelBase::TableViewSortFilterModelBase(QObject *parent) : QSortFilterProxyModel(parent)
{
    this->setFilterRole (Qt::UserRole);
    m_filterColumn = -1;
}

TableViewSortFilterModelBase::~TableViewSortFilterModelBase()
{
}

//设置多个关键字段排序的关键字段
void TableViewSortFilterModelBase::setMultiColumnOrders(const TMultiColumnOrder &orders)
{
    m_orders = orders;
}

//获取多个关键字段排序的关键字段
TMultiColumnOrder TableViewSortFilterModelBase::multiColumnOrder() const
{
    return m_orders;
}

/**
 * @brief TableViewSortFilterModelBase::setFilterColumn 设置过滤列
 * @param modelType         modelType-模型类型：0-逻辑表模型，1-关联表模型，2-闭锁方案模型
 * @param column            过滤列
 * @return
 */
int TableViewSortFilterModelBase::setFilterColumn(int modelType, int column)
{
	switch (modelType)
	{
	case 0:		//逻辑表模型
	case 1:		//关联表模型
		m_filterColumn = 2;		//主编号  第2列
		break;
	case 2:		//闭锁方案模型
		{
			switch (column)
			{
			case 0:		//设备编号
				m_filterColumn = 1;	
				break;
			case 1:		//设备类型
				m_filterColumn = 2;	
				break;
			case 2:		//锁具类型
				m_filterColumn = 3;	
				break;
			case 3:		//锁码类型
				m_filterColumn = 4;	
				break;
			default:
				m_filterColumn = column;
				break;
			}
		}
		break;
	default:
        m_filterColumn = column;//默认主编号 第2列
		break;
	}

    return 0;
}

//过滤需要显示的行
bool TableViewSortFilterModelBase::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QAbstractItemModel *pModel = sourceModel();
    if(NULL == pModel)  return false;

    //如果本节点的父节点可见，那么本节点也要可见
    {
        QModelIndex source_index = sourceParent;
        while (source_index.isValid())
        {
            bool isContains = pModel->data(source_index).toString().contains(filterRegExp());
            if(isContains)  return true;

            source_index = sourceModel()->parent(source_index);
        }
    }

    //判断本身是否可见
    QModelIndex index;
    bool isContains = false;
    int columnCount = pModel->columnCount();
    for(int i=0;i<columnCount;i++)
    {
        index = pModel->index(sourceRow, i, sourceParent);
        if (index.column() != m_filterColumn && -1 != m_filterColumn)	continue;	//根据所选过滤类型选择需要进行过滤的列

        isContains = pModel->data(index).toString().contains(filterRegExp());
        if(isContains)  return true;
    }

    //如果本节点的子节点可见，那么本节点也要可见
    {
        // check all decendant's
        QModelIndex source_index = sourceModel()->index(sourceRow, 0, sourceParent);
        if(!source_index.isValid())
        {
            return false;
        }

        for (int k=0; k<sourceModel()->rowCount(source_index); k++)
        {
            if (filterAcceptsRow(k, source_index))
            {
                return true;
            }
        }
    }

    return false;
}

//过滤需要显示的列
bool TableViewSortFilterModelBase::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    //if(source_column == 3)//屏蔽第4列显示
    //return false;
    return true;
}

//排序方法
bool TableViewSortFilterModelBase::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    //采用基类的比较方法
    return QSortFilterProxyModel::lessThan(left,right);

    //以下自定义排序方法
    //>>>>>>>>>>>>>>>>>>>>>>>>>>
    /*
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if (leftData.type() == QVariant::DateTime)
    {
        return leftData.toDateTime() < rightData.toDateTime();
    }
    else
    {
        bool ok;
        double leftDouble = leftData.toDouble(&ok);
        double rightDouble = rightData.toDouble(&ok);
        return leftDouble < rightDouble;

        //Email比较
//        QRegExp *emailPattern = new QRegExp("([\\w\\.]*@[\\w\\.]*)");

//        QString leftString = leftData.toString();
//        if(left.column() == 1 && emailPattern->indexIn(leftString) != -1)
//            leftString = emailPattern->cap(1);

//        QString rightString = rightData.toString();
//        if(right.column() == 1 && emailPattern->indexIn(rightString) != -1)
//            rightString = emailPattern->cap(1);

//        return QString::localeAwareCompare(leftString, rightString) < 0;
    }*/
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //以下实现多个关键字排序方法
    QPair<int, Qt::SortOrder> colorder;
    int c;
    QVariant l, r;
    QModelIndex idxLeft, idxRight;
    // loop for all ordered columns
    foreach(colorder, m_orders)
    {
        c = colorder.first;
        idxLeft = left.model()->index(left.row(), c, left.parent());
        idxRight = right.model()->index(right.row(), c, right.parent());

        // read value
        if (colorder.second==Qt::AscendingOrder)
        {
            // compare l<r while Ascending
            l = idxLeft.data(sortRole());
            r = idxRight.data(sortRole());
        }
        else
        {
            // compare r<l while Descending
            r = idxLeft.data(sortRole());
            l = idxRight.data(sortRole());
        }

        switch (l.userType())
        {
        case QVariant::Invalid:
            return (r.type() == QVariant::Invalid);
        case QVariant::Int:
            if (l.toInt() < r.toInt())
                return true;
            else if (l.toInt() > r.toInt())
                return false;
            break;
        case QVariant::UInt:
            if (l.toUInt() < r.toUInt())
                return true;
            else if (l.toUInt() > r.toUInt())
                return false;
            break;
        case QVariant::LongLong:
            if (l.toLongLong() < r.toLongLong())
                return true;
            else if (l.toLongLong() > r.toLongLong())
                return false;
            break;
        case QVariant::ULongLong:
            if (l.toULongLong() < r.toULongLong())
                return true;
            else if (l.toULongLong() > r.toULongLong())
                return false;
            break;
        case QMetaType::Float:
            if (l.toFloat() < r.toFloat())
                return true;
            else if (l.toFloat() > r.toFloat())
                return false;
            break;
        case QVariant::Double:
            if (l.toDouble() < r.toDouble())
                return true;
            else if (l.toDouble() > r.toDouble())
                return false;
            break;
        case QVariant::Char:
            if (l.toChar() < r.toChar())
                return true;
            else if (l.toChar() > r.toChar())
                return false;
            break;
        case QVariant::Date:
            if (l.toDate() < r.toDate())
                return true;
            else if (l.toDate() > r.toDate())
                return false;
            break;
        case QVariant::Time:
            if (l.toTime() < r.toTime())
                return true;
            else if (l.toTime() > r.toTime())
                return false;
            break;
        case QVariant::DateTime:
            if (l.toDateTime() < r.toDateTime())
                return true;
            else if (l.toDateTime() > r.toDateTime())
                return false;
            break;
        case QVariant::String:
        default:
            if (isSortLocaleAware())
            {
                c = l.toString().localeAwareCompare(r.toString());
                if (c<0)
                    return true;
                else if (c>0)
                    return false;
            }
            else
            {
                c = l.toString().compare(r.toString(), sortCaseSensitivity());
                if (c<0)
                    return true;
                else if (c>0)
                    return false;
            }
        }
    }
    return true;
}

