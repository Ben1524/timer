#include <iostream>
#include "multiThreadTimer.h"
#include "timelineTimer.h"

void test1()
{
    std::cout<<"test1"<<std::endl;
}
void test2(int a)
{
    std::cout<<"test2  "<<a<<std::endl;
}
void test3(int a,int b)
{
    std::cout<<"test3  "<<a<<"----"<<b<<std::endl;
}


int main()
{
    auto timerMan=by::singleton<by::timerManager>::getInstance();
    timerMan->addTimer(1000,test1);
    timerMan->addTimer(1000,2,test2,1);
    timerMan->addTimer(1000,2,test3,1,2);
    auto run=std::bind(&by::timerManager::start,timerMan);


    return 0;
}

