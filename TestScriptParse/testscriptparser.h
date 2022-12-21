#ifndef TESTSCRIPTPARSER_H
#define TESTSCRIPTPARSER_H

#include <QObject>
#include <QString>
#include <QHash>
#include "testscriptparse_global.h"

class TestScriptParser : public QObject
{
    Q_OBJECT
public:
    explicit TestScriptParser(QString test_script_file, QObject *parent = nullptr);

    TestScriptSigList_t getAllSignals(); //获取哪些msg下的哪些信号参与了该测试脚本

    TestDataMap_t getTestData(); //获取具体信号在当前测试脚本中所有的设置

    uint64_t getTestScriptTick(); //有多少tick

    uint64_t getBeatNs();

private:
    TestScriptSigDataList_t getCurrentTickData(uint64_t tick);

    void generateTestData();
    uint64_t sToNum(QString sStr);

private:
    QString test_script_file_;
    QList<TestScriptSig> script_sigs_;
    TestCmdMap_t steps_;
    TestDataMap_t test_data_;
    int max_tick_;
    uint64_t beat_ns_; //一个节拍代表的时间(ns)
};

#endif // TESTSCRIPTPARSER_H
