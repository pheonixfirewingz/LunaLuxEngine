//
// Created by luket on 16/01/2020.
//
#include "Vulkan.h"


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
    memset(&result, 0, 0);
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
    const char* ext[] = { "VK_KHR_surface",VK_KHR_PLATFOM_SUFRACE, VK_EXT_DEBUG_REPORT_EXTENSION_NAME };

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

    CHECK_N(result,"VULKAN ERROR")

    if (EnabledDebug)
    {
        VkDebugReportCallbackCreateInfoEXT reportCallbackCreateInfoExt = {};
		reportCallbackCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		reportCallbackCreateInfoExt.pNext = nullptr;
		reportCallbackCreateInfoExt.pfnCallback = vkLLEDebugCallback;
		reportCallbackCreateInfoExt.flags = 1 | 2 | 4 | 8 | 10;
		reportCallbackCreateInfoExt.pUserData = nullptr;
        auto vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
        CHECK_P(vkCreateDebugReportCallbackEXT, "VULKAN ERROR")
        result = vkCreateDebugReportCallbackEXT(instance, &reportCallbackCreateInfoExt, nullptr, &debug_ext);
        CHECK_N(result,"VULKAN ERROR")
    }
    /*==================================================================
     *					CREATES PHYSICAL DEVICE
     *=================================================================
     */
	result = vkEnumeratePhysicalDevices(instance,&count, nullptr);

    CHECK_N(result,"")

    std::vector<VkPhysicalDevice> physical_device(count);

    result = vkEnumeratePhysicalDevices(instance, &count, physical_device.data());

    CHECK_N(result,"VULKAN ERROR")
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
     *		                    CREATES DEVICE
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

    CHECK_B(found,"VULKAN ERROR")

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

  CHECK_N(result,"VULKAN ERROR")
  /*==================================================================
   *				        CREATES SURFACE
   *==================================================================
   */
#ifdef WIN32
  HINSTANCE hInst = GetModuleHandle(nullptr);

  VkWin32SurfaceCreateInfoKHR surf_ = {};
  surf_.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surf_.hinstance = hInst;
  surf_.hwnd = win->getWindow();

  result = vkCreateWin32SurfaceKHR(instance, &surf_, nullptr, &surface);
#endif
#ifdef __linux__
  VkXlibSurfaceCreateInfoKHR surf_ = {};
  surf_.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surf_.dpy = win->getWindowL();
  surf_.window = win->getWindowL_();

  result = vkCreateXlibSurfaceKHR(instance,&surf_,nullptr,&surface);
#endif
  CHECK_N(result,"VULKAN ERROR")

  VkSurfaceCapabilitiesKHR surfaceCapabilities = {};

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice, surface, &surfaceCapabilities);

  int16 width_, height_;

  VkExtent2D scrres;

  scrres.height = win->getWindowH();

  scrres.width = win->getWindowW();

  /*==================================================================
   *                    CREATES SWAP_CHAIN
   *==================================================================
   */

  VkSwapchainCreateInfoKHR swap_chainCreateInfoKhr = {};
    swap_chainCreateInfoKhr.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swap_chainCreateInfoKhr.surface = surface;
    swap_chainCreateInfoKhr.minImageCount = 2;
    swap_chainCreateInfoKhr.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
    swap_chainCreateInfoKhr.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    swap_chainCreateInfoKhr.imageExtent = scrres;
    swap_chainCreateInfoKhr.imageArrayLayers = 1;
    swap_chainCreateInfoKhr.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swap_chainCreateInfoKhr.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swap_chainCreateInfoKhr.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swap_chainCreateInfoKhr.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swap_chainCreateInfoKhr.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    swap_chainCreateInfoKhr.clipped = true;
    swap_chainCreateInfoKhr.oldSwapchain = nullptr;

  result = vkCreateSwapchainKHR(device, &swap_chainCreateInfoKhr, nullptr, &swapChain);

  CHECK_N(result,"VULKAN ERROR")

 result =  vkGetSwapchainImagesKHR(device, swapChain, &count, nullptr);
 
 CHECK_N(result,"VULKAN ERROR")

  image = new VkImage[0];

  result = vkGetSwapchainImagesKHR(device, swapChain, &count, image);

  CHECK_N(result,"VULKAN ERROR")

  image_v = new VkImageView[2];

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
	  viewCreateInfo.image = image[0];

