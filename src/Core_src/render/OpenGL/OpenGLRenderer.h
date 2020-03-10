//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_OPENGL_H
#define LUNALUXENGINE_OPENGL_H
#include <LLESDK/types.h>
#include "../Renderer.h"
#include "../../render/Common/IRender.h"
#include <glad/glad.h>

namespace LunaLuxEngine
{
	class OGLRenderer : public IRender
	{
	public:
		void prepRender() override {};
		void initRender() override;
		void postRender() override {};
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif
