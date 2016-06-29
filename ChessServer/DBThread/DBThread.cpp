#include "DBThread.h"
#include "SrvConfig/CSrvConfig.h"
#include "RoLog/RoLog.h"
#include "Mysql/mysqlquery.h"
#include "EventBuffer/EventBufferRecycle.h"
#include "EventBuffer/EventBuffer.h"

namespace chess
{
CDBThread::CDBThread()
{
    m_xConn = new MySQLConnection;
}

CDBThread::~CDBThread()
{
    delete m_xConn;
}

bool CDBThread::Init (unsigned uThreadIndex)
{
    m_uThreadIndex = uThreadIndex;
    m_uRetrySleepSeconds = g_pSrvConfig->GetDBRetrySleepSeconds();
    m_uRetryMaxCount = g_pSrvConfig->GetDBRetryMaxCount();

    CSrvConfig::_SMySQLConn const& xConnInfo = g_pSrvConfig->GetMySQLConn ();

    m_xConn->Connect (xConnInfo.m_strHost,
                      xConnInfo.m_uPort,
                      xConnInfo.m_strUser,
                      xConnInfo.m_strPassword,
                      xConnInfo.m_strDatabase);
    return m_uRetrySleepSeconds > 0 && m_xConn->IsConnected ();
}

}
