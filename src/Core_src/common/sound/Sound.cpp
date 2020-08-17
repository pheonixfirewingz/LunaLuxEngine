//
// Created by luket on 07/08/2020.
//

#include "Sound.h"

void Sound::createSound(char *file)
{
    if (m_device != nullptr)
    {
        m_device = OAL::getInstance();
    }

    //need to create buffer from file
}

void Sound::destroySound()
{
    if (!m_device)
    { return; }
    alSourceStop(source);

    //need to destroy buffer

    m_device->closeAL();
}

void Sound::pause()
{
    alSourcePause(source);
}

void Sound::play()
{
    alSourcePlay(source);
}