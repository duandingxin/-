#ifndef TESTSCRIPTPARSE_GLOBAL_H
#define TESTSCRIPTPARSE_GLOBAL_H

#include <QString>
#include <QList>
#include <QMap>

struct TestCmdData
{
    TestCmdData()
    {
       step = 0;
    }

    QString cmd_type;
    QString msgid;
    QString sigid;
    QString sig_name;
    QString data_type;
    uint64_t step;
};

struct TestScriptSig
{
    TestScriptSig() {}
    TestScriptSig(QString msg_id, QString sig_id)
    {
        msgid = msg_id;
        sigid = sig_id;
    }

    bool operator< (const TestScriptSig &other)const
    {
        if(msgid < other.msgid) return true;
        else if(msgid > other.msgid) return false;
        else if(msgid == other.msgid)
        {
            if(sigid < other.sigid) return true;
            else return false;
        }
        return true;
    }

    TestScriptSig & operator=(const TestScriptSig &other)
    {
        msgid = other.msgid;
        sigid = other.sigid;
    }

    QString msgid;
    QString sigid;
};

typedef QList<TestCmdData> SigCmdList_t;
typedef QMap<TestScriptSig, SigCmdList_t> TestCmdMap_t;
typedef QList<TestScriptSig> TestScriptSigList_t;

struct TestScriptSigData
{
    TestScriptSigData()
    {
        value = 0;
        current_step = 0;
    }
    QString msgid;
    QString sigid;
    double  value;
    uint64_t current_step;
    QString command;
};
typedef QList<TestScriptSigData> TestScriptSigDataList_t;
typedef QMap<TestScriptSig, TestScriptSigDataList_t> TestDataMap_t;


#endif // TESTSCRIPTPARSE_GLOBAL_H
