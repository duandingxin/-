#ifndef VVPREVIEWDATA_H
#define VVPREVIEWDATA_H

#include <QObject>
#include <QMap>
#include <list>
#include <QThread>
#include <QSharedPointer>
#include "../TestScriptParse/testscriptparser.h"

typedef struct SigData
{
    SigData() {}
    QString sigid_;
    QString cmd_type_;
    QVector<QPointF> data_;

}SigData_t;

typedef QMap<QString, SigData_t> SigDataMap_t; //<信号id, 信号数据>
typedef QMap<QString, SigDataMap_t> MsgData_t; //<消息ID, 消息数据>

class VVPreviewData : public QThread
{
    Q_OBJECT
public:
    explicit VVPreviewData(QString workspace, QString vvfile, QObject *parent = nullptr);

    MsgData_t getMsgData();

    QString getBaseName();

    double getTick_ns() const;  //获取一个tick代表多少ns

signals:
    void sigDataOk(QString filePath,long long tick_ns_);

private:
    bool loadICD();

    void run();

private:
    QSharedPointer<TestScriptParser> parser_;
    MsgData_t msg_data_;
    bool read_sucess_;
    QString base_name_;
    uint64_t tick_ns_;
    QString filePath;
};

#endif // VVPREVIEWDATA_H
