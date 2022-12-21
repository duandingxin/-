#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <QList>
#include <QPersistentModelIndex>

#include <VVPreview/vvpreviewdata.h>
#include "datavisualizationanalysislib_global.h"

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    /**
     * @brief data
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief flags
     * @param index
     * @return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @brief headerData
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;

    /**
     * @brief index
     * @param row
     * @param column
     * @param parent
     * @return
     */
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief parent
     * @param index
     * @return
     */
    QModelIndex parent(const QModelIndex &index) const;

    /**
     * @brief rowCount
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief columnCount
     * @param parent
     * @return
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief setData
     * @param index
     * @param value
     * @param role
     * @return
     */
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);  

    /**
     * @brief setCheckedStrList     获取被勾选的节点，并且获取节点的数据写入到checkedStrList中
     * @param item                  根节点
     * @param checkedStrList        存储数据名称的容器
     */
    void setCheckedStrList(TreeItem *item, QList<QVariantMap> &checkedStrList);

    /**
     * @brief getCheckedItemData    获取被勾选的数据
     * @param resStr                被勾选的节点名称
     */
    void getCheckedItemData(QList<QVariantMap> &resData);

    /**
     * @brief loadModelData     加载文件数据
     * @param monitor_file      文件路径名称
     */
    void loadExcelModelData(const QString &monitorFile);

    /**
     * @brief loadXmlModelData
     * @param vvFile
     */
    void loadXmlModelData(const QString &workSpacePath, const QString &vvFile);

    /**
     * @brief getItem
     * @param index
     * @return
     */
    TreeItem *getItem(const QModelIndex &index) const;


    /**
     * @brief getItem
     * @param uuid item的uuid
     * @return  对应item的指针
     */
    TreeItem *getItem(QString uuid);

    /**
     * @brief cancelItemcheck 取消节点的选中
     * @param uuid 节点的uuid
     */
    void  cancelItemcheck(QString uuid);


    /**
     * @brief clearCheckState   清空导航树中所有的节点
     */
    void clearCheckState();

    /**
     * @brief manageNodeCheckState  设置节点是否被勾选
     * @param index                 节点对象
     * @param flag                  勾选状态
     */
    void manageNodeCheckState(TreeItem *index, bool flag);
    /**
     * @brief removeRows 删除节点下指定子节点
     * @param row    起始行
     * @param count  删除数量
     * @param parent 父节点
     * @return 是否删除成功
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;


    /**
     * @brief clear 清理整个模型的数据
     * @return 是否清理成功
     */
    bool  clear();

private slots:

    /**
     * @brief slotLoadData  在线程中解析完XML数据发送信号触发的槽函数
     */
    void slotLoadData(QString filePath, long long tick_ns_);

private:

    /**
     * @brief rootItem          根节点
     */
    TreeItem *rootItem;

    /**
     * @brief uuidAndItem key-uuid,value--TreeItem*
     */
    QHash<QString,TreeItem*>uuidAndItem;


    /**
     * @brief vv_preview_data_
     */
    QSharedPointer<VVPreviewData> vv_preview_data_;

    /**
     * @brief checkItems    存储所有勾选的item
     */
    QHash<QString,TreeItem*> checkItems;
};

#endif
