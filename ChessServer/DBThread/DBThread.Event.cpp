#include "DBThread.h"
#include "Protol/CSProtol.h"
#include "Protol/ServerInternal.h"
#include "RoLog/RoLog.h"
#include "EventBuffer/EventBuffer.h"
#include "EventBuffer/EventBufferRecycle.h"
#include <string.h>
#include <mysql/errmsg.h>
#include <thread>

#include "sqlite/sqlite3.h"

namespace chess
{
void CDBThread::ProcessEvent(SEventBuffer *pEventBuffer)
{
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

    g_pEventBufferRecycle->RecycleEventBuffer ( pEventBuffer );
}

void CDBThread::On_CS_LOGIN(SEventBuffer *pEventBuffer)
{
    const SCS_LOGIN* pLogin = static_cast<const SCS_LOGIN*>( pEventBuffer->GetEventParamPtr ());

    SSC_LOGIN_ACK xLoginACK;

    memcpy (xLoginACK.m_szUserName, pLogin->m_szUserName,
            sizeof(xLoginACK.m_szUserName));
    xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::UNKOWN_ERROR;

    const char *szSql = "SELECT COUNT(*) FROM chess_user WHERE name = ? AND password = ? ";
    sqlite3_stmt *stm = NULL;

    if ( SQLITE_OK == sqlite3_prepare(m_pDB, szSql, -1, &stm, NULL ) )
    {
        sqlite3_bind_text( stm, 1, pLogin->m_szUserName, -1, SQLITE_STATIC );
        sqlite3_bind_text( stm, 2, pLogin->m_szPassword, -1, SQLITE_STATIC );

        int ret = sqlite3_step( stm );

        if ( ret == SQLITE_ROW )
        {
            int num = sqlite3_column_int(stm, 0 );

            if ( num == 1 )
            {
                xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::LOGIN_OK;
            }
            else
            {
                xLoginACK.m_uLoginResult = SSC_LOGIN_ACK::PASSWORD_ERROR;
            }
        }
        else
        {
            START_LOG(RO_CERR).OUT_LOG( sqlite3_errmsg( m_pDB ) ).END_LOG();
        }
    }
    else
    {
        START_LOG(RO_CERR).OUT_LOG( sqlite3_errmsg( m_pDB ) ).END_LOG();
    }

    sqlite3_finalize( stm );

    PutEventToUserMgr(pEventBuffer->m_uTraceID,
                      SC_LOGIN_ACK, xLoginACK);
}

void CDBThread::On_CS_REGISTER(SEventBuffer *pEventBuffer)
{
    const SCS_REGISTER* pRegister = static_cast<SCS_REGISTER const*> (pEventBuffer->GetEventParamPtr ());

    SSC_REGISTER_ACK xRegisterACK;
    memcpy (xRegisterACK.m_szUserName, pRegister->m_szUserName,
            sizeof(pRegister->m_szUserName));
    xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::UNKOWN_ERROR;

    sqlite3_stmt *stm = NULL;

    if ( SQLITE_OK == sqlite3_prepare(m_pDB, "SELECT * FROM chess_user WHERE name = ? ", -1, &stm, NULL) )
    {
        int ret =0;

        sqlite3_bind_text(stm, 1, pRegister->m_szUserName, -1, SQLITE_STATIC);
        ret = sqlite3_step(stm);

        if ( ret == SQLITE_ROW )
        {
            xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::USERNAME_EXISTS;
        }
        else if ( ret == SQLITE_DONE )
        {
            sqlite3_finalize(stm);

            ret = sqlite3_prepare(m_pDB, "INSERT INTO chess_user(name, password) VALUES(?, ?)", -1, &stm, NULL);
            if ( ret == SQLITE_OK )
            {
                sqlite3_bind_text(stm, 1, pRegister->m_szUserName, -1, SQLITE_STATIC);
                sqlite3_bind_text(stm, 1, pRegister->m_szPassword, -1, SQLITE_STATIC);

                if ( sqlite3_step(stm) == SQLITE_DONE )
                {
                    xRegisterACK.m_uRegisterResult = SSC_REGISTER_ACK::REGISTER_OK;
                }
            }
        }
    }

    if ( xRegisterACK.m_uRegisterResult != SSC_REGISTER_ACK::REGISTER_OK &&
         xRegisterACK.m_uRegisterResult != SSC_REGISTER_ACK::USERNAME_EXISTS )
    {
        START_LOG(RO_CERR).OUT_LOG( sqlite3_errmsg(m_pDB) ).END_LOG();
    }
    sqlite3_finalize( stm );

    PutEventToUserMgr(pEventBuffer->m_uTraceID,
                      SC_REGISTER_ACK,
                      xRegisterACK);
}

void CDBThread::On_SD_SAVE_MSG(SEventBuffer *pEventBuffer)
{
    SSD_SAVE_MSG const* pSaveMsg = static_cast<SSD_SAVE_MSG*>(
                pEventBuffer->GetEventParamPtr () );
    sqlite3_stmt *stm = NULL;

    int ret = sqlite3_prepare(m_pDB, "INSERT INTO chess_msg(id, user, what) VALUES(?, ?, ?)", -1, &stm, NULL) ;

    if ( ret == SQLITE_OK )
    {
        uint64_t id = time(NULL) << 32 + rand() % UINT32_MAX;

        sqlite3_bind_int64(stm, 1, id);
        sqlite3_bind_text(stm, 2, pSaveMsg->m_szMessageFrom, -1, NULL);
        sqlite3_bind_text(stm, 3, pSaveMsg->m_szMessageBody, -1, NULL);

        sqlite3_step(stm);
    }

    sqlite3_finalize( stm );
}

}
