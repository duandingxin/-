/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionzoomIn;
    QAction *actionzoomOut;
    QAction *actionExport;
    QAction *action_savePNG;
    QAction *actionClearAllWidget;
    QAction *action_restore;
    QAction *action_CurveAdaptation;
    QAction *action_SetSize;
    QAction *action_setWidgetNumber;
    QAction *action_AllMode;
    QAction *action_oneMode;
    QAction *action_Excel;
    QAction *action_XML;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_3;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1334, 629);
        actionzoomIn = new QAction(MainWindow);
        actionzoomIn->setObjectName(QStringLiteral("actionzoomIn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DockWidget/Icon/zoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionzoomIn->setIcon(icon);
        actionzoomOut = new QAction(MainWindow);
        actionzoomOut->setObjectName(QStringLiteral("actionzoomOut"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DockWidget/Icon/zoomOut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionzoomOut->setIcon(icon1);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        action_savePNG = new QAction(MainWindow);
        action_savePNG->setObjectName(QStringLiteral("action_savePNG"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DockWidget/Icon/savePng2.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_savePNG->setIcon(icon2);
        actionClearAllWidget = new QAction(MainWindow);
        actionClearAllWidget->setObjectName(QStringLiteral("actionClearAllWidget"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/DockWidget/Icon/Clear1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearAllWidget->setIcon(icon3);
        action_restore = new QAction(MainWindow);
        action_restore->setObjectName(QStringLiteral("action_restore"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/DockWidget/Icon/renew.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_restore->setIcon(icon4);
        action_CurveAdaptation = new QAction(MainWindow);
        action_CurveAdaptation->setObjectName(QStringLiteral("action_CurveAdaptation"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/DockWidget/Icon/action_CurveAdaptation.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_CurveAdaptation->setIcon(icon5);
        action_SetSize = new QAction(MainWindow);
        action_SetSize->setObjectName(QStringLiteral("action_SetSize"));
        action_setWidgetNumber = new QAction(MainWindow);
        action_setWidgetNumber->setObjectName(QStringLiteral("action_setWidgetNumber"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/DockWidget/Icon/setCustom.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_setWidgetNumber->setIcon(icon6);
        action_AllMode = new QAction(MainWindow);
        action_AllMode->setObjectName(QStringLiteral("action_AllMode"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/DockWidget/Icon/all3.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_AllMode->setIcon(icon7);
        action_oneMode = new QAction(MainWindow);
        action_oneMode->setObjectName(QStringLiteral("action_oneMode"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/DockWidget/Icon/oneWindows.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_oneMode->setIcon(icon8);
        action_Excel = new QAction(MainWindow);
        action_Excel->setObjectName(QStringLiteral("action_Excel"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/DockWidget/Icon/open_excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Excel->setIcon(icon9);
        action_XML = new QAction(MainWindow);
        action_XML->setObjectName(QStringLiteral("action_XML"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/DockWidget/Icon/open_xml.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_XML->setIcon(icon10);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QStringLiteral("action_8"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1334, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menu_2);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action_Excel);
        menu->addAction(action_XML);
        menu_2->addAction(menu_4->menuAction());
        menu_2->addAction(menu_5->menuAction());
        menu_4->addAction(action_4);
        menu_4->addAction(action_5);
        menu_5->addAction(action_6);
        menu_5->addAction(action_7);
        menu_5->addAction(action_8);
        menu_3->addAction(action_3);
        toolBar->addAction(action_AllMode);
        toolBar->addAction(action_oneMode);
        toolBar->addSeparator();
        toolBar->addAction(actionzoomIn);
        toolBar->addAction(actionzoomOut);
        toolBar->addSeparator();
        toolBar->addAction(action_restore);
        toolBar->addAction(action_CurveAdaptation);
        toolBar->addSeparator();
        toolBar->addAction(actionClearAllWidget);
        toolBar->addSeparator();
        toolBar->addAction(action_savePNG);
        toolBar->addAction(action_setWidgetNumber);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\217\257\350\247\206\345\214\226\345\267\245\345\205\267", Q_NULLPTR));
        actionzoomIn->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionzoomIn->setToolTip(QApplication::translate("MainWindow", "\346\224\276\345\244\247", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionzoomOut->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionzoomOut->setToolTip(QApplication::translate("MainWindow", "\347\274\251\345\260\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionExport->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("MainWindow", "\345\257\274\345\207\272Excel\346\225\260\346\215\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_savePNG->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272\345\233\276\347\211\207", Q_NULLPTR));
        actionClearAllWidget->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\252\227\345\217\243", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClearAllWidget->setToolTip(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\211\200\346\234\211\347\252\227\345\217\243", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_restore->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215\347\274\251\346\224\276", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_restore->setToolTip(QApplication::translate("MainWindow", "\346\201\242\345\244\215\347\274\251\346\224\276\346\257\224\344\276\213", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_CurveAdaptation->setText(QApplication::translate("MainWindow", "\346\233\262\347\272\277\350\207\252\351\200\202\345\272\224", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_CurveAdaptation->setToolTip(QApplication::translate("MainWindow", "\346\233\262\347\272\277\350\207\252\351\200\202\345\272\224\347\252\227\345\217\243", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SetSize->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\347\252\227\345\217\243\345\244\247\345\260\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SetSize->setToolTip(QApplication::translate("MainWindow", "\350\256\276\347\275\256\347\252\227\345\217\243\345\244\247\345\260\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_setWidgetNumber->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\347\252\227\345\217\243\346\225\260", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_setWidgetNumber->setToolTip(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\257\217\344\270\200\345\210\227\345\261\225\347\244\272\347\252\227\345\217\243\347\232\204\346\225\260\351\207\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_AllMode->setText(QApplication::translate("MainWindow", "\345\205\250\347\252\227\345\217\243\346\250\241\345\274\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_AllMode->setToolTip(QApplication::translate("MainWindow", "\345\205\250\347\252\227\345\217\243\346\250\241\345\274\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_oneMode->setText(QApplication::translate("MainWindow", "\345\215\225\347\252\227\345\217\243\346\250\241\345\274\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_oneMode->setToolTip(QApplication::translate("MainWindow", "\345\215\225\347\252\227\345\217\243\346\250\241\345\274\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Excel->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275Excel\346\225\260\346\215\256", Q_NULLPTR));
        action_XML->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275XML\346\225\260\346\215\256", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\211\213\345\206\214", Q_NULLPTR));
        action_4->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\207", Q_NULLPTR));
        action_5->setText(QApplication::translate("MainWindow", "\350\213\261\346\226\207", Q_NULLPTR));
        action_6->setText(QApplication::translate("MainWindow", "\351\273\221\350\211\262", Q_NULLPTR));
        action_7->setText(QApplication::translate("MainWindow", "\347\231\275\350\211\262", Q_NULLPTR));
        action_8->setText(QApplication::translate("MainWindow", "\350\223\235\350\211\262", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("MainWindow", "\344\270\255\350\213\261\346\226\207\345\210\207\346\215\242", Q_NULLPTR));
        menu_5->setTitle(QApplication::translate("MainWindow", "\351\243\216\346\240\274\344\270\273\351\242\230\345\210\207\346\215\242", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
