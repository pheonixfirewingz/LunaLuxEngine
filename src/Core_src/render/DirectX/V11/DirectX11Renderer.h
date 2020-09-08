//
// Created by luket on 31/08/2020.
//

#ifndef LUNALUXENGINE_DIRECTX11RENDERER_H
#define LUNALUXENGINE_DIRECTX11RENDERER_H
#include "../../Common/IRender.h"

namespace LunaLuxEngine
{
    class DX11Renderer : public IRender
    {
    public:
        void clearscreen(float colour[4]) override;

        void prepRender() override
        {};

        void fireRender(int i) override;
    };
}
#endif //LUNALUXENGINE_DIRECTX11RENDERER_H
