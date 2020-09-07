//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_ITHREAD_H
#define LUNALUXENGINE_ITHREAD_H
#include <LLESDK/types.h>

class IThread
{
public:
    virtual void outputThreadInfo() = 0;
    virtual void create(void*) = 0;
    virtual void start() = 0;
    virtual void* join() = 0;
};

#endif //LUNALUXENGINE_ITHREAD_H
