#pragma once
// Created by luket on 05/12/2020.
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
/*===========================================================================================================
 *                                      LUNA LUX ENGINE WINDOW LIBRARY
 *                                              VERSION 1.0
 *===========================================================================================================
 */
#include <string>
#include <tuple>
#include <cstdint>
namespace LunaLux
{
    //you pass createWindow a title, width and height
    //this is used to create a native window
    LLWL_EXPORT void createWindow(const std::string&, int, int) noexcept;

    //this will retrieve a pointer to the handle of the native window
    LLWL_EXPORT void* getNativeWindow() noexcept;

    //TODO: write documentation

    LLWL_EXPORT void changeWindowTitle(const std::string& title);

    //this is used to limit the amount of frames looped pre second
    [[maybe_unused]] LLWL_EXPORT void limitFrameRate(double fps) noexcept;

    //this will check if the window user has asked to close window true for no, false for yes.
    LLWL_EXPORT bool shouldCloseWindow() noexcept;

    //this will check if the window has changed size from last check if it has it will return true
    LLWL_EXPORT bool HasWindowResized() noexcept;

    LLWL_EXPORT void updateWindow() noexcept;

    //this will get the current size of the native window
    LLWL_EXPORT std::tuple<int,int> GetWindowSize() noexcept;

    LLWL_EXPORT void closeWindow() noexcept;

    LLWL_EXPORT bool isKeyDown(uint8_t);

    LLWL_EXPORT bool isMouseDown(uint8_t);

    LLWL_EXPORT uint64_t getWheelDelta();
    //this will get the current position of the native windows mouse relative to size of window
    LLWL_EXPORT std::tuple<int64_t,int64_t> getMousePosition();
}