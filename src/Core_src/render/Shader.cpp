#include "Shader.h"
#include "OpenGL/glad.h"

void LunaLuxEngine::Shader::compile(char* filedata, char* filedata1)
{
	Vshader->create(filedata, 0);
	Fshader->create(filedata1, 1);
    bind();
    Vshader->link(openGLshaderprogramid);
    UnBind();
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

void LunaLuxEngine::Shader::use()
{
    Vshader->use(openGLshaderprogramid);
}

LunaLuxEngine::Shader::Shader()
{
    Vshader = new OpenGLShader();
    Fshader = new OpenGLShader();
    openGLshaderprogramid = glCreateProgram();
}

LunaLuxEngine::Shader::~Shader()
{
    glDeleteProgram(openGLshaderprogramid);
    openGLshaderprogramid = 0;
}
