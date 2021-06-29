cmake_minimum_required(VERSION 3.18)
include_directories(STATIC src)

add_library(LunaLuxNetLib SHARED src/NetLib.cpp src/StringUtil.cpp)

add_executable(LunaLuxNetLibClientTest ClientTest.cpp)

target_link_libraries(LunaLuxNetLibClientTest LunaLuxNetLib)

add_executable(LunaLuxNetLibServerTest ServerTest.cpp)

target_link_libraries(LunaLuxNetLibServerTest LunaLuxNetLib)