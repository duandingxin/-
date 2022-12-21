#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

struct MonitorData
{
    QString name;
    QVector<QPointF> pointContainer;//x为Tick值，Y为信号的值
    QVector<double>timePoint;//Tick对应的时间点，其数量和索引与pointContainer的X值对应，没有放在一起是为了兼容以前的代码
};

Q_DECLARE_METATYPE(MonitorData)

class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    /**
     * @brief appendChild   添加子节点
     * @param child         子节点对象
     */
    void appendChild(TreeItem *child);

    /**
     * @brief child         获取子节点
     * @param row           子节点索引
     * @return
     */
    TreeItem *child(int row);

    /**
     * @brief childCount    子节点总数
     * @return
     */
    int childCount() const;

    /**
     * @brief columnCount   节点的列数
     * @return
     */
    int columnCount() const;

    /**
     * @brief data          节点的某列数据
     * @param column        列的索引
     * @return
     */
    QVariant data(int column) const;

    /**
     * @brief row       当前节点下所有子节点的数量
     * @return
     */
    int row() const;

    /**
     * @brief parent    当前节点的父节点
     * @return
     */
    TreeItem *parent();

    /**
     * @brief m_checked 当前节点是否被选中的状态
     */
	bool m_checked;

    /**
     * @brief isChecked 当前节点是否被选中
     * @return
     */
	bool isChecked();
    /**
     * @brief setCheckState     设置当前节点选中状态
     * @param state
     */
    void setCheckState(bool state);

    /**
     * @brief read
     * @param monitor_file
     */
    bool read(const QString &monitor_file);
    /**
     * @brief readData 读取的执行函数
     * @param monitor_file
     * @return
     */
    bool readData(const QString &monitor_file);

    /**
     * @brief getFileName   获取文件名称
     * @return
     */
    const QString &getFileName();

    /**
     * @brief getTickNs     获取tick数
     * @return
     */
    double getTickNs() const;

    /**
     * @brief getMonitorDataContainer   获取文件中所有的（x,y）数据
     * @return
     */
    QList<MonitorData> getMonitorDataContainer() const;

    /**
     * @brief getMonitorData        获取当前节点的(x,y)数据
     * @return
     */
    MonitorData getMonitorData();

    /**
     * @brief setMonitorData        设置当前节点的(x,y)数据
     * @param data
     */
    void setMonitorData(MonitorData& data);

    /**
     * @brief setFileName       设置文件名称
     * @param name
     */
    void setFileName(QString name);

    /**
     * @brief settickNs         设置tick数
     * @param number
     */
    void settickNs(double number);

    /**
     * @brief setNodeData   设置节点数据
     * @param data          数据
     */
    void setNodeData(QVariantMap data);

    /**
     * @brief getNodeData   获取当前节点所有的数据
     * @return
     */
    QVariantMap getNodeData();
    /**
     * @brief removeChildren 删除该节点下指定孩子节点
     * @param row 起始行
     * @param count 删除数量
     * @return 是否删除成功
     */
    bool removeChildren(int row,int count,QHash<QString,TreeItem*>&uuidAndItem);


    /**
     * @brief setfilePath 设置文件的完整路径（顶层节点特有）
     * @param filepath
     */
    void setfilePath(QString filepath);
    /**
     * @brief getFilePath 获取文件的完整路径（顶层节点特有）
     * @return 文件完整路径
     */
    QString getFilePath();

    /**
     * @brief clearTreeData 清空数据
     */
    void clearTreeData();

private:
    /**
     * @brief childItems        当前节点的所有子节点
     */
    QList<TreeItem*> childItems;

    /**
     * @brief itemData          当前节点的数据
     */
    QList<QVariant> itemData;

    /**
     * @brief parentItem    当前节点的父节点
     */
    TreeItem *parentItem;

    /**
     * @brief m_fileName    文件名称
     */
    QString m_fileName;

    /**
     * @brief m_filepath （顶层节点属性，文件的完整路径，防止文件被多次打开）
     */
    QString  m_filepath;

    /**
     * @brief m_tickNs
     */
    double m_tickNs; // tick纳秒

    /**
     * @brief m_MonitorDataContainer    root节点下所有的子节点数据
     */
    QList<MonitorData> m_MonitorDataContainer;

    /**
     * @brief m_MonitorData     单个节点的(x,y)数据
     */
    MonitorData m_MonitorData;

    /**
     * @brief m_NodeData    存储自身节点的所有数据（键值对）
     */
    QVariantMap m_NodeData;
};

#endif
