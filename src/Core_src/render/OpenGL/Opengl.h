//
// Created by digitech on 19/02/2020.
//

#ifndef LUNALUXENGINE_OPENGL_H
#define LUNALUXENGINE_OPENGL_H
#include "../Common/IRender.h"
#include <LLESDK/types.h>
#include "window/Opengl_h.h"
namespace LunaLuxEngine
{

	class OGLRenderer : public IRender
	{
	private:
#ifdef __linux__
		GLXContext glc;
#endif // !
	public:
		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void postRender() override;
		void destroyRender() override;
	};

}
#endif //LUNALUXENGINE_OPENGL_H
