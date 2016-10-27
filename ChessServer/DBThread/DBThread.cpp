#include "DBThread.h"
#include "SrvConfig/CSrvConfig.h"
#include "RoLog/RoLog.h"
#include "EventBuffer/EventBufferRecycle.h"
#include "EventBuffer/EventBuffer.h"
#include "sqlite/sqlite3.h"

namespace chess
{
CDBThread::CDBThread()
{
    m_pDB = NULL;
}

CDBThread::~CDBThread()
{
    sqlite3_close(m_pDB);
}

bool CDBThread::Init (unsigned uThreadIndex)
{
    m_uThreadIndex = uThreadIndex;

    int ret = sqlite3_open( g_pSrvConfig->GetDBFilename(), &m_pDB);

    return ret == SQLITE_OK;
}

}
