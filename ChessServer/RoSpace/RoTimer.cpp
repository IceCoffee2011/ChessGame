#include "RoTimer.h"
#include <assert.h>
#include "RoLog/RoLog.h"

namespace RoSpace
{
CTimer::CTimer(unsigned uDuration, bool bAutoStart)
    : m_bIsRuning( bAutoStart ), m_uDuration(uDuration)
{
    m_tmBegin = time(NULL);
}

void CTimer::ReStart()
{
    ReStart ( m_uDuration );
}

void CTimer::ReStart(unsigned uNewDurationSeconds)
{
    m_bIsRuning = true;
    m_tmBegin = time(NULL);
    m_uDuration = uNewDurationSeconds;
}

bool CTimer::IsTimeout() const
{
    if ( IsRuning () )
    {
        time_t tmNow = time(NULL);

        if ( tmNow - m_tmBegin >= m_uDuration )
        {
            return true;
        }
    }

    return false;
}

}
