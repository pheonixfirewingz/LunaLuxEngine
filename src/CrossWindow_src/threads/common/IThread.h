//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_ITHREAD_H
#define LUNALUXENGINE_ITHREAD_H
#include <LLESDK/types.h>
#ifdef LLE_WINDOWS
#define THREAD_FUN DWORD WINAPI
#define THREAD_FUN_RET return 0;
#elif LLE_LINUX
#define THREAD_FUN
#define THREAD_FUN_RET
#endif

class IThread
{
public:
    virtual void outputThreadInfo() = 0;
    virtual void create(void*,void*) = 0;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void sleep(int) = 0;
    virtual void join() = 0;
};

#endif //LUNALUXENGINE_ITHREAD_H
