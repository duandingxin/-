/**
 * @file MainWindow.h
 * @brief 数据可视化主界面类
 * @author hejie
 * @version 1.0.0
 * @date 2021-09-26
 *
 * @section LICENSE
 *
 * Copyright(c)2021 winring All rights reserved
 *
 * @section DESCRIPTION
 * descrip
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <assert.h>
#include <customplotWidget/MdiChildWidgetBase.h>
#include "StatusBarWidget.h"
#include "TreeWidget/datatreewig.h"
#include "tableWidget/dataTableWig.h"
#include "chartConfigWig/chartConfigWig.h"
#include "datavisualizationanalysislib_global.h"
#include "customListwidget.h"
#include "GlobalCurveState.h"
#include "QsLog.h"


/**
 * @brief areaToOrientation     根据dock获取方向
 * @param area
 * @return
 */
inline Qt::Orientation areaToOrientation(Qt::DockWidgetArea area)
{
    assert((area == Qt::LeftDockWidgetArea) || (area ==Qt::RightDockWidgetArea ) ||
           (area == Qt::TopDockWidgetArea) || (area == Qt::BottomDockWidgetArea));

    switch(area)
    {
        case Qt::LeftDockWidgetArea:
        case Qt::RightDockWidgetArea:
            return Qt::Vertical;
        case Qt::TopDockWidgetArea:
        case Qt::BottomDockWidgetArea:
            return Qt::Horizontal;
        default:
            return Qt::Orientation(0);
    }
}

class NXDockWidget;
class NXDockWidgetTabBar;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString workspace = "",QWidget *parent = nullptr);
    ~MainWindow();

public:
    /**
     * @brief addDockWidget     添加dock窗口到主界面
     * @param area              方向位置
     * @param dockWidget        dock窗口对象
     */
    void addDockWidget(Qt::DockWidgetArea area, NXDockWidget* dockWidget);
    void addDockWidget(Qt::DockWidgetArea area, NXDockWidget* dockWidget, Qt::Orientation orientation);

    /**
     * @brief removeDockWidget      移除dock窗口
     * @param dockWidget            dock窗口对象
     */
    void removeDockWidget(NXDockWidget* dockWidget);

    /**
     * @brief createMdiChild        创建mdiz子窗口 创建的同时关联相关信号
     * @return
     */
    MdiChildWidgetBase *createMdiChild(QString id);

    /**
     * @brief loadvvFile    加载测试脚本文件
     * @param vvfile
     */
    void loadvvFile(const QString &vvfile);
    /**
     * @brief loadCSVFile    加载数据记录文件
     * @param csvfile
    */
  void loadCSVFile(const QString &csvfile);

    /**
     * @brief addTracerItems        在曲线场景中添加数据标记
     * @param x                     x轴坐标
     * @param y                     y轴坐标
     */
    void addTracerItems(double x, double y , XxwCustomPlot *plot);

private:

    /**
     * @brief InitWidget    初始化界面
     */
    void InitWidget();

    /**
     * @brief InitConnect   初始化连接信号
     */
    void InitConnect();

    /**
     * @brief hideDockWidget        隐藏dock窗口
     * @param dockWidget            dock窗口对象
     */
    void hideDockWidget(NXDockWidget* dockWidget);

    /**
     * @brief getDockWidgetsAreaRect    获取主窗口tab按钮对应的dock窗口
     * @return
     */
    QRect getDockWidgetsAreaRect();

    /**
     * @brief adjustDockWidget      点击tab按钮触发函数，调整dock的大小位置
     * @param dockWidget
     */
    void adjustDockWidget(NXDockWidget* dockWidget);

    /**
     * @brief getDockWidgetBar      根据dock的位置获取tab按钮面板
     * @param area
     * @return
     */
    NXDockWidgetTabBar* getDockWidgetBar(Qt::DockWidgetArea area);

    /**
     * @brief getDockWidgetListAtArea   获取主窗口中某个区域tab按钮对应的所有dock窗口对象
     * @param area
     * @return
     */
    std::list<NXDockWidget*> getDockWidgetListAtArea(Qt::DockWidgetArea area);

    /**
     * @brief createDockWidgetBar   添加工具栏按钮到主窗口的指定区域
     * @param area                  区域位置
     */
    void createDockWidgetBar(Qt::DockWidgetArea area);

    /**
     * @brief showDockWidget    点击tab按钮，显示或隐藏dock窗口
     * @param dockWidget
     */
    void showDockWidget(NXDockWidget* dockWidget);

    /**
     * @brief dockWidgetPinned      dock窗口停靠后，自动隐藏按钮被显示
     * @param dockWidget
     */
    void dockWidgetPinned(NXDockWidget* dockWidget);

    /**
     * @brief dockWidgetUnpinned    鼠标拖出来后，自动隐藏按钮被隐藏
     * @param dockWidget
     */
    void dockWidgetUnpinned(NXDockWidget* dockWidget);

    /**
     * @brief dockWidgetDocked      Dock窗口停靠
     * @param dockWidget
     */
    void dockWidgetDocked(NXDockWidget* dockWidget);

    /**
     * @brief dockWidgetUndocked        Dock窗口取消停靠
     * @param dockWidget
     */
    void dockWidgetUndocked(NXDockWidget* dockWidget);

    /**
     * @brief menuWindows_triggered     窗口部件的菜单按钮槽函数
     * @param action
     */
    void menuWindows_triggered(QAction* action);

    /**
     * @brief resetPlotState        重置曲线的选中状态
     */
    void resetPlotState(bool isTrue);

