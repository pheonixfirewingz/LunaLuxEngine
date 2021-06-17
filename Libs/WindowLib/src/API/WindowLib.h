#pragma once
// Created by luket on 05/12/2020.

#if __has_include(<windows.h>)
#ifndef LIB_APP
#ifndef STATIC_LIB
#define LLWL_EXPORT __declspec(dllexport)
#else
#define LLWL_EXPORT
#endif
#else
#ifndef STATIC_LIB
#define LLWL_EXPORT __declspec(dllimport)
#else
#define LLWL_EXPORT
#endif
#endif
#else
#ifndef LIB_APP
#ifndef STATIC_LIB
#define LLWL_EXPORT __attribute__((visibility("default")))
#else
#define LLWL_EXPORT
#endif
#else
#ifndef STATIC_LIB
#define LLWL_EXPORT
#endif
#endif
#endif
/*===========================================================================================================
 *                                      LUNA LUX ENGINE WINDOW LIBRARY
 *                                              VERSION 1.0
 *===========================================================================================================
 */
#include <cstdint>
#include <string>
#include <tuple>
namespace LunaLux
{
// you pass createWindow a title, width and height
// this is used to create a native window
LLWL_EXPORT void windowCreate(const std::string &, int, int) noexcept;

// this will retrieve a pointer to the handle of the native window
LLWL_EXPORT void *windowGetNative() noexcept;

// this is used to change the window title label
LLWL_EXPORT void windowChangeTitle(const std::string &title);

// this will check if the window user has asked to close window true for no, false for yes.
LLWL_EXPORT bool shouldCloseWindow() noexcept;

//this is use to update the window and io for the operating system
LLWL_EXPORT void windowUpdate() noexcept;

// this will get the current size of the native window
LLWL_EXPORT std::tuple<int, int> windowGetRectSize() noexcept;

LLWL_EXPORT void windowClose() noexcept;

//---------------------------------------------------------------------------------------------------------------------
//                              this is the library keyboard and mouse controls
//---------------------------------------------------------------------------------------------------------------------
LLWL_EXPORT bool isKeyDown(uint8_t);

LLWL_EXPORT bool isMouseDown(uint8_t);

LLWL_EXPORT uint64_t getWheelDelta();
// this will get the current position of the native windows mouse relative to size of window
LLWL_EXPORT std::tuple<int64_t, int64_t> getMousePosition();
//---------------------------------------------------------------------------------------------------------------------
//                              this is the library extras
//---------------------------------------------------------------------------------------------------------------------
// this will check if the window has changed size from last check if it has it will return true
LLWL_EXPORT bool hasWindowResized() noexcept;
// this will get system time in nano seconds
LLWL_EXPORT uint64_t getTime();
} // namespace LunaLux