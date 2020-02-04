//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_VULKAN_H
#define LUNALUXENGINE_VULKAN_H

#include "IRender.h"
#include <vulkan/vulkan.h>
#include "../window/Window.h"

namespace LunaLuxEngine
{
	class VKRenderer : public IRender
	{

		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif //LUNALUXENGINE_VULKAN_H
