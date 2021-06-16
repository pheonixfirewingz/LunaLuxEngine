#pragma once
// Created by luket on 05/12/2020.
/*===========================================================================================================
 *                                      LUNA LUX ENGINE WINDOW LIBRARY
 *                                              VERSION 1.0
 *===========================================================================================================
 */
/*------------------------------------------------------------------------------------------------------------
 * the Window header is used to define the window interface where the Common window functions are defined for
 * use of the user.
 *
 * FUNCTIONS:
 * *********
 * OPEN:
 *
 * Args:
 * char*(character pointer) this is a pointer to the title that is (or to be) displayed in the window action ribbon.
 * int(integer) this argument is where the user passed in the width that is used to create the window originally.
 * int(integer) this argument is where the user passed in the height that is used to create the window originally.
 *
 * Returns: none.
 *
 * Job:
 * this function is used to define the function open in other class's in the abstraction layer.
 *
 * Description:
 * the open function is used to create the window on start of the software.
 * ====================================================================================================================
 * GETNATIVEWINDOW:
 *
 * Args: none.
 *
 * Returns:
 * void * (" " pointer) this is used to return the native window handler.
 *
 * Job: the job of this function is to get the window handler created by the lib.
 *
 * Description:
 * this function is used to get the native window handler this is needed to create a directx, opengl, vulkan context.
 *====================================================================================================================
 * CHANGEWINDOWTITLE:
 *
 * Args:
 * char* (Char Pointer) this is used to pass the new title.
 *
 * Returns: none.
 *
 * Job: this is used to change the current display title of the window.
 *
 * Description:
 * this is used to change the current display title of the window so the lib user can change the title after the window
 * has being opened.
 * ====================================================================================================================
 * LIMITFRAMERATE:
 *
 * Args:
 * double(Double) this double is used to state max frame rate is defined.
 *
 * Returns: none.
 *
 * Job: this is so the user can can limit the number of frame cycles per second.
 *
 * Description: this is so the user can can limit the number of frame cycles per second it will not allow the user to set the frame
 * limit less than 5.0fps if the user try's to do so it will through an exception.
 * ====================================================================================================================
 * SHOULD CLOSE:
 *
 * Args: none.
 *
 * Returns:
 * bool(Boolean) this function is returns if th window should close if returns false then the user should stay in the
 * while loop else the user should break out of the while loop.
 *
 * Job: this function is used to define the function ShouldClose in other class's in the abstraction layer.
 *
 * Description: the ShouldClose function is used to ask the window if it should close the software and window down.
 * ====================================================================================================================
 * GETWINDOWSIZE:
 *
 * Args: none.
 *
 * Returns:
 * tuple(temple class) this is used to return the width and height in on go instead of having multiple functions.
 *
 * Job: this function is used to define the function GetWindowSize in other class's in the abstraction layer.
 *
 * Description: the GetWindowSize function is used to get the window size stored in the children classes.
 * ====================================================================================================================
 * UPDATE:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job: this function is used to define the function Update in other class's in the abstraction layer.
 *
 * Description: the Update function is used to update the window and that the platform knows the software is still active.
 * ====================================================================================================================
 * CLOSE:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job: this function is used to define the function Close in other class's in the abstraction layer.
 *
 * Description:
 * the Close function is used to close the window and tell the platform that the software is in the process of shutdown.
 * //TODO: finish documentation.
 * ====================================================================================================================
 * GETMOUSEPOSITION:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job:  .
 *
 * Description: .
 * ====================================================================================================================
 * ISKEYDOWN:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job:  .
 *
 * Description: .
 * ====================================================================================================================
 * ISMOUSEDOWN:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job: .
 *
 * Description: .
 * ====================================================================================================================
 * GETWHEELDELTA:
 *
 * Args: none.
 *
 * Returns: none.
 *
 * Job: .
 *
 * Description: .
 * ====================================================================================================================
 */
#include <string>
#include <tuple>
namespace LunaLuxWindowLib
{
    class Window
    {
    public:
        void Open(std::string, int, int);

        void* GetNativeWindow();

        void changeWindowTitle(std::string title);

        [[maybe_unused]] void LimitFrameRate(double fps);

        bool ShouldClose();

        void Update(double fps);

        std::tuple<int,int> GetWindowSize();

        void Close();

        bool isKeyDown(int);

        bool isMouseDown(int);

        float getWheelDelta();

        std::tuple<int,int> getMousePosition();

        ~Window();
    };
}