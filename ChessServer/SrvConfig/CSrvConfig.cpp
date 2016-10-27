#include "CSrvConfig.h"
#include "RoLog/RoLog.h"
#include "inifile/inifile.h"

#define CHECK_RET( ret ) if ( ret != 0 ) \
{\
START_LOG(RO_CERR).OUT_LOG("Get value error !").END_LOG();\
return false;\
}

namespace chess
{

bool CSrvConfig::Init(const char *szFileName)
{
    inifile::IniFile file;

    if ( 0 != file.load (szFileName) )
    {
        START_LOG(RO_CERR).OUT_LOG("Open file error : ").BUILD_LOG( szFileName ).END_LOG();

        return false;
    }

    std::string strSection = "ChessServer";
    int ret ;

    m_uMaxUserCount =  file.getIntValue (strSection, "MaxUserCount", ret );
    CHECK_RET(ret);

    m_uListenPort = file.getIntValue (strSection, "ListenPort", ret);
    CHECK_RET(ret);

    m_uRecvBufferByte = file.getIntValue (strSection, "RecvBufferByte", ret);
    CHECK_RET( ret );

    m_iHeartBeatOverTime = file.getIntValue (strSection, "HeartBeatOverTime", ret);
    CHECK_RET(ret);

    strSection = "SQLITE";

    m_strDBfilename = file.getStringValue (strSection, "file", ret);
    CHECK_RET( ret );

    return true;
}

}
