//
// Created by luket on 07/09/2020.
//

#ifndef LUNALUXENGINE_WIN32THREAD_H
#define LUNALUXENGINE_WIN32THREAD_H
#include "../common/IThread.h"

class Win32Thread : public IThread
{
#ifdef LLE_WINDOWS
private:

public:
    void outputThreadInfo() override;

    void create(void *pVoid) override;

    void start() override;

    void *join() override;
#else
public:
    void outputThreadInfo() override { LOG("thread api that your trying to use is not supported on this OS")};

    void create(void *pVoid) override {};

    void start() override {};

    void *join() override { return nullptr; };
#endif
};


#endif //LUNALUXENGINE_WIN32THREAD_H
