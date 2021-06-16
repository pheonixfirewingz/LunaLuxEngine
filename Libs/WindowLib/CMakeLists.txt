cmake_minimum_required(VERSION 3.18)
include_directories(STATIC src)

add_library(LunaLuxWindowLib SHARED src/WindowLib.cpp
                                    src/Windows/WindowsWindow.cpp)

