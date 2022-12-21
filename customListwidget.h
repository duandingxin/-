/**
 * @file customListwidget.h
 * @brief 数据分析工具中心的工作区域，每个图表都是一个item；
 * @author hejie
 * @version 1.0.0
 * @date 2021-11-05
 *
 * @section LICENSE
 *
 * Copyright(c)2021 winring All rights reserved
 *
 * @section DESCRIPTION
 *  实现item鼠标拖动合并，交换位置;
 *
 */
#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>
#include <TreeWidget/treeitem.h>
#include "QListWidget"
#include "customplotWidget/MdiChildWidgetBase.h"
#include "QsLog.h"
#include <QObject>

class customListwidget : public QListWidget
{
    Q_OBJECT
public:
    explicit customListwidget(QWidget *parent = Q_NULLPTR);
    ~customListwidget();

    /**
     * @brief dropEvent     拖动事件
     * @param event
     */
    void dropEvent(QDropEvent *event) ;

    /**
     * @brief resizeEvent 窗口大小改变事件
     * @param event
     */
    void resizeEvent(QResizeEvent * event)override;

    /**
     * @brief addListItem   添加item
     * @param item
     */
    void addListItem(QString id,QListWidgetItem *item);

    /**
     * @brief insertListItem    在指定位置插入item
     * @param id
     * @param row
     * @param item
     */
    void insertListItem(QString id, int row, QListWidgetItem *item);

    /**
     * @brief removeListItem    删除item
     * @param item
     */
    void removeListItem(TreeItem *item);

    /**
     * @brief removeListItem    删除item
     * @param item
     */
    void removeListItem(QString id);

    /**
     * @brief getCurWidgetId    根据id获取item窗口
     * @param id
     * @return
     */
    MdiChildWidgetBase *getCurWidgetId(QString id);

    /**
     * @brief getItems      获取当前导航树中所有的窗口item
     * @return
     */
    QHash<QString,QListWidgetItem *>getItems();

    /**
     * @brief getCurItem    获取当前列表中的item对象
     * @param id
     * @return
     */
    QListWidgetItem *getCurItem(QString id);


    void locationChart(QString id);

    void addGraphIdAndTickTimeRatio(QString id,double TickTimeRatio);

    QHash<QString,double>getAllGraphIdAndTickTimeRatio();

    /**
     * @brief getBeginEndItem   获取当前界面显示的所有的item窗口
     * @return
     */
    QList<MdiChildWidgetBase *> getBeginEndItem();

    /**
     * @brief setWidgethorstationMax    设置当前窗口显示的一行总数
     * @param maxNum                    每一行显示的窗口数
     */
    void setWidgethorstationMax(int maxNum);
signals :
    /**
     * @brief signalSetTreeItemUnchecked 取消左侧树节点的选中状态
     * @param uuid 节点的uuid
     */
    void signalSetTreeItemUnchecked(QString uuid);

    /**
     * @brief sigRearrange 通知主界面重新布局
     */
    void sigRearrange();

private:

    /**
     * @brief horstationMax     每一行显示的窗口总数
     */
    int horstationMax;

    /**
     * @brief items     存储所有的item
     */
    QHash<QString,QListWidgetItem *> items;

    /**
     * @brief linesIdAndTickTimeRatio   TickTimeRatio值这里已经不需要了暂时先不删
     */
    QHash<QString,double>linesIdAndTickTimeRatio;
};

#endif // CUSTOMLISTWIDGET_H
