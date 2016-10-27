#ifndef CSRVCONFIG_H
#define CSRVCONFIG_H

#include "RoSpace/RoSingleton.h"
#include "RoSpace/RoTypes.h"
#include <string>

namespace chess
{
using namespace RoSpace;

class CSrvConfig
        : public RoSpace::CSingleton<CSrvConfig>
{
public:
    bool Init(const char* szFileName);

    UINT       GetMaxUserCount() const { return m_uMaxUserCount; }
    USHORT GetListenPort() const { return m_uListenPort; }
    UINT       GetRecvBufferByte() const { return m_uRecvBufferByte; }
    UINT       GetDBThreadCount() const { return 1; } // 数据库线程数目恒定为1
    const char *GetDBFilename() const { return m_strDBfilename.c_str(); }
    int       GetHeartBeatOverTime() const { return m_iHeartBeatOverTime; }
private:
    UINT        m_uMaxUserCount;  // 最大用户数目
    USHORT  m_uListenPort;          // 监听端口
    UINT        m_uRecvBufferByte; // 接收缓冲区大小
    int            m_iHeartBeatOverTime; // 心跳包超时秒数
    std::string m_strDBfilename;
};
#define g_pSrvConfig chess::CSrvConfig::Instance ()

}
#endif // CSRVCONFIG_H
