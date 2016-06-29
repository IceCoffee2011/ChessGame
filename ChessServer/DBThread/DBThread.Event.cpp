#include "DBThread.h"
#include "Mysql/mysqlquery.h"
#include "Protol/CSProtol.h"
#include "Protol/ServerInternal.h"
#include "RoLog/RoLog.h"
#include "EventBuffer/EventBuffer.h"
#include "EventBuffer/EventBufferRecycle.h"
#include <string.h>
#include <mysql/errmsg.h>
#include <thread>
#include <signal.h>
#include <sys/types.h>

namespace chess
{
void CDBThread::ProcessEvent(SEventBuffer *pEventBuffer)
{
begin_flag :
    switch ( pEventBuffer->m_uEventType )
    {
    case CS_LOGIN :
        On_CS_LOGIN(pEventBuffer);
        break;
    case CS_REGISTER:
        On_CS_REGISTER(pEventBuffer);
        break;
    case SD_SAVE_MSG:
        On_SD_SAVE_MSG(pEventBuffer);
        break;
    default :
        START_LOG(RO_CERR).OUT_LOG("Unown EventkType")
                .BUILD_LOG(pEventBuffer->m_uEventType).END_LOG();
    }

    // 如果发现数据库服务器断开链接啦
    if ( m_xConn->GetLastErrorNo () == CR_SERVER_GONE_ERROR )
    {
        unsigned uRetryCount = 0;

        while ( m_xConn->Ping () == false && uRetryCount < m_uRetryMaxCount )
        {
            std::this_thread::sleep_for(std::chrono::seconds(m_uRetrySleepSeconds));
        }

        if ( uRetryCount >= m_uRetryMaxCount )
        {
            START_LOG(RO_CERR)
                    .OUT_LOG("Retry max to connect db "
                             ", server exit !").END_LOG();
            raise(SIGINT);
        }
        else
        {
            goto begin_flag;
        }
    }

    g_pEventBufferRecycle->RecycleEventBuffer ( pEventBuffer );
}

void CDBThread::On_CS_LOGIN(SEventBuffer *pEventBuffer)
{
    const SCS_LOGIN* pLogin = static_cast<const SCS_LOGIN*>( pEventBuffer->GetEventParamPtr ());

    MySQLQuery query(m_xConn, "CALL cup_Login(?, ?)");

    query.setString (1, pLogin->m_szUserName);
    query.setString (2, pLogin->m_szPassword);

    SSC_LOGIN_ACK xLoginACK;

    memcpy (xLoginACK.m_szUserName, pLogin->m_szUserName,
            sizeof(xLoginACK.m_szUserName));
    xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::UNKOWN_ERROR;

    if ( query.ExecuteQuery () )
    {
        int ret = query.getInt (1, 0);

        if ( ret == 0 )
        {
            xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::LOGIN_OK;
        }
        else
        {
            xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::PASSWORD_ERROR;
        }
    }

    PutEventToUserMgr(pEventBuffer->m_uTraceID,
                      SC_LOGIN_ACK, xLoginACK);
}

void CDBThread::On_CS_REGISTER(SEventBuffer *pEventBuffer)
{
    MySQLQuery query(m_xConn, "CALL cup_Register(?, ?)");
    const SCS_REGISTER* pRegister = static_cast<SCS_REGISTER const*> (pEventBuffer->GetEventParamPtr ());

    query.setString (1, pRegister->m_szUserName);
    query.setString (2, pRegister->m_szPassword);

    SSC_REGISTER_ACK xRegisterACK;
    memcpy (xRegisterACK.m_szUserName, pRegister->m_szUserName,
            sizeof(pRegister->m_szUserName));
    xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::UNKOWN_ERROR;

    if ( query.ExecuteQuery () )
    {
        int ret = query.getInt (1, 0);

        if ( ret == 0 )
        {
            xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::REGISTER_OK;
        }
        else
        {
            xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::USERNAME_EXISTS;
        }
    }

    PutEventToUserMgr(pEventBuffer->m_uTraceID,
                      SC_REGISTER_ACK,
                      xRegisterACK);
}

void CDBThread::On_SD_SAVE_MSG(SEventBuffer *pEventBuffer)
{
    SSD_SAVE_MSG const* pSaveMsg = static_cast<SSD_SAVE_MSG*>(
                pEventBuffer->GetEventParamPtr () );
    MySQLQuery query(m_xConn, "CALL cup_SaveMsg(?, ?)");

    query.setString (1, pSaveMsg->m_szMessageFrom);
    query.setString (2, pSaveMsg->m_szMessageBody);

    query.ExecuteQuery ();
}

}
