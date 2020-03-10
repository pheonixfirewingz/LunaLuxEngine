#include "GPUInstance.h"
#include <glad\glad.h>

namespace LunaLuxEngine
{
	void GPUInstance::Release()
	{
		if (device->vk_device != nullptr) vkDestroyDevice(*device->vk_device, nullptr);
		if (device->vk_instance != nullptr) vkDestroyInstance(device->vk_instance, nullptr);
		if (device->dc != nullptr)ReleaseDC(CWin.getWindow(), device->dc);
		if (device->rc != nullptr)wglDeleteContext(device->rc);
	}

	void GPUInstance::createOGLGPUInstance()
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24,0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
		};
		device->dc = GetDC(CWin.getWindow());
		int pf = ChoosePixelFormat(device->dc, &pfd);
		SetPixelFormat(device->dc, pf, &pfd);
		device->rc = wglCreateContext(device->dc);
		wglMakeCurrent(device->dc, device->rc);
	}
};