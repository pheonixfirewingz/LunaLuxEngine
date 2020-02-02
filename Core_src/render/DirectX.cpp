//
// Created by luket on 23/01/2020.
//
#include "IRender.h"
#ifdef WIN32
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d11.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d10.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d10_1.lib" )
#include <d3d11.h>

void IRender::initRender(HWND hwnd)
{
}

void IRender::destroyRender()
{

}

void IRender::fireRender()
{

}

void IRender::prepRender()
{

}
#endif