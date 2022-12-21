#include "vvpreviewdata.h"
#include <algorithm>
#include <memory>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include "configuration.h"
#include "WinringLogger.h"
#include "icdloadershuck.h"
#include "ICDController.h"
#include "../WRMemLeaksAssist.h"

VVPreviewData::VVPreviewData(QString workspace, QString vvfile, QObject *parent)
    : QThread(parent)
    , read_sucess_(false)
    ,filePath(vvfile)
{

    Configuration::getInstance()->wrp_workspace = workspace;

    if(Configuration::getInstance()->_ICDController == nullptr)
    {
        loadICD();
    }


    parser_.reset(new TestScriptParser(vvfile));
    QFileInfo fileinfo(vvfile);
    base_name_ = fileinfo.completeBaseName();
}

MsgData_t VVPreviewData::getMsgData()
{
    return msg_data_;
}

QString VVPreviewData::getBaseName()
{
    return base_name_;
}

double VVPreviewData::getTick_ns() const
{
    return tick_ns_;
}

bool VVPreviewData::loadICD()
{
    //1.先删除原有的controller
    if(Configuration::getInstance()->_ICDController != nullptr)
    {
        //不删除
    }
    //2.先判断icd的目录是否存在
    QString icd_dir = Configuration::getInstance()->wrp_workspace + "/metaData";
    QDir dir(icd_dir);
    if(dir.exists() == false)
    {
        QString str(QStringLiteral("存放ICD的metaData目录不存在！"));
        WINRING::LOG::WinringLogger::instance().setLogToDisplay(WINRING::LOG::err, str.toStdWString());
        Configuration::getInstance()->_ICDController = nullptr;
        return false;
    }
    //3.

    bool result = WRPEngine::tj::ICDLoaderShuck::instance().setICDLoader(icd_dir.toStdWString());
    WRPEngine::tj::ICDLoaderShuck::instance().setDefautValueToICD();
    if(result == false)
    {
        QString str(QStringLiteral("加载ICD失败！"));
        WINRING::LOG::WinringLogger::instance().setLogToDisplay(WINRING::LOG::err, str.toStdWString());
        Configuration::getInstance()->_ICDController = nullptr;
        return false;
    }
    Configuration::getInstance()->_ICDController = WRPEngine::tj::ICDLoaderShuck::instance().getICDController();
    QString str(QStringLiteral("加载ICD成功！"));
    WINRING::LOG::WinringLogger::instance().setLogToDisplay(WINRING::LOG::info, str.toStdWString());
    return true;
}


void VVPreviewData::run()
{
    if(parser_ == nullptr)
        return;
    tick_ns_ = parser_->getBeatNs();
    TestDataMap_t test_data = parser_->getTestData();
    for (auto iter = test_data.begin(); iter != test_data.end(); ++iter)
    {
        auto item = iter.value();
        SigData_t sig_data;
        auto msgsig = iter.key();
        sig_data.sigid_ = msgsig.sigid;

        //获取ICD的初始值
        double value = 0;
        ReturnValue ret_value = WRPEngine::tj::ICDLoaderShuck::instance().getSignalValue(msgsig.msgid.toStdWString(), msgsig.sigid.toStdWString(), -1);
        if(ret_value.type == SignalDataType::_unknown) continue;
        switch (ret_value.type)
        {
        case SignalDataType::uint64:
            value = (uint64_t)ret_value;
            break;
        case SignalDataType::uint32:
        case SignalDataType::bit32:
            value = (uint32_t)ret_value;
            break;
        case SignalDataType::uint16:
        case SignalDataType::bit16:
            value = (uint16_t)ret_value;
            break;
        case SignalDataType::uint8:
        case SignalDataType::bit8:
        case SignalDataType::_byte:
            value = (uint8_t)ret_value;
            break;
        case SignalDataType::int32:
            value = (int32_t)ret_value;
            break;
        case SignalDataType::int64:
            value = (int64_t)ret_value;
            break;
        case SignalDataType::int16:
            value = (int16_t)ret_value;
            break;
        case SignalDataType::int8:
        case SignalDataType::_char:
            value = (char)ret_value;
            break;
        case SignalDataType::real32:
        case SignalDataType::_float:
            value = (float)ret_value;
            break;
        case SignalDataType::real64:
        case SignalDataType::_double:
            value = (double)ret_value;
            break;
        case SignalDataType::_bool:
            value = (bool)ret_value;
            break;
        default:
            break;
        }

        sig_data.data_.append(QPointF(0, value)); //加入ICD的初始值

        uint64_t pre_tick = 0;
        for (int i = 0; i < item.size(); ++i)
        {
            uint64_t tick = item.at(i).current_step;
            value = item.at(i).value;
            if(tick != pre_tick+1)
            {
                double y = sig_data.data_.last().y();
                sig_data.data_.append(QPointF(tick, y));
            }
            pre_tick = tick;
            sig_data.data_.append(QPointF(tick, value));
        }

        auto find_iter = msg_data_.find(msgsig.msgid);
        if(find_iter != msg_data_.end())
        {
            find_iter.value().insert(msgsig.sigid, sig_data);
        }
        else
        {
            SigDataMap_t sigdatamap;
            sigdatamap.insert(msgsig.sigid, sig_data);
            msg_data_.insert(msgsig.msgid, sigdatamap);
        }

    }

    read_sucess_ = true;
    emit sigDataOk(filePath,tick_ns_);
}
