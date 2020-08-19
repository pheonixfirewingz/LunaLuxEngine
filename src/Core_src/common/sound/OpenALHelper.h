//
// Created by luket on 07/08/2020.
//

#ifndef LUNALUXENGINE_OPENALHELPER_H
#define LUNALUXENGINE_OPENALHELPER_H

#include <AL/al.h>
#include <AL/alc.h>

class OAL
{
private:
    static OAL *m_instance;
    bool m_loaded_OAL = false;
public:
    ~OAL()
    {
        if (m_loaded_OAL != true)
        { closeAL(); }
        m_instance = nullptr;
    }

    static OAL *getInstance()
    {
        m_instance = new OAL();
        return m_instance;
    }

    int InitAL();

    void closeAL();

    ALuint LoadSound(const char *filename);
};

#endif //LUNALUXENGINE_OPENALHELPER_H
