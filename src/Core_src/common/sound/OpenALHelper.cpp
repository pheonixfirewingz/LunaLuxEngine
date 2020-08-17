//
// Created by luket on 07/08/2020.
//

#include "OpenALHelper.h"
#include <cstdio>

int OAL::InitAL()
{
    const ALCchar *name = nullptr;
    ALCdevice *device = nullptr;

    /* Open and initialize a device */
    if (!device)
    { device = alcOpenDevice(nullptr); }

    if (!device)
    {
        fprintf(stderr, "Could not open a device!\n");
        m_loaded_OAL = false;
        return 1;
    }

    ALCcontext *ctx = alcCreateContext(device, nullptr);
    if (ctx == nullptr || alcMakeContextCurrent(ctx) == ALC_FALSE)
    {
        if (ctx != nullptr)
        { alcDestroyContext(ctx); }

        alcCloseDevice(device);
        fprintf(stderr, "Could not set a context!\n");
        m_loaded_OAL = false;
        return 1;
    }

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(device,
                            ALC_ALL_DEVICES_SPECIFIER);
    }

    if (!name || alcGetError(device) != AL_NO_ERROR)
    { name = alcGetString(device, ALC_DEVICE_SPECIFIER); }

    printf("Opened \"%s\"\n", name);
    m_loaded_OAL = true;
    return 0;
}

void OAL::closeAL()
{
    ALCdevice *device;
    ALCcontext *ctx;

    ctx = alcGetCurrentContext();

    if (ctx == nullptr)
    { return; }

    device = alcGetContextsDevice(ctx);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(ctx);
    alcCloseDevice(device);
    m_loaded_OAL = false;
}