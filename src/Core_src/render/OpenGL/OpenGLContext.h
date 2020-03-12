#ifndef LUNALUXENGINE_OPENGLCONTEXT_H
#define LUNALUXENGINE_OPENGLCONTEXT_H
#include <LLESDK/types.h>
#include <glad\glad.h>
#include "../../window/Window.h" 
#include "../Common/IContext.h"
#ifdef WIN32
#pragma comment(lib,"opengl32.lib")
#endif

namespace LunaLuxEngine
{
	class OpenGLContext : public IContext
	{
#ifdef WIN32
	private:
		HGLRC rc;
#endif
	public:
		void create() override;
		void swapBuffers() override;
		void destroy() override;
	};
}
#endif