protected:
    /**
     * @brief event     事件函数，隐藏活动窗口
     * @param event
     * @return
     */
    virtual bool event(QEvent* event) override;

    /**
     * @brief closeEvent    关闭事件
     * @param e
     */
    virtual void closeEvent(QCloseEvent *e) override;
private slots:
    /**
     * @brief slotOpenExcel    打开excel，加载数据
     */
    void slotOpenExcel();

    /**
     * @brief slotOpenXml  打开XML，加载数据
     */
    void slotOpenXml();

    /**
     * @brief slotNodeItem  勾选导航树的节点，触发新建曲线槽函数
     * @param item          节点对象
     */
    void slotNodeItem(TreeItem *item);

    /**
     * @brief slot_RecvPoint    接收custom窗口的坐标信号,处理全局窗口的坐标同步
     * @param pos               鼠标坐标信号
     */
    void slot_RecvPoint(QPoint pos);

    /**
     * @brief slot_RecvWheel    接收处理曲线场景中的鼠标滚轮缩放放大事件的函数
     * @param event             滚轮缩放放大事件
     */
    void slot_RecvWheel(QWheelEvent* event);

    /**
     * @brief slot_RecvMouseMove    接收处理曲线场景中的鼠标移动事件的函数
     * @param event                 鼠标移动事件
     */
    void slot_RecvMouseMove(QString id,QMouseEvent* event);

    /**
     * @brief slot_RecvMousePress   接收处理曲线场景中的鼠标点击事件的函数
     * @param event                 鼠标点击事件
     */
    void slot_RecvMousePress(QString id,QMouseEvent* event);

    /**
     * @brief slot_RecvMouseRelease 接收处理曲线场景中的鼠标移动事件的函数
     * @param event                 鼠标移动事件
     */
    void slot_RecvMouseRelease(QString id,QMouseEvent* event);

    /**
     * @brief slot_AllMode          全局窗口模式
     */
    void slot_AllMode();

    /**
     * @brief slot_oneMode          单窗口模式
     */
    void slot_oneMode();

    /**
     * @brief slotUpdataGlobalState     更新全局窗口/单窗口状态
     * @param isTrue
     */
    void slotUpdataGlobalState(bool isTrue);

    /**
     * @brief slot_RecvSelectGraphData      接收选中曲线的数据
     * @param graph                         曲线对象
     */
    void slot_RecvSelectGraphData(XxwCustomPlot *plot, QCPGraph* graph);

    /**
     * @brief slot_RecvFullScreenWindow     全屏展示
     * @param id                            窗口的id
     */
    void slot_RecvFullScreenWindow(QString id);

    /**
     * @brief slot_CurveActionRestoreFull   取消全屏展示
     * @param id                            窗口的id
     */
    void slot_CurveActionRestoreFull(QString id);

    /**
     * @brief slot_SendRangePos             接收窗口右键框选后的坐标
     * @param xpos                          x轴的坐标
     * @param ypos                          y轴的坐标
     */
    void slot_SendRangePos(QPoint xpos,QPoint ypos);

    /**
     * @brief slot_SendlocatorData          接收数据表格中的全局数据定位
     * @param begin                         开始的坐标
     * @param end                           结束的坐标
     */
    void slot_SendlocatorData(double begin,double end);

    /**
     * @brief slot_ClearlocatorData         清空全局数据
     */
    void slot_ClearlocatorData();

    /**
     * @brief slotActionRestoreZoom         恢复全部窗口的缩放
     */
    void slotActionRestoreZoom();

    /**
     * @brief slotAction_CurveAdaptation    曲线自适应场景
     */
    void slotAction_CurveAdaptation();

    /**
     * @brief slt_AddVerticalLine 全局添加阈值线
     */
    void slt_AddVerticalLine();

    /**
     * @brief slt_RemoveVerticalLine 全局删除阈值线
     */
    void slt_RemoveVerticalLine();

    /**
     * @brief slotActionzoomIn      放大
     */
    void slotActionzoomIn();

    /**
     * @brief slotActionzoomOut     缩小
     */
    void slotActionzoomOut();

    /**
     * @brief slotActionClearAllWidget  清空所有的窗口
     */
    void slotActionClearAllWidget();

    /**
     * @brief slotAction_savePNG        另存为图片
     */
    void slotAction_savePNG();

    /**
     * @brief slotSetWidgetNumber       设置窗口列的数量
     */
    void slotSetWidgetNumber();

    /**
      * @brief setSetWidgetNumber 设置窗口列数的具体执行函数（这个函数以后要考虑移动到customListwidget中）
      * @param widget_number（窗口列数）
      */
     void sltsetSetWidgetNumber();

    /**
     * @brief slotWriteLog              写日志
     * @param message
     * @param level
     */
    void slotWriteLog(const QString &message, int level);

    /**
     * @brief slot_SendCustomData   接收拆分曲线的槽函数
     * @param id                    曲线id
     * @param graph                 曲线对象
     */
    void slot_SendCustomData(QString id,QCPGraph* graph);

    /**
     * @brief slotSetTreeItemUnchecked 取消左侧树节点选中状态的槽函数
     * @param uuid 节点的uuid
     */
    void slotSetTreeItemUnchecked(QString uuid);

    void slotlocationChart(QString uuid);


private:
    Ui::MainWindow *ui;

    /**
     * @brief m_menuWindows     主窗口的菜单按钮
     */
    QMenu* m_menuWindows;

    /**
     * @brief m_dockWidget  当前活动的dock窗口
     */
    NXDockWidget* m_dockWidget;

    /**
     * @brief m_dockWidgets     存储所有的dock窗口对象
     */
    std::list<NXDockWidget*> m_dockWidgets;

    /**
     * @brief m_dockWidgetBar   存储主窗口中所有的tab按钮以及dock窗口对象
     */
    std::map<Qt::DockWidgetArea, NXDockWidgetTabBar*> m_dockWidgetBar;

    /**
     * @brief m_StatusBarWidget 主窗口底部状态栏
     */
    StatusBarWidget *m_statusBarWidget;

    /**
     * @brief centralWidget     MDI工作区域
     */
    customListwidget* centralWidget_;

    /**
     * @brief m_datatreewig     数据导航树
     */
    DataTreeWig *m_datatreewig;

    /**
     * @brief m_workSpacePath   工作空间路径
     */
    QString m_workSpacePath;

    /**
     * @brief m_dataTableWig    右侧数据表格显示窗口
     */
    dataTableWig *m_dataTableWig;

    /**
     * @brief m_chartConfigWig  右侧曲线设置窗口
     */
    chartConfigWig *m_chartConfigWig;

    /**
     * @brief m_CentralWidgetId     工作区域主窗口
     */
    QString m_CentralWidgetId;

    /**
     * @brief m_horstationMax   窗口中显示的列数
     */
    int m_horstationMax;

    /**
     * @brief m_verticalMax     窗口中显示的行数
     */
    int m_verticalMax;

    /**
     * @brief textEdit          日志操作记录,临时的，以后用日志库
     */
    QTextEdit* textEdit;


    /**
     * @brief stackedWidget_ 主窗的CentralWidget区
     */
    QStackedWidget *stackedWidget_;
};
#endif // MAINWINDOW_H
