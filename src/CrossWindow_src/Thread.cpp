//
// Created by luket on 07/09/2020.
//

#include "Thread.h"
void Thread::outputThreadInfo()
{
    thread->outputThreadInfo();
}

void Thread::create(void * ptr,void * pram)
{
    thread->create(ptr,pram);
}

void Thread::start()
{
    thread->start();
}

void Thread::join()
{
    thread->join();
}

void Thread::pause()
{
    thread->pause();
}

void Thread::sleep(int one)
{
    thread->sleep(one);
}
