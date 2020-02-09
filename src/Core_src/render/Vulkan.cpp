//
// Created by luket on 16/01/2020.
//
#include "Vulkan.h"
#include <vector>

using namespace LunaLuxEngine;

VKAPI_ATTR VkBool32 VKAPI_CALL vkLLEDebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT  objectType, uint64_t  object, size_t  location, int32_t  messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    switch (flags)
    {
        case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
            printf("\n%s%s\n", "VK_DEBUG_REPORT_INFORMATION_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_WARNING_BIT_EXT: 
            printf("\n%s%s\n", "VK_DEBUG_REPORT_WARNING_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
            printf("\n%s%s\n", "VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_ERROR_BIT_EXT:
            printf("\n%s%s\n", "VK_DEBUG_REPORT_ERROR_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_DEBUG_BIT_EXT: 
            printf("\n%s%s\n", "VK_DEBUG_REPORT_DEBUG_BIT_EXT: ", pMessage);
        default:
            return false;
    }
}

void VKRenderer::initRender(window_api::CrossWindow* win)
{
	if (EnabledDebug) printf("%s\n", "Vulkan Debug Log");
	uint32 count = 0;
    VkResult result;
    /*==================================================================
     *						CREATES INSTANCE
     *=================================================================
     */
    VkApplicationInfo ai = {};
    ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ai.pApplicationName = reinterpret_cast<const char*>(win->getTitle());
    ai.applicationVersion = 1;
    ai.pEngineName = "LunaLuxEngine";
    ai.engineVersion = 002;
    ai.apiVersion = 1;
    const char* lay[] = {"VK_LAYER_LUNARG_standard_validation"};
#ifdef WIN32
    const char* ext[] = { "VK_KHR_surface",VK_KHR_PLATFOM_SUFRACE, VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
#endif // WIN32
    VkInstanceCreateInfo ici = {};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.flags = 0;
    ici.pNext = nullptr;
    ici.pApplicationInfo = &ai;
    ici.enabledLayerCount = 1;
    ici.ppEnabledLayerNames = lay;
    ici.enabledExtensionCount = 3;
    ici.ppEnabledExtensionNames = ext;

    result = vkCreateInstance(&ici, nullptr,&instance);

    CHECK(result)

    if (EnabledDebug)
    {
        VkDebugReportCallbackCreateInfoEXT reportCallbackCreateInfoExt = {};
		reportCallbackCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		reportCallbackCreateInfoExt.pNext = nullptr;
		reportCallbackCreateInfoExt.pfnCallback = vkLLEDebugCallback;
		reportCallbackCreateInfoExt.flags = 1 | 2 | 4 | 8 | 10;
		reportCallbackCreateInfoExt.pUserData = nullptr;
        auto vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
        CHECK_P(vkCreateDebugReportCallbackEXT)
        result = vkCreateDebugReportCallbackEXT(instance, &reportCallbackCreateInfoExt, nullptr, &debug_ext);
        CHECK(result)
    }
    /*==================================================================
     *					CREATES PHYSICAL DEVICE
     *=================================================================
     */
	result = vkEnumeratePhysicalDevices(instance,&count, nullptr);

    CHECK(result)

    std::vector<VkPhysicalDevice> physical_device(count);

    result = vkEnumeratePhysicalDevices(instance, &count, physical_device.data());

    CHECK(result)
    if (physical_device.size() == 1)
    {
        pDevice = physical_device[0];

        VkPhysicalDeviceProperties dProp;

        memset(&dProp, 0, sizeof dProp);

        vkGetPhysicalDeviceProperties(physical_device[0], &dProp);

        if (EnabledDebug) printf("%s%s%s%s%i\n","Your Gpu Is", "(GPU NAME):",dProp.deviceName," (DRIVER VERSION):", dProp.driverVersion);
    }
    else
    {
        std::vector<VkPhysicalDevice> physical_device_X(count);

        for (uint32 i = 0; i < count; i++)
        {
            VkPhysicalDeviceProperties dProp;

            memset(&dProp, 0, sizeof dProp);

            vkGetPhysicalDeviceProperties(physical_device[i], &dProp);

            if (dProp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
				physical_device_X.push_back(physical_device[i]);

                if(EnabledDebug) printf("%s%s%s%s%i\n", "adding gpu to accepted list:", " (GPU NAME):", dProp.deviceName, " (DRIVER VERSION):", dProp.driverVersion);
            }
            else if(EnabledDebug) printf("%s%s%s%s%i\n", "rejected gpu from list:", " (GPU NAME):", dProp.deviceName, " (DRIVER VERSION):", dProp.driverVersion);
        }
        if (physical_device_X.size() == 1) pDevice = physical_device_X[0];
        else
        {
            if (EnabledDebug) printf("%s\n", "More that one non Intergrated Gpu Randomly choicing one");
            int8 nam = rand() % physical_device.size() + 1;
            pDevice = physical_device_X[nam];
        }
    }
    /*==================================================================
     *							CREATES DEVICE
     *=================================================================
     */
    vkGetPhysicalDeviceQueueFamilyProperties(pDevice, &count, nullptr);
    std::vector<VkQueueFamilyProperties> Family_Properties (count);
    vkGetPhysicalDeviceQueueFamilyProperties(pDevice, &count, Family_Properties.data());

    bool found = false;
    int8 index_number = 0;

    for (uint32 i = 0; i < count; i++)
        if (Family_Properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            found = true;
			index_number = i;
        }

    CHECK_B(found);

    float queue_p[] { 1.0f  };

    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};

	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

	deviceQueueCreateInfo.queueFamilyIndex = index_number;

	deviceQueueCreateInfo.queueCount = 1;

	deviceQueueCreateInfo.pQueuePriorities = queue_p;

    const char* dLayers[] = { "VK_KHR_swapchain" };

    VkDeviceCreateInfo deviceCreateInfo = {};

	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	deviceCreateInfo.pNext = nullptr;

	deviceCreateInfo.queueCreateInfoCount = 1;

	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

	deviceCreateInfo.enabledExtensionCount = 1;

	deviceCreateInfo.ppEnabledExtensionNames = dLayers;

	deviceCreateInfo.enabledLayerCount = 1;

	deviceCreateInfo.ppEnabledLayerNames = lay;

    VkPhysicalDeviceFeatures features = {};
    features.shaderClipDistance = VK_TRUE;

	deviceCreateInfo.pEnabledFeatures = &features;

  result = vkCreateDevice(pDevice, &deviceCreateInfo, nullptr, &device);

  CHECK(result);
  /*==================================================================
   *						CREATES SURFACE
   *==================================================================
   */
  HINSTANCE hInst = GetModuleHandle(nullptr);

  VkWin32SurfaceCreateInfoKHR surf_ = {};
  surf_.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surf_.hinstance = hInst;
  surf_.hwnd = win->getWindow();

  result = vkCreateWin32SurfaceKHR(instance, &surf_, nullptr, &surface);

  CHECK(result);

  VkSurfaceCapabilitiesKHR surfaceCapabilities = {};

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice, surface, &surfaceCapabilities);

  int16 width_, height_;

  VkExtent2D scrres;

  scrres.height = win->getWindowH();

  scrres.width = win->getWindowW();

  /*==================================================================
   *						CREATES SWAPCHAIN
   *==================================================================
   */

  VkSwapchainCreateInfoKHR swcninf = {};
  swcninf.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swcninf.surface = surface;
  swcninf.minImageCount = 2;
  swcninf.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
  swcninf.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
  swcninf.imageExtent = scrres;
  swcninf.imageArrayLayers = 1;
  swcninf.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swcninf.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  swcninf.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  swcninf.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swcninf.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
  swcninf.clipped = true;
  swcninf.oldSwapchain = nullptr;

  result = vkCreateSwapchainKHR(device, &swcninf, nullptr, &swapChain);

  CHECK(result)

 result =  vkGetSwapchainImagesKHR(device, swapChain, &count, nullptr);
 
 CHECK(result)

  image = new VkImage[0];

  result = vkGetSwapchainImagesKHR(device, swapChain, &count, image);

  CHECK(result)

  image_v = new VkImageView[2];

  for (uint8 i = 0; i < 2; i++)
  {
      VkImageViewCreateInfo viewCreateInfo = {};
	  viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	  viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	  viewCreateInfo.format = VK_FORMAT_B8G8R8A8_UNORM;
	  viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	  viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
	  viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	  viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
	  viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	  viewCreateInfo.subresourceRange.baseMipLevel = 0;
	  viewCreateInfo.subresourceRange.levelCount = 1;
	  viewCreateInfo.subresourceRange.baseArrayLayer = 0;
	  viewCreateInfo.subresourceRange.layerCount = 1;
	  viewCreateInfo.image = image[i];

      result = vkCreateImageView(device,&viewCreateInfo , nullptr, &image_v[i]);
      CHECK(result)
  }

}

void VKRenderer::destroyRender()
{
    vkDestroyDevice(device, nullptr);
    if (EnabledDebug)
    {
        auto vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
        CHECK_P(vkDestroyDebugReportCallbackEXT)
        vkDestroyDebugReportCallbackEXT(instance, debug_ext, nullptr);
    }
    vkDestroyInstance(instance, nullptr);
}

void VKRenderer::fireRender()
{

}

void VKRenderer::prepRender()
{

}