<<<<<<< HEAD
      result = vkCreateImageView(device,&viewCreateInfo , nullptr, &image_v[i]);
      CHECK_N(result,"VULKAN ERROR")
  }
=======
      result = vkCreateImageView(device,&viewCreateInfo , nullptr, &image_v[0]);
      CHECK(result)

      viewCreateInfo.image = image[1];

      result = vkCreateImageView(device, &viewCreateInfo, nullptr, &image_v[1]);
      CHECK(result)

>>>>>>> master
  //need to understand file path
  vertShaderModule = createShaderModule(FileSystem::FileReader::get()->readFile("vert.spv"));
  fragShaderModule = createShaderModule(LunaLuxEngine::FileSystem::FileReader::get()->readFile("frag.spv"));

  VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

  VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInputInfo.vertexBindingDescriptionCount = 0;
  vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
  vertexInputInfo.vertexAttributeDescriptionCount = 0;
  vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

  VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = CWin->getWindowW();
  viewport.height = CWin->getWindowH();
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkExtent2D extent = {};
  extent.width = CWin->getWindowW();
  extent.height = CWin->getWindowH();

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = extent;

  VkPipelineViewportStateCreateInfo viewportState = {};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.blendEnable = VK_TRUE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

  VkPipelineColorBlendStateCreateInfo colorBlending = {};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

  VkDynamicState dynamicStates[] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_LINE_WIDTH
  };

  VkPipelineDynamicStateCreateInfo dynamicState = {};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = 2;
  dynamicState.pDynamicStates = dynamicStates;

  VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0; // Optional
  pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);

  CHECK_N(result,"VULKAN ERROR")

 VkAttachmentDescription colorAttachment = {};
  colorAttachment.format = VK_FORMAT_B8G8R8A8_UNORM;
  colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference colorAttachmentRef = {};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;

  VkRenderPassCreateInfo renderPassInfo = {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = 1;
  renderPassInfo.pAttachments = &colorAttachment;
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;

  result = vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass);

  CHECK_N(result,"VULKAN ERROR")

 VkGraphicsPipelineCreateInfo pipelineInfo = {};
 pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
 pipelineInfo.stageCount = 2;
 pipelineInfo.pStages = shaderStages;
 pipelineInfo.pVertexInputState = &vertexInputInfo;
 pipelineInfo.pInputAssemblyState = &inputAssembly;
 pipelineInfo.pViewportState = &viewportState;
 pipelineInfo.pRasterizationState = &rasterizer;
 pipelineInfo.pMultisampleState = &multisampling;
 pipelineInfo.pDepthStencilState = nullptr; // Optional
 pipelineInfo.pColorBlendState = &colorBlending;
 pipelineInfo.pDynamicState = nullptr; // Optional
 pipelineInfo.layout = pipelineLayout;
 pipelineInfo.renderPass = renderPass;
 pipelineInfo.subpass = 0;
 pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
 pipelineInfo.basePipelineIndex = -1; // Optional

 result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline);

 CHECK_N(result,"VULKAN ERROR")
}

void VKRenderer::destroyRender()
{
    vkDeviceWaitIdle(device);
    vkDestroyRenderPass(device, renderPass, nullptr);
    vkDestroyPipeline(device, pipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);
    for (int32 x = 0; x < 2; x++) 
    {
        vkDestroyImageView(device, image_v[x], nullptr);
    }
    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    if (EnabledDebug)
    {
        auto vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
        CHECK_P(vkDestroyDebugReportCallbackEXT,"VULKAN ERROR")
        vkDestroyDebugReportCallbackEXT(instance, debug_ext, nullptr);
    }
    vkDestroyInstance(instance, nullptr);
}

void VKRenderer::prepRender()
{
    VkResult res;
    memset(&res, 0, 0);
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    res = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore);

    CHECK_N(res,"VULKAN ERROR")

    res = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore);

    CHECK_N(res,"VULKAN ERROR")
}

void VKRenderer::fireRender()
{
<<<<<<< HEAD
    VkResult res = VK_SUCCESS;
=======
    VkResult res;
    memset(&res, 0, 0);
>>>>>>> master
    uint32 imageIndex;
    vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);


    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    //res = vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

    CHECK_N(res,"VULKAN ERROR")

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;

    VkSwapchainKHR swapChains[] = { swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    //res = vkQueuePresentKHR(presentQueue, &presentInfo);

    CHECK_N(res,"VULKAN ERROR")
}

void VKRenderer::postRender()
{
    vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
}