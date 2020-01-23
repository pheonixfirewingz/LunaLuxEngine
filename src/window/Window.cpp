#include "Window.h"
#include "Window.h"
#include "../LunaLuxEngine.h"

GLFWwindow* win__;

namespace LunaLuxEngine::window_api
{
#ifndef WIN32
	void Window::updateWindow()
	{
		glfwSwapBuffers(win__);
		glfwPollEvents();
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0,0,width,height);
	}

	void Window::createWindow()
	{
		if (!glfwInit())
			throw std::invalid_argument( "Failed to initialize to GLFW" );

		win__ = glfwCreateWindow(width, height, Title, NULL, NULL);
		glfwSetFramebufferSizeCallback(win__, framebuffer_size_callback);

		if (!win__)
		{
			glfwTerminate();
			throw std::invalid_argument( "Failed to create to Window" );
		}
		glfwMakeContextCurrent(win__);
	}

	void Window::destoryWindow()
	{
		glfwTerminate();
	}

	bool Window::getShouldClose()
	{
		return glfwWindowShouldClose(win__);
	}
#else
	void Window::updateWindow()
	{
	
	}

	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_CLOSE:
				PostQuitMessage(0);
			break;
		default:
			return DefWindowProcA(hWnd, Msg, wParam, lParam);
		}
		return 0;
	}

	void Window::createWindow()
	{
		Inst = GetModuleHandle(nullptr);

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = Inst;
		wc.hIcon = static_cast<HICON>(LoadImage(Inst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = Title;
		wc.hIconSm = static_cast<HICON>(LoadImage(Inst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
		RegisterClassEx(&wc);

		RECT wr;
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;

		hwnd = CreateWindow(
			Title, Title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, Inst, this
		);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	void Window::destoryWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClassW((LPCWSTR)Title, Inst);
	}

	HWND Window::getWindow()
	{
		return hwnd;
	};
#endif
	void Window::setTitle(char* title)
	{
		Title = title;
	}
	bool Window::shouldClose() 
	{
		return  WIN_SHOULD_CLOSE; 
	}

}