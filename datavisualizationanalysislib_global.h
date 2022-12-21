#ifndef DATAVISUALIZATIONANALYSISLIB_GLOBAL_H
#define DATAVISUALIZATIONANALYSISLIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QPointF>

#if defined(DATAVISUALIZATIONANALYSISLIB_LIBRARY)
#  define DATAVISUALIZATIONANALYSISLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATAVISUALIZATIONANALYSISLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

enum class PreTestScriptType{VV, EXCEl, ICD_DATA, FMU_DATA};
enum class TreeNodeType{MSGTYPE, SIGTYPE, MONITORTYPE, MONITORVALUETYPE, UNKNOWN};
enum class COLUMNS{COLUMNS_ONE = 1, COLUMNS_TWO, COLUMNS_THREE, COLUMNS_FOUR,COLUMNS_FIVE};//窗口列数
enum class LOGSTATE{LOGSTATE_TRACE = 0, LOGSTATE_DEBUG, LOGSTATE_INFO, LOGSTATE_WARN,LOGSTATE_ERROR,LOGSTATE_FATAL};//日志的提示等级
typedef QMap<QString,QVector<double>> GRAPHSDATA;           //开始阈值线和结束阈值线范围的曲线数据
typedef QList<QMap<QString,QVector<QPointF>>> CURVEDATALIST;//获取当前窗口所有的曲线对象数据

#define CHARTNAME "chartName"   //图表曲线的名称
#define CHARTDATA "chartData"   //图表曲线的数据
#define TICK_NS "ticks"         //图表曲线的tick
#define FILENAME "fileName"     //图表曲线对应的文件名称
#define CHARTID "uuid"          //图表曲线的uuid
#define INIT_HORSTATION 2       //水平布局默认列数
#define INIT_VERTICAL 2         //垂直布局默认列数
#define PNG_WIDTH 1024          //图片的宽度
#define PNG_HEIGHT 780          //图片的高低
#define INIT_NUM 0              //初始化数字
#define MAX_NODE 20             //初始化最大添加的节点
#define TIME_POINT "timepoint"  //图表曲线每个点对应的时间（单位：ns）
#define TICKTIMERATIO "tickTimeRatio" //tick和时间的对应比例。这里的时间单位为纳秒



#endif // DATAVISUALIZATIONANALYSISLIB_GLOBAL_H
