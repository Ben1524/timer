//
// Created by a1767 on 2023/8/24.
//

#include "multiThreadTimer.h"

using namespace by;

multiThreadTimer::multiThreadTimer():
m_isRunning(false),m_interval(0),repeatCount(-1)
{

}

by::multiThreadTimer::~multiThreadTimer()
{
    stop();
}

void multiThreadTimer::stop()
{
    m_isRunning.store(false);
    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

void multiThreadTimer::setRepeatCount(int count)
{
    repeatCount = count;
}

multiThreadTimer::multiThreadTimer(int repeatCount):
m_isRunning(false),m_interval(0),repeatCount(repeatCount)
{
}
