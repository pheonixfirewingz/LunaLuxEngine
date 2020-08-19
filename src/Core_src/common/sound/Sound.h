//
// Created by luket on 07/08/2020.
//

#ifndef LUNALUXENGINE_SOUND_H
#define LUNALUXENGINE_SOUND_H

#include <AL/al.h>
#include <AL/alc.h>
#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "OpenALHelper.h"

class Sound
{
private:
    ALuint source, buffer;
    OAL *m_device = nullptr;
    bool m_sound_alive = false;
public:
    void createSound(char *);

    void play();

    void pause();

    void destroySound();
};


#endif //LUNALUXENGINE_SOUND_H
