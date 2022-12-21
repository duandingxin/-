/**
 * @file GlobalCurveState.h
 * @brief 数据分析工具单例类，记录全局的数据，达到数据的同步
 * @author hejie
 * @version 1.0.0
 * @date 2021-11-05
 *
 * @section LICENSE
 *
 * Copyright(c)2021 winring All rights reserved
 *
 * @section DESCRIPTION
 * 数据分析工具单例类，记录全局的数据，达到数据的同步,鼠标平移，缩放，放大，框选等操作
 *
 */
#ifndef GLOBALCURVESTATE_H
#define GLOBALCURVESTATE_H

#include <QObject>
#include <QPointF>
#include <QWheelEvent>

class GlobalCurveState : public QObject
{
    Q_OBJECT
public:
    ~GlobalCurveState();

    static GlobalCurveState *getInstance();

    void releaseGlobalCurveState();

    /**
     * @brief getGlobalPos  获取全局窗口的坐标
     * @return
     */
    QPoint getGlobalPos();

    /**
     * @brief setGlobalPos  设置全局窗口的坐标
     * @param pos
     */
    void setGlobalPos(QPoint pos);

    /**
     * @brief getGlobalState    获取全局状态
     * @return
     */
    bool getGlobalState();

    /**
     * @brief setGlobalState    设置全局状态
     * @param isTrue
     */
    void setGlobalState(bool isTrue);

    /**
     * @brief setGlobalWheelEvent   设置全局的鼠标滚轮事件
     * @param event
     */
    void setGlobalWheelEvent(QWheelEvent *event);

    /**
     * @brief getGlobalWheelEvent   获取全局的鼠标滚轮事件
     * @return
     */
    QWheelEvent *getGlobalWheelEvent();

    /**
     * @brief setGlobalMousePress   设置全局的鼠标点击事件
     * @param event
     */
    void setGlobalMousePress(QMouseEvent *event);

    /**
     * @brief getGlobalMousePress   获取全局的鼠标点击事件
     * @return
     */
    QMouseEvent *getGlobalMousePress();

    /**
     * @brief setGlobalMouseRelease 设置全局的鼠标点击松开事件
     * @param event
     */
    void setGlobalMouseRelease(QMouseEvent *event);

    /**
     * @brief getGlobalMouseRelease 获取全局的鼠标点击松开事件
     * @return
     */
    QMouseEvent *getGlobalMouseRelease();

    /**
     * @brief setGlobalMouseMove    设置全局的鼠标移动事件
     * @param event
     */
    void setGlobalMouseMove(QMouseEvent *event);

    /**
     * @brief getGlobalMouseMove    获取全局的鼠标点击事件
     * @return
     */
    QMouseEvent *getGlobalMouseMove();

    /**
     * @brief setGlobalActiveWindowId   设置全局中鼠标正在操作的窗口
     * @param id
     */
    void setGlobalActiveWindowId(QString id);

    /**
     * @brief getGlobalActiveWindowId   获取全局中鼠标正在操作的窗口
     * @return
     */
    QString getGlobalActiveWindowId();

    /**
     * @brief setGlobalWindows          设置全屏窗口模式
     * @param isTrue
     */
    void setGlobalWindows(bool isTrue);

    /**
     * @brief getGlobalWindows          获取全屏窗口模式
     * @return
     */
    bool getGlobalWindows();

private:
    explicit GlobalCurveState(QObject *parent = nullptr);

    static GlobalCurveState *m_GlobalCurveState;

    QPoint curvePos;                    //全局坐标
    bool IsGlobal = false;              //全局同步状态
    bool IsGlobalWindows = false;       //全屏窗口状态
    QWheelEvent *m_WheelEvent;          //全局的滚轮缩放事件
    QMouseEvent *m_MousePressEvent;     //全局的鼠标点击事件
    QMouseEvent *m_MouseReleaseEvent;   //全局的鼠标松开事件
    QMouseEvent *m_MouseMoveEvent;      //全局的鼠标移动事件
    QString m_GlobalActiveWindowId;     //当前全局中活动窗口的ID
};

#endif // GLOBALCURVESTATE_H
