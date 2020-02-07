//
// Created by luket on 16/01/2020.
//
#include "Vulkan.h"
#include <string>
using namespace LunaLuxEngine;

VKAPI_ATTR VkBool32 VKAPI_CALL vkLLEDebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT  objectType, uint64_t  object, size_t  location, int32_t  messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    switch (flags)
    {
        case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
            std::printf("\n%s%s\n", "VK_DEBUG_REPORT_INFORMATION_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_WARNING_BIT_EXT: 
            std::printf("\n%s%s\n", "VK_DEBUG_REPORT_WARNING_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
            std::printf("\n%s%s\n", "VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_ERROR_BIT_EXT:
            std::printf("\n%s%s\n", "VK_DEBUG_REPORT_ERROR_BIT_EXT: ", pMessage);
        case VK_DEBUG_REPORT_DEBUG_BIT_EXT: 
            std::printf("\n%s%s\n", "VK_DEBUG_REPORT_DEBUG_BIT_EXT: ", pMessage);
        default:
            return false;
    }
    return false;
}

void VKRenderer::initRender(window_api::CrossWindow* win)
{
    if (EnabledDebug) std::printf("%s\n", "Vulkan mode");
	uint32 count = 0;
    VkResult result;
    /*==================================================================
     *                                          CREATES INSTANCE
     *=================================================================
     */
    result = vkEnumerateInstanceLayerProperties(&count, nullptr);

	CHECK(result);

    std::vector<VkLayerProperties> instLay;
    instLay.resize(count);

    result = vkEnumerateInstanceLayerProperties(&count,&instLay[0]);

    result = vkEnumerateInstanceExtensionProperties(nullptr,&count, nullptr);

	CHECK(result);

    std::vector<VkExtensionProperties> extPro;
    extPro.resize(count);

    result = vkEnumerateInstanceExtensionProperties(nullptr,&count, &extPro[0]);

    CHECK(result);

    VkApplicationInfo ai = {};
    ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ai.pApplicationName = win->getTitle();
    ai.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    ai.pEngineName = "LunaLuxEngine";
    ai.engineVersion = VK_MAKE_VERSION(0,0,2);
    ai.apiVersion = VK_API_VERSION_1_0;
    const char* lay[] = {"VK_LAYER_LUNARG_standard_validation"};
#ifdef WIN32
    const char* ext[] = { "VK_KHR_surface",VK_KHR_PLATFOM_SUFRACE, VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
#endif // WIN32
    VkInstanceCreateInfo ici = {};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.flags = 0;
    ici.pNext = 0;
    ici.pApplicationInfo = &ai;
    ici.enabledLayerCount = 1;
    ici.ppEnabledLayerNames = lay;
    ici.enabledExtensionCount = 3;
    ici.ppEnabledExtensionNames =ext ;

    result = vkCreateInstance(&ici, nullptr,&instance);

    CHECK(result);

    if (EnabledDebug)
    {
        VkDebugReportCallbackCreateInfoEXT deinf = {};
        deinf.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        deinf.pNext = nullptr;
        deinf.pfnCallback = vkLLEDebugCallback;
        deinf.flags = VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT;
        deinf.pUserData = nullptr;
        PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
        CHECKP(vkCreateDebugReportCallbackEXT);
        result = vkCreateDebugReportCallbackEXT(instance, &deinf, nullptr, &debug_ext);
        CHECK(result);
    }
    /*==================================================================
     *                                          CREATES PHYSICAL DEVICE
     *=================================================================
     */
	result = vkEnumeratePhysicalDevices(instance,&count, nullptr);

    CHECK(result);

    std::vector<VkPhysicalDevice> pdiv(count);

    result = vkEnumeratePhysicalDevices(instance, &count, pdiv.data());

    CHECK(result);
    if (pdiv.size() == 1)
    {
        pDevice = pdiv[0];

        VkPhysicalDeviceProperties dProp;

        memset(&dProp, 0, sizeof dProp);

        vkGetPhysicalDeviceProperties(pdiv[0], &dProp);

        if (EnabledDebug) std::printf("%s%s%s%s%i\n","Your Gpu Is", "(GPU NAME):",dProp.deviceName," (DRIVER VERSION):", dProp.driverVersion);
    }
    else
    {
        std::vector<VkPhysicalDevice> pdiv_x(count);

        for (uint32 i = 0; i < count; i++)
        {
            VkPhysicalDeviceProperties dProp;

            memset(&dProp, 0, sizeof dProp);

            vkGetPhysicalDeviceProperties(pdiv[i], &dProp);

            if (dProp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                pdiv_x.push_back(pdiv[i]);

                if (EnabledDebug)  std::printf("%s%s%s%s%i\n", "adding gpu to accepted list:", " (GPU NAME):", dProp.deviceName, " (DRIVER VERSION):", dProp.driverVersion);
            }
            else
            {
                if (EnabledDebug) std::printf("%s%s%s%s%i\n", "rejected gpu from list:", " (GPU NAME):", dProp.deviceName, " (DRIVER VERSION):", dProp.driverVersion);
            }
        }
        if (pdiv_x.size() == 1)
        {
            pDevice = pdiv_x[0];
        }
        else
        {
            if (EnabledDebug) std::printf("%s\n", "More that one non Intergrated Gpu Randomly choicing one");
            int8 nam = rand() % pdiv.size() + 1;
            pDevice = pdiv_x[nam];
        }
    }
    /*==================================================================
     *                                          CREATES DEVICE
     *=================================================================
     */
    vkGetPhysicalDeviceQueueFamilyProperties(pDevice, &count, nullptr);
    std::vector<VkQueueFamilyProperties> fampro (count);
    vkGetPhysicalDeviceQueueFamilyProperties(pDevice, &count, fampro.data());

    bool found = false;
    int8 indexnum;
    for (uint32 i = 0; i < count; i++)
    {
        if (fampro[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            found = true;
            indexnum = i;
        }
    }

    CHECKB(found);

    float queueprioritys[] {  1.0f  };

    VkDeviceQueueCreateInfo queinf = {};

    queinf.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

    queinf.queueFamilyIndex = indexnum;

    queinf.queueCount = 1;

    queinf.pQueuePriorities = queueprioritys;

    const char* dLayers[] = { "VK_KHR_swapchain" };

    VkDeviceCreateInfo devinf = {};

    devinf.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    devinf.pNext = NULL;

    devinf.queueCreateInfoCount = 1;

    devinf.pQueueCreateInfos = &queinf;

    devinf.enabledExtensionCount = 1;

    devinf.ppEnabledExtensionNames = dLayers;

    devinf.enabledLayerCount = 1;

    devinf.ppEnabledLayerNames = lay;

    VkPhysicalDeviceFeatures features = {};
    features.shaderClipDistance = VK_TRUE;

    devinf.pEnabledFeatures = &features;

  result = vkCreateDevice(pDevice, &devinf, NULL, &device);

  CHECK(result);
  /*==================================================================
   *                                          CREATES SURFACE
   *==================================================================
   */
#ifdef WIN32
  HINSTANCE hInst = GetModuleHandle(NULL);

  VkWin32SurfaceCreateInfoKHR surf_ = {};
  surf_.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surf_.hinstance = hInst;
  surf_.hwnd = win->getWindow();

  result = vkCreateWin32SurfaceKHR(instance, &surf_, nullptr, &surface);

  CHECK(result);
#endif
#ifdef __linux__
  VkXLibSurfaceCreateInfoKHR surf_ = {};
  surf_.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;

  result = vkCreateXLibSurfaceKHR(instance, &surf_, nullptr, &surface);

  CHECK(result);
#endif

  VkSurfaceCapabilitiesKHR surfaceCapabilities = {};

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice, surface, &surfaceCapabilities);

  int16 width_, height_;

  VkExtent2D scrres;

  scrres.height = win->getWindowH();

  scrres.width = win->getWindowW();

  /*==================================================================
   *                                          CREATES SWAPCHAIN
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

  CHECK(result);

 result =  vkGetSwapchainImagesKHR(device, swapChain, &count, nullptr);
 
 CHECK(result);

  image = new VkImage[0];

  result = vkGetSwapchainImagesKHR(device, swapChain, &count, image);

  CHECK(result);

  image_v = new VkImageView[2];

  for (uint8 i = 0; i < 2; i++)
  {
      VkImageViewCreateInfo imvwinf = {};
      imvwinf.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
      imvwinf.viewType = VK_IMAGE_VIEW_TYPE_2D;
      imvwinf.format = VK_FORMAT_B8G8R8A8_UNORM;
      imvwinf.components.r = VK_COMPONENT_SWIZZLE_R;
      imvwinf.components.g = VK_COMPONENT_SWIZZLE_G;
      imvwinf.components.b = VK_COMPONENT_SWIZZLE_B;
      imvwinf.components.a = VK_COMPONENT_SWIZZLE_A;
      imvwinf.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      imvwinf.subresourceRange.baseMipLevel = 0;
      imvwinf.subresourceRange.levelCount = 1;
      imvwinf.subresourceRange.baseArrayLayer = 0;
      imvwinf.subresourceRange.layerCount = 1;
      imvwinf.image = image[i];

      result = vkCreateImageView(device,&imvwinf , nullptr, &image_v[i]);
      CHECK(result);
  }

}

void VKRenderer::destroyRender()
{
    vkDestroyDevice(device, nullptr);
    if (EnabledDebug)
    {
        PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
        CHECKP(vkDestroyDebugReportCallbackEXT);
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
