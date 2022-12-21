QT       += core gui  xml printsupport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataVisualizationAnalysisLib
TEMPLATE = app

DEFINES += DATAVISUALIZATIONANALYSISLIB_LIBRARY

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

include(src/qtpropertybrowser.pri)
include(LogWidget/qlog/QsLog.pri)

SOURCES += \
    DockWidget/NXDockWidget.cpp \
    DockWidget/NXDockWidgetTabBar.cpp \
    DockWidget/NXDockWidgetTabButton.cpp \
    DockWidget/NXDockWidgetTitle.cpp \
    E:/Qss/untitled25/text.cpp \
    GlobalCurveState.cpp \
    LogWidget/LogForm.cpp \
    StatusBarWidget.cpp \
#    TestScriptParse/testscriptparser.cpp \
    TreeWidget/TableViewSortFilterModelBase.cpp \
    TreeWidget/datatreewig.cpp \
    TreeWidget/treeitem.cpp \
    TreeWidget/treemodel.cpp \
#    VVPreview/vvpreviewdata.cpp \
    chartConfigWig/chartConfigWig.cpp \
    customListwidget.cpp \
    customplotWidget/MdiChildWidgetBase.cpp \
    customplotWidget/ScaleVerticalLines.cpp \
    customplotWidget/XxwCustomPlot.cpp \
    customplotWidget/XxwTracer.cpp \
    customplotWidget/customplotWidget.cpp \
    datavisualizationanalysislib.cpp \
    MainWindow.cpp \
    qcustomplot.cpp \
    tableWidget/dataTableWig.cpp \
    main.cpp \
    waittingdlg.cpp

HEADERS += \
    DockWidget/NXDockWidget.h \
    DockWidget/NXDockWidgetTabBar.h \
    DockWidget/NXDockWidgetTabButton.h \
    DockWidget/NXDockWidgetTitle.h \
    E:/Qss/untitled25/text.h \
    GlobalCurveState.h \
    LogWidget/LogForm.h \
    MainWindow.h \
    StatusBarWidget.h \
#    TestScriptParse/testscriptparse_global.h \
#    TestScriptParse/testscriptparser.h \
    TreeWidget/TableViewSortFilterModelBase.h \
    TreeWidget/datatreewig.h \
    TreeWidget/treeitem.h \
    TreeWidget/treemodel.h \
#    VVPreview/vvpreviewdata.h \
    chartConfigWig/chartConfigWig.h \
    customListwidget.h \
    customplotWidget/MdiChildWidgetBase.h \
    customplotWidget/ScaleVerticalLines.h \
    customplotWidget/XxwCustomPlot.h \
    customplotWidget/XxwTracer.h \
    customplotWidget/customplotWidget.h \
    datavisualizationanalysislib.h \
    datavisualizationanalysislib_global.h \
    qcustomplot.h \
    tableWidget/dataTableWig.h \
    waittingdlg.h

FORMS += \
    LogWidget/LogForm.ui \
    MainWindow.ui \
    StatusBarWidget.ui \
    TreeWidget/datatreewig.ui \
    chartConfigWig/chartConfigWig.ui \
    customplotWidget/MdiChildWidgetBase.ui \
    customplotWidget/customplotWidget.ui \
    tableWidget/dataTableWig.ui \
    waittingdlg.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

QMAKE_POST_LINK += xcopy /y/F \"$$PWD/datavisualizationanalysislib.h\" \"$$DEST_IC_DIR\\\" $$escape_expand(\\n\\t)

RESOURCES += \
    Icon.qrc \
    qss.qrc

CONFIG += c++11
