#include "testscriptparser.h"
#include <QFile>
#include <QDomDocument>
#include "../WRMemLeaksAssist.h"

TestScriptParser::TestScriptParser(QString test_script_file, QObject *parent)
    : QObject(parent)
    , test_script_file_(test_script_file)
    , max_tick_(0)
    , beat_ns_(0)
{
    QFile xmlFile(test_script_file);
    if(!xmlFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QString errorStr="";
    int errorLine=0;
    int errorColumn=0;
    QDomDocument doc;
    if (!doc.setContent(&xmlFile, false, &errorStr, &errorLine, &errorColumn))
    {
        xmlFile.close();
        return;
    }
    xmlFile.close();

    QDomElement root = doc.documentElement();//读取根节点
    QDomElement steptime_node = root.firstChildElement("scripFile").firstChildElement("general").firstChildElement("stepTime");
    if(steptime_node.isNull() == false)
    {
        //beat_ns_ = steptime_node.text().toDouble() * 1000*1000*1000;
        //by lk start
        QString srtbeat_ns_=steptime_node.text();
        beat_ns_=sToNum(srtbeat_ns_);

        //by lk end


    }
    QDomElement test_case = root.firstChildElement("testCase").firstChildElement("caseData");
    QDomElement step_node = test_case.firstChildElement("row");

    while (step_node.isNull() == false)
    {
        uint64_t current_step = step_node.firstChildElement("currentStep").text().toULongLong();
        if(max_tick_ < current_step)
        {
            max_tick_ = current_step;
        }
        uint64_t delay = step_node.firstChildElement("isdelay").text().toULongLong();

        if(delay > 0)
        {// delay
        }
        else
        {
            QDomElement step_cmd = step_node.firstChildElement("stepCmd").firstChildElement("row");
            while(step_cmd.isNull() == false)
            {
                QString cmd_type = step_cmd.firstChildElement("cmdType").text();
                QString data_type = step_cmd.firstChildElement("dataType").text();
                QString data_value = step_cmd.firstChildElement("dataValue").text();
                QString msgid = step_cmd.firstChildElement("groupID").text();
                QString sigid = step_cmd.firstChildElement("signalID").text();
                QString sig_name = step_cmd.firstChildElement("signalName").text();

                TestCmdData cmd;
                cmd.cmd_type = cmd_type;
                cmd.data_type = data_type;
                cmd.msgid = msgid;
                cmd.sigid = sigid;
                cmd.sig_name = sig_name;
                cmd.step = current_step;

                QStringList value_list = data_value.split(';', QString::SkipEmptyParts);
                int size = value_list.size();
                if(size == 0)
                {
                    step_cmd = step_cmd.nextSiblingElement("row");
                    continue;
                }
                QString function_name = value_list.at(0);
                if(function_name == "SineWave")
                {
                    if(size != 5)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new SineWave(QString(value_list.at(1)).toDouble(),
                                                       QString(value_list.at(2)).toDouble(),QString(value_list.at(3)).toUInt(),QString(value_list.at(4)).toInt());
                   // cmd.value_algorithm->setInitValue(QString(value_list.at(1)).toDouble());
                }
                else if(function_name == "Linear") //y = ax+b
                {
                    if(size != 5)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new LinearFunction(QString(value_list.at(1)).toDouble(),
                                                             QString(value_list.at(2)).toDouble(),QString(value_list.at(3)).toLongLong(),QString(value_list.at(4)).toInt());
                }
                else if(function_name == "StepOffset")
                {
                    if(size != 4)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new StepOffset(QString(value_list.at(1)).toDouble(),QString(value_list.at(2)).toUInt(),QString(value_list.at(3)).toInt());
                    cmd.value_algorithm->setInitValue(QString(value_list.at(1)).toDouble());
                }
                else if(function_name == "Ramp")
                {
                    if(size != 5)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new Ramp(QString(value_list.at(1)).toDouble(), QString(value_list.at(2)).toDouble(),
                                                   QString(value_list.at(3)).toUInt(),QString(value_list.at(4)).toInt());
                }
                else if(function_name == "SquareWave")
                {
                    if(size != 7)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new SquareWave(QString(value_list.at(1)).toDouble(),QString(value_list.at(2)).toUInt(),
                                                         QString(value_list.at(3)).toDouble(), QString(value_list.at(4)).toUInt(),QString(value_list.at(5)).toUInt(),QString(value_list.at(6)).toInt());
                  //  cmd.value_algorithm->setInitValue(QString(value_list.at(1)).toDouble());
                }else if(function_name == "WhiteNoise"){
                    if(size != 5)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new WhiteNoise(QString(value_list.at(1)).toDouble(),QString(value_list.at(2)).toDouble(),
                                                         QString(value_list.at(3)).toUInt(),QString(value_list.at(4)).toInt());

                }
                else if(function_name == "RandomNumber")
                {
                    if(size != 5)
                    {
                        step_cmd = step_cmd.nextSiblingElement("row");
                        continue;
                    }
                    cmd.value_algorithm = new RandomNumber(QString(value_list.at(1)).toDouble(), QString(value_list.at(2)).toDouble(),
                                                   QString(value_list.at(3)).toUInt(),QString(value_list.at(4)).toInt());
                }
                else if(value_list.size() == 1)
                { //固定值
                    cmd.value_algorithm = new ConstantValue(QString(value_list.at(0)).toDouble());
                }
                cmd.value_algorithm->setSignalName(sig_name.toStdString());


                TestScriptSig msgsig(msgid, sigid);
                auto iter = steps_.find(msgsig);
                if(iter != steps_.end())
                {
                    iter.value().append(cmd);
                }
                else
                {
                    SigCmdList_t cmdlist;
                    cmdlist.append(cmd);
                    steps_.insert(msgsig, cmdlist);
                }
                if(cmd.cmd_type == "COMBINATION")
                {
                    //add taoj
                    cmd.value_algorithm->setSignalName(sig_name.toStdString());
                    uint64_t hold_tick = cmd.value_algorithm->getHoldTime();
                    uint64_t tick_num = 0;
                    if(hold_tick > 0)
                    {
                        tick_num = (current_step + hold_tick);
                    }
                    else
                    {
                        tick_num =(current_step + 1000);
                    }
                    if(tick_num > max_tick_)
                    {
                        if(tick_num > 200)
                            tick_num = 200;//数据点的量不能超过2000,要做成分页显示;
                        max_tick_ = tick_num;
                    }
                }


                step_cmd = step_cmd.nextSiblingElement("row");
            }
        }

        step_node = step_node.nextSiblingElement("row");
    }

    generateTestData();
}

TestScriptSigDataList_t TestScriptParser::getCurrentTickData(uint64_t tick)
{
    QList<TestScriptSigData> sig_datas;
    for (auto step = steps_.begin(); step != steps_.end();)
    {
        SigCmdList_t& cmdlist = step.value();
        TestScriptSigData data;
        for (auto iter = cmdlist.begin(); iter != cmdlist.end();)
        {
            TestCmdData item = *iter;
            if(item.step > tick) break;
            if(item.cmd_type.compare("SET", Qt::CaseInsensitive) == 0)
            {
                data.msgid = item.msgid;
                data.sigid = item.sigid;
                data.command = "SET";
                data.value = item.value_algorithm->operator ()();
                delete item.value_algorithm;
                iter = cmdlist.erase(iter);

                data.current_step = tick;
                sig_datas.append(data);
                continue;
            }
            else if(item.cmd_type.compare("CHECK", Qt::CaseInsensitive) == 0)
            {
                data.msgid = item.msgid;
                data.sigid = item.sigid;
                data.command = "CHECK";
                data.value = item.value_algorithm->operator ()();
                delete item.value_algorithm;
                iter = cmdlist.erase(iter);

                data.current_step = tick;
                sig_datas.append(data);
                continue;
            }
            else if(item.cmd_type.compare("COMBINATION", Qt::CaseInsensitive) == 0)
            {
                data.msgid = item.msgid;
                data.sigid = item.sigid;
                data.command = "COMBINATION";
                if(item.value_algorithm->isAdditive())
                {
                    data.value +=item.value_algorithm->operator ()();
                }
                else
                {
                    data.value =item.value_algorithm->operator ()();
                }

                data.current_step = tick;
                sig_datas.append(data);

                if(item.value_algorithm->isWorking() == false)
                {
                    iter = cmdlist.erase(iter);
                    continue;
                }
            }
            ++iter;
        }
        if(cmdlist.size() == 0)
        {
            step = steps_.erase(step);
        }
        else
        {
            ++step;
        }
    }
    return sig_datas;
}

void TestScriptParser::generateTestData()
{
    for (int i = 1; i <= max_tick_; ++i)
    {
        TestScriptSigDataList_t data = getCurrentTickData(i);
        for (auto item : data)
        {
            TestScriptSig msgsig(item.msgid, item.sigid);
            auto iter = test_data_.find(msgsig);
            if(iter != test_data_.end())
            {
                iter.value().append(item);
            }
            else
            {
                TestScriptSigDataList_t list;
                list.append(item);
                test_data_.insert(msgsig, list);
            }
        }
    }
}


TestScriptSigList_t TestScriptParser::getAllSignals()
{
    return test_data_.keys();
}

TestDataMap_t TestScriptParser::getTestData()
{
    return test_data_;
}

uint64_t TestScriptParser::getTestScriptTick()
{
    return max_tick_;
}

uint64_t TestScriptParser::getBeatNs()
{
    return beat_ns_;
}

uint64_t TestScriptParser::sToNum(QString sStr)
{
    // 提取单位
    QString uintStr;
    QString numStr;

    for (int m=0; m<sStr.length(); m++)
    {
        if ((sStr.at(m) >= '0' && sStr.at(m) <= '9'))
            numStr.append(sStr.at(m));
        else
            uintStr.append(sStr.at(m));
    }

    int64_t ms = numStr.toLongLong();

    if (uintStr.contains("ns", Qt::CaseInsensitive))
    {
        return ms;
    }
    else if (uintStr.contains("us", Qt::CaseInsensitive))
    {
        return ms * 1000;
    }
    else if (uintStr.contains("ms", Qt::CaseInsensitive))
    {
        return ms * 1000000;
    }
    else
    {
        return ms * 1000000000;
    }
}
