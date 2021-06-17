cmake_minimum_required(VERSION 3.18)
include_directories(STATIC src)

add_library(LunaLuxWindowLib SHARED src/WindowLib.cpp
                                    src/Windows/WindowsWindow.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxWindowLib ${X11_xcb_LIB} ${X11_LIBRARIES})
endif ()