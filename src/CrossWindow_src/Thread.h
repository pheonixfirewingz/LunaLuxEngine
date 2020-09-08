//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_THREAD_H
#define LUNALUXENGINE_THREAD_H

#include <LLESDK/types.h>
#include "threads/common/IThread.h"
#ifdef LLE_WINDOWS
#include "threads/windows/Win32Thread.h"
#endif

class Thread
{
private:
    IThread* thread;
public:
    Thread()
    {
#ifdef LLE_WINDOWS
        thread = new Win32Thread();
#endif
    }

    ~Thread()
    {
        join();
    }

    void outputThreadInfo();
    void create(void*,void*);
    void start();
    void pause();
    void sleep(int);
    void join();
};


#endif //LUNALUXENGINE_THREAD_H
