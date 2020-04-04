#include "Shader.h"
#include <glad/glad.h>

void LunaLuxEngine::Shader::create()
{
	if (lunaLuxEngine::get()->currentAPItype == 0)
	{
		Vshader = new OpenGLShader();
		Fshader = new OpenGLShader();
		openGLshaderprogramid = glCreateProgram();
	}
}

void LunaLuxEngine::Shader::compile(char* filedata, char* filedata1)
{
	Vshader->create(filedata, 0);
	Fshader->create(filedata1, 1);
}

void LunaLuxEngine::Shader::bind()
{
	Vshader->bind(openGLshaderprogramid);
	Fshader->bind(openGLshaderprogramid);
}

void LunaLuxEngine::Shader::UnBind()
{
	Vshader->unBind(openGLshaderprogramid);
	Fshader->unBind(openGLshaderprogramid);
}

void LunaLuxEngine::Shader::link()
{
	bind();
	Vshader->link(openGLshaderprogramid);
	UnBind();
}

void LunaLuxEngine::Shader::destory()
{
	if (lunaLuxEngine::get()->currentAPItype == 0)
	{
		glDeleteProgram(openGLshaderprogramid);
		openGLshaderprogramid = 0;
	}
	Vshader->destory();
	Vshader = nullptr;
	Fshader->destory();
	Fshader = nullptr;
}
