cmake_minimum_required(VERSION 3.18)
include_directories(STATIC src)

add_library(LunaLuxNetLib SHARED src/NetLib.cpp src/linux/LinuxNetManager.hpp)