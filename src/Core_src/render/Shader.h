#ifndef LUNALUXENGINE_SHADER_H
#define LUNALUXENGINE_SHADER_H
#include "Common/IShader.h"
#include "OpenGL/OpenGLShader.h"
#include "../LunaLuxEngineCore.h"

namespace LunaLuxEngine
{
	class Shader
	{
		unsigned int openGLshaderprogramid;
	private:
		IShader* Vshader;
		IShader* Fshader;
	public:
	    Shader();
	    ~Shader();
		void compile(char* filedata, char* filedata1);
		void use();
		void bind();
		void UnBind();
		unsigned int getOGLSID()
        {
            return openGLshaderprogramid;
        }
	};
}
#endif