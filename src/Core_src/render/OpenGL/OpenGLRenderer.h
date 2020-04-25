//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_OPENGL_H
#define LUNALUXENGINE_OPENGL_H
#include <LLESDK/types.h>
#include "../Renderer.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../../render/Common/IRender.h"

namespace LunaLuxEngine
{
	class OGLRenderer : public IRender
	{
	public:
		void clearscreen(float[4]) override;
		void prepRender() override {};
		void initRender() override;
		void postRender() override {};
		void fireRender(int) override;
		void destroyRender() override;
	};
}
#endif
