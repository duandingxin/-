#include "datavisualizationanalysislib.h"
#include "MainWindow.h"
#include <QMessageBox>


DataVisualizationAnalysisLib::DataVisualizationAnalysisLib(QString workspace, QWidget* parent)
{
   MainWindow* widget = new MainWindow(workspace,parent);
   widget->showMaximized();
}

DataVisualizationAnalysisLib::DataVisualizationAnalysisLib(QString workspace, PreTestScriptType type, QString file, QWidget *parent)
{
    MainWindow* widget = new MainWindow(workspace, parent);
    if(type == PreTestScriptType::VV)
    {
        widget->loadvvFile(file);
    }else if(type == PreTestScriptType::EXCEl){
        widget->loadCSVFile(file);
    }
    widget->showMaximized();
}
