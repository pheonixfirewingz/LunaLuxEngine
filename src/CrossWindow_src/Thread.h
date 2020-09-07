//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_THREAD_H
#define LUNALUXENGINE_THREAD_H


#include "threads/common/IThread.h"
#include "threads/windows/Win32Thread.h"

class Thread
{
private:
    IThread* thread;
public:
    Thread()
    {
        thread = new Win32Thread();
    }

    ~Thread()
    {
        join();
    }

    void outputThreadInfo();
    void create(void*);
    void start();
    void* join();
};


#endif //LUNALUXENGINE_THREAD_H
