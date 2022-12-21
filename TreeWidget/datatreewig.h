#ifndef DATATREEWIG_H
#define DATATREEWIG_H

#include <QWidget>
#include "TableViewSortFilterModelBase.h"
#include "treemodel.h"
#include <QObject>

namespace Ui {
class DataTreeWig;
}

class DataTreeWig : public QWidget
{
    Q_OBJECT

public:
    explicit DataTreeWig(QWidget *parent = nullptr);
    ~DataTreeWig();

    /**
     * @brief setMonitorFile    传入excel文件解析加载数据到节点中
     * @param monitor_file      excel文件
     */
    void setMonitorFile(const QString &monitorFile);

    /**
     * @brief setVVFile     传入测试脚本文件加载解析到节点中
     * @param vvfile
     */
    void setVVFile(const QString &workSpacePath, const QString &vvfile);

    /**
     * @brief setExpandAll  展开导航树节点
     */
    void setExpandAll();

    /**
     * @brief manageNode    管理节点,显示/隐藏节点
     * @param index
     * @param flag
     */
    void manageNode(QModelIndex index, bool flag);

    /**
     * @brief clearCheckState   清空导航树中所有的节点
     */
    void clearCheckState();


    /**
     * @brief cancelItemcheck 取消节点的选中状态
     * @param uuId 节点的uuid
     */
    void cancelItemcheck(QString uuId);


signals:
    /**
     * @brief signalNodeItem    勾选节点，发送创建图表窗口
     */
    void signalNodeItem(TreeItem *);

    void  signalActionClearAllWidget();

    /**
     * @brief signallocationChart 定位到指定曲线图
     * @param uuid 选中item的uuid
     */
    void signallocationChart(QString uuid);

    /**
     * @brief signalFullScreenWindow 将指定曲线图满屏显示（若该曲线图没有打开，会先打开该曲线图）
     * @param uuid 选中item的uuid
     */
    void signalFullScreenWindow(QString uuid);
private slots:
    /**
     * @brief slotDataChanged       勾选节点，触发槽函数
     * @param top
     * @param bottom
     */
    void slotDataChanged(const QModelIndex &top,const QModelIndex &bottom);

    /**
     * @brief on_lineEdit_textChanged   搜索框，显隐节点
     * @param arg1
     */
    void on_lineEdit_textChanged(const QString &arg1);

    /**
     * @brief slotTreeViewDataMenu      导航树右键菜单
     * @param pos
     */
    void slotTreeViewDataMenu(const QPoint &pos);

    /**
     * @brief slotExpandNode        展开当前选择的节点
     */
    void slotExpandNode();

    /**
     * @brief slotPackUpNode        收起当前选择的节点
     */
    void slotPackUpNode();
    /**
     * @brief slotremoveNode       删除当前节点（只有顶层节点才有此功能）
     */
    void slotremoveNode();

    /**
     * @brief slotremoveAllNode 删除所有节点
     */
    void slotremoveAllNode();

    void on_treeView_doubleClicked(const QModelIndex &index);


    /**
     * @brief openSelectItem 打开选中item的曲线图
     */
    void openSelectItem();

    /**
     * @brief closeSelectItem 关闭选中item的曲线图
     */
    void closeSelectItem();

    /**
     * @brief locationChart 定位到选中节点对应的曲线图
     */
    void locationChart();

    /**
     * @brief FullScreenWindow 全屏显示选中的item
     */
    void FullScreenWindow();

    void setItemIsCheck(TreeItem *item,bool isCheck);

    /**
     * @brief getCheckedItemData    获取全部勾选的item
     * @param resData
     */
    void getCheckedItemData(QList<QVariantMap> &resData);

private:
    Ui::DataTreeWig *ui;


    /**
     * @brief getModelItemFilterByIndex //根据筛选模型的QModelIndex获取源模型的item
     * @param index 筛选模型的QModelIndex
     * @return 源模型的item
     */
    TreeItem *getModelItemByFilterIndex(QModelIndex index);

    /**
     * @brief model     数据导航树中的模型数据
     */
    TreeModel *model;

    /**
     * @brief openFiles 已经打开的文件
     */
    QStringList openFiles;

    TableViewSortFilterModelBase *m_pTableViewSortFilterModelBase;
};

#endif // DATATREEWIG_H
