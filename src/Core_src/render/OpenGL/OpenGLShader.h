#ifndef LUNALUXENGINE_OPENGLSHADER_H
#define LUNALUXENGINE_OPENGLSHADER_H
#include <LLESDK/types.h>
#include "../Common/IShader.h"

namespace LunaLuxEngine
{
	class OpenGLShader : public IShader
	{
	private:
		int shaderid;
	public:
	    ~OpenGLShader();
		void create(char*, int) override;
		void bind(int) override;
		void unBind(int) override;
		void link(int) override;
	};
}

#endif
