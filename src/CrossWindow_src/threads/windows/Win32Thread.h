//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_WIN32THREAD_H
#define LUNALUXENGINE_WIN32THREAD_H
#include "../common/IThread.h"
#ifdef LLE_WINDOWS
#include <windows.h>
#include <synchapi.h>

class Win32Thread : public IThread
{
private:
    HANDLE thread;
public:
    void outputThreadInfo() override;

    void create(void*,void*) override;

    void start() override;

    void pause() override;

    void sleep(int) override;

    void join() override;

    ~Win32Thread();
};
#endif
#endif //LUNALUXENGINE_WIN32THREAD_H