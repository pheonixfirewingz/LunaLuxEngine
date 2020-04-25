#include	"OpenGLContext.h"
#include    "../../window/WindowAPI.h"

void LunaLuxEngine::OpenGLContext::create()
{
#ifdef WIN32
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
		24,0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	SetPixelFormat(GetDC(CWin.getWin32Window()), ChoosePixelFormat(GetDC(CWin.getWin32Window()), &pfd), &pfd);
	rc = wglCreateContext(GetDC(CWin.getWin32Window()));
	wglMakeCurrent(GetDC(CWin.getWin32Window()), rc);
#endif 

}

void LunaLuxEngine::OpenGLContext::swapBuffers()
{
#ifdef WIN32
	SwapBuffers(GetDC(CWin.getWin32Window()));
#endif
}

void LunaLuxEngine::OpenGLContext::destroy()
{
#ifdef WIN32
	ReleaseDC(CWin.getWin32Window(), GetDC(CWin.getWin32Window()));
	wglDeleteContext(rc);
#endif
}
