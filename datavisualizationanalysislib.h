#ifndef DATAVISUALIZATIONANALYSISLIB_H
#define DATAVISUALIZATIONANALYSISLIB_H

#include <QString>
#include <QWidget>

#include "datavisualizationanalysislib_global.h"
class DATAVISUALIZATIONANALYSISLIBSHARED_EXPORT DataVisualizationAnalysisLib
{

public:
    DataVisualizationAnalysisLib(QString workspace, QWidget* parent);

    DataVisualizationAnalysisLib(QString workspace, PreTestScriptType type, QString file, QWidget* parent);
};

#endif // DATAVISUALIZATIONANALYSISLIB_H
