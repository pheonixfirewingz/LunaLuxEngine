//
// Created by luket on 07/09/2020.
//

#include "Thread.h"
void Thread::outputThreadInfo()
{
    thread->outputThreadInfo();
}

void Thread::create(void * ptr)
{
    thread->create(ptr);
}

void Thread::start()
{
    thread->start();
}

void *Thread::join()
{
    return thread->join();
}
