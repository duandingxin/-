/**
 * @file StatusBarWidget.h
 * @brief 数据分析工具窗口下的状态栏
 * @author hejie
 * @version 1.0.0
 * @date 2021-11-05
 *
 * @section LICENSE
 *
 * Copyright(c)2021 winring All rights reserved
 *
 * @section DESCRIPTION
 * 记录全局的状态信息，操作曲线名称等
 *
 */
#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QWidget>

namespace Ui {
class StatusBarWidget;
}

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = nullptr);
    ~StatusBarWidget();

    /**
     * @brief setlabelWinModeStart  设置状态栏全局/单窗口状态信息
     * @param isTrue                全局/单窗口状态
     */
    void setlabelWinModeStart(bool isTrue);

    /**
     * @brief setcustomName         设置当前正在操作曲线的名称
     * @param name                  名称
     */
    void setcustomName(QString name);

private:
    Ui::StatusBarWidget *ui;
};

#endif // STATUSBARWIDGET_H
