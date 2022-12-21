#ifndef TABLEVIEWSORTFILTERMODELBASE_H
#define TABLEVIEWSORTFILTERMODELBASE_H

#include <QObject>
#include <QSortFilterProxyModel>

//本类是TableView的排序过滤类的基类,如果不指定过滤时匹配的列，过滤时会查找TableView所有列符合条件的项
//类型MultiColumnOrder表示多关键字段的排序方式定义
//QList内的QPair类型表示一个排序字段的信息，整数为字段的列号，Qt::SortOrder定义了排序方式是升序还是降序
typedef QList<QPair<int, Qt::SortOrder> > TMultiColumnOrder;

class TableViewSortFilterModelBase : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TableViewSortFilterModelBase(QObject *parent = 0);
    ~TableViewSortFilterModelBase();

    void setMultiColumnOrders(const TMultiColumnOrder& orders);
    TMultiColumnOrder multiColumnOrder() const;
    int setFilterColumn(int modelType, int column);

protected:
    //过滤需要显示的行
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    //过滤需要显示的列
    bool filterAcceptsColumn(int source_column, const QModelIndex & source_parent) const;
    //排列方式
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

protected:
    TMultiColumnOrder m_orders;
    int m_filterColumn;         //指定过滤时匹配的列，如果不指定，匹配所有的列
};

#endif // TABLEVIEWSORTFILTERMODELBASE_H
