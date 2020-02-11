#pragma once
#include <LLESDK/types.h>
#define WIN32_LEAN_AND_MEAN
#define STRICT

#include <windows.h>
#include <windowsx.h>
#define CWin LunaLuxEngine::window_api::CrossWindow::get()

namespace LunaLuxEngine::window_api
{
class CrossWindow
{
    private:
        HWND hwnd{};
        HINSTANCE Inst{};
        public:
        inline HWND getWindow()
        {
            return hwnd;
        };
        LPCSTR class_name = (LPCSTR)"LunaLuxEngine_WindowClass";
protected:
        int8* Title = (int8*)"temp";
        int16 width = 800,  height = 600;
        void(*resizeCallback)(int32,int32) = nullptr;
public:
        LLEbool WIN_SHOULD_CLOSE = LLEfalse;
        void createWindow();
        inline void setTitle(int8* in_title)
        {
            Title = in_title;
        };
        inline void setSize(int16 in_width,int in_height)
        {
            width = in_width;
            height = in_height;
            //fireResizeCallback(in_width, in_height);
        };
        inline int8* getTitle()
        {
            return Title;
        };
        inline LLEbool shouldClose()
        {
            return  WIN_SHOULD_CLOSE;
        };
        void updateWindow();
        void destoryWindow();

		inline float getWindowW()
        {
            return width;
        };
		inline float getWindowH()
		{
			return height;
		};
        inline void setResizeCallback(void(*callback)(int32, int32))
        {
            resizeCallback = callback;
        }
        void fireResizeCallback(int32, int32);

		inline static CrossWindow* get()
		{
			static auto* window_ = new CrossWindow();
			return window_;
		}
	};
}