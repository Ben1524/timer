//
// Created by a1767 on 2023/8/24.
//

#ifndef BYTIMER_MULTITHREADTIMER_H
#define BYTIMER_MULTITHREADTIMER_H

#include <functional>
#include <thread>
#include <atomic>


namespace by
{
    class multiThreadTimer
    {
    public:
        using TimerCallback = std::function<void()>;
        multiThreadTimer();
        multiThreadTimer(const multiThreadTimer&)=delete;
        multiThreadTimer(int repeatCount);
        ~multiThreadTimer();

        template<typename F,typename...Args>
        void start(int interval,F&&f,Args&&...args);
        void setRepeatCount(int count);
        void stop();
    private:
        std::thread m_thread;
        std::atomic<bool> m_isRunning;
        TimerCallback m_callback;
        int m_interval; // ms
        int repeatCount;
    };
    template<typename F,typename...Args>
    void multiThreadTimer::start(int interval,F&&f,Args&&...args)
    {
        if(m_isRunning.load())
        {
            return;
        }
        m_interval  = interval;
        // 将回调函数和参数绑定,std::forward<F>(f)表示完美转发,将f的类型保持不变
        // 否则如果f是左值,则std::bind会将f拷贝一份,这样会导致f的类型变成右值
        // 完美转发可以保持f的类型不变
        m_callback = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        m_isRunning.store(true);
        m_thread = std::thread([this](){
            if(repeatCount<0)
            {
                while(m_isRunning.load())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
                    if(m_isRunning.load()) // 这里需要再次判断,因为如果在sleep的过程中,stop()被调用,则m_isRunning会被置为false
                    {
                        m_callback();
                    }
                    else
                    {
                        return;
                    }
                }
            }
            else if(repeatCount==0)
            {
                return;
            }
            else if(repeatCount>0)
            {
                while(repeatCount>0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
                    if(m_isRunning.load())
                    {
                        m_callback();
                    }
                    else
                    {
                        return;
                    }
                    repeatCount--;
                }
            }
        });
    }

}


#endif //BYTIMER_MULTITHREADTIMER_H
