#include "OpenGLShader.h"
#include "../../common/EnginePanic.h"
#include <vector>
#include "glad.h"
void LunaLuxEngine::OpenGLShader::create(char* filedata, int type)
{
	if (type == 0)
		shaderid = glCreateShader(GL_VERTEX_SHADER);
	else
		shaderid = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shaderid, 1, &filedata, 0);
	glCompileShader(shaderid);
	GLint state;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &state);
	if (state == GL_FALSE)
	{
		GLint maxl;
		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &maxl);

		std::vector<GLchar> info(maxl);

		glGetShaderInfoLog(shaderid, maxl, &maxl, &info[0]);

		glDeleteShader(shaderid);

		EnginePanic::get()->panic(info.data());
	}
}

void LunaLuxEngine::OpenGLShader::bind(int programid)
{
	glAttachShader(programid, shaderid);
}

void LunaLuxEngine::OpenGLShader::unBind(int programid)
{
	glDetachShader(programid, shaderid);
}

void LunaLuxEngine::OpenGLShader::link(int programid)
{
	glLinkProgram(programid);
	glUseProgram(programid);
}

void LunaLuxEngine::OpenGLShader::destory()
{
	glDeleteShader(shaderid);
}
