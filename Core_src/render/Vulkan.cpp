//
// Created by luket on 16/01/2020.
//
#include "Vulkan.h"
using namespace LunaLuxEngine;

void VKRenderer::initRender(window_api::CrossWindow* win)
{
	std::printf("%s\n", "Vulkan mode");
	uint32 count = 0;
	VkResult result = vkEnumerateInstanceLayerProperties(&count, nullptr);

	if(result != VK_SUCCESS) std::exit(-5);
    if(count > 0) std::exit(-51);

    std::vector<VkLayerProperties> instLay;

    result = vkEnumerateInstanceLayerProperties(&count,&instLay[0]);

    result = vkEnumerateInstanceExtensionProperties(nullptr,&count, nullptr);

    if(result != VK_SUCCESS) std::exit(-5);
    if(count > 0) std::exit(-51);

    std::vector<VkExtensionProperties> extPro;
    extPro.resize(count);

    result = vkEnumerateInstanceExtensionProperties(nullptr,&count, &extPro[0]);

    std::vector<std::string> extNam;
    extNam.resize(count);

    const char *layer[] = { "VK_LAYER_NV_optimus" };

    VkApplicationInfo ai = {};
    ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ai.pApplicationName = win->getTitle();
    ai.applicationVersion = 1;
    ai.pEngineName = "LunaLuxEngine";
    ai.engineVersion = 1;
    ai.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo ici = {};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.flags = 0;
    ici.pNext = 0;
    ici.pApplicationInfo = &ai;
    ici.enabledLayerCount = 1;
    ici.ppEnabledLayerNames = layer;
    ici.enabledExtensionCount = 3;
    ici.ppEnabledExtensionNames = extentions;

    VkResult result_ = vkCreateInstance(&ici, nullptr,&instance);

    if(result_ != VK_SUCCESS) std::exit(-5);

#ifdef WIN32
    HINSTANCE hInst = GetModuleHandle(NULL);
    HWND hwnd = win->getWindow();
#endif
}

void VKRenderer::destroyRender()
{
    instance = nullptr;
}

void VKRenderer::fireRender()
{

}

void VKRenderer::prepRender()
{

}
