#ifndef CTIMER_H
#define CTIMER_H

#include <time.h>

namespace RoSpace
{
class CTimer
{
public:
    /**
     * @brief CTimer 构造函数
     * @param uDurationSeconds 计时器时间周期的秒数
     * @param bAutoStart 是否自动启动计时器
     */
    CTimer(unsigned uDurationSeconds=0, bool bAutoStart = true);

    /**
     * @brief ReStart 重启计时器
     */
    void ReStart();

    /**
     * @brief ReStart 重启计时器
     * @param uNewDurationSeconds 新的超时秒数
     */
    void ReStart(unsigned uNewDurationSeconds);

    /**
     * @brief Stop 停止计时器
     */
    void Stop() { m_bIsRuning = false; }

    /**
     * @brief IsTimeout 判断计时器时间是否到达
     * @return true -> 正在运行, 且时间到达了, false -> 其它情况
     */
    bool IsTimeout() const;
    /**
     * @brief IsRuning 判断计时器是否正在运行
     * @return true -> 正在运行, false -> 没有运行
     */
    bool IsRuning() const { return m_bIsRuning; }
private:
    bool m_bIsRuning; // 是否正在运行
    time_t m_tmBegin; // 启动时间
    unsigned m_uDuration; // 到达时间
};

}
#endif // CTIMER_H
