//
// Created by a1767 on 2023/8/24.
//

#ifndef BYTIMER_SINGLETON_H
#define BYTIMER_SINGLETON_H

namespace by
{
    template <typename T>
    class singleton
    {
    public:
        static T*getInstance()
        {
            static T instance; // 静态局部变量,在程序结束时会被销毁
            return &instance;
        }
    private:
        singleton()= default;
        singleton(const singleton&)= delete;
        singleton&operator=(const singleton&)= delete;
    };

#define SINGLETON(classname) \
    friend class by::singleton<classname>; \
    private:                \
    classname(const classname&)= delete; \
    classname&operator=(const classname&)= delete; \
    classname()= default;    \
    ~classname()=default;
}


#endif //BYTIMER_SINGLETON_H
