if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_subdirectory(DirectX12Lib)
endif ()
add_subdirectory(NetLib)
add_subdirectory(VulkanLib)
add_subdirectory(VulkanUtilLib)
add_subdirectory(WindowLib)