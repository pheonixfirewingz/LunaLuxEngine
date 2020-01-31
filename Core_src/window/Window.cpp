#include <chrono>
#include "Window.h"
#include "Window.h"
#include "../LunaLuxEngineCore.h"

#ifdef MAC
GLFWwindow* win__;
#endif

namespace LunaLuxEngine::window_api
{
	bool sc_temp;
#ifdef MAC
	void CrossWindow::updateWindow()
	{
		glfwSwapBuffers(win__);
		glfwPollEvents();
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0,0,width,height);
	}

	void CrossWindow::createWindow()
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

	void CrossWindow::destoryWindow()
	{
		glfwTerminate();
	}
#endif
#ifdef __linux__
    void CrossWindow::updateWindow()
    {
        XNextEvent(dpy, &xev);

        switch(xev.type)
        {
            case Expose:
                XGetWindowAttributes(dpy, win, &gwa);
                glXSwapBuffers(dpy, win);
                break;
            case ConfigureNotify:
                glViewport(0, 0, xev.xconfigure.width, xev.xconfigure.height);
                break;
                //TODO fix this error not fatal to running but will not shutdown engine correctly

                /* XIO:  fatal IO error 11 (Resource temporarily unavailable) on X server ":0"
                 * after 45 requests (45 known processed) with 0 events remaining.
                 */
            case DestroyNotify:
                WIN_SHOULD_CLOSE = true;
                break;
        }
    }

    void CrossWindow::createWindow()
    {
        dpy = XOpenDisplay(nullptr);

        if(dpy == nullptr)
        {
            std::printf("\n\tcannot connect to X server\n\n");
            std::exit(0);
        }

        root = DefaultRootWindow(dpy);

        GLint  att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        vi = glXChooseVisual(dpy, 0, att);

        if(vi == nullptr)
        {
            std::printf("\n\tno appropriate visual found\n\n");
            std::exit(0);
        }

        cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

        win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

        XMapWindow(dpy, win);

        XStoreName(dpy, win, Title);

        glc = glXCreateContext(dpy, vi, nullptr, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
        glEnable(GL_DEPTH_TEST);
        glViewport(0,0,width,height);
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void CrossWindow::destoryWindow()
    {
        glXMakeCurrent(dpy, None, nullptr);
        XFree(vi);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XSync(dpy, false);
        XCloseDisplay(dpy);
    }
#endif
#ifdef WIN32
	void CrossWindow::updateWindow()
	{
		if (sc_temp) WIN_SHOULD_CLOSE = true;
	}

	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_CLOSE:
		{
			sc_temp = true;
		}
			break;
		default:
            		return DefWindowProc(hwnd, msg, wparam, lparam);
            		break;
		}
		return 0;
	}

	void CrossWindow::createWindow()
	{
		WIN_SHOULD_CLOSE = false;
		const char* class_name = "LunaLuxEngine_WindowClass";

		Inst = GetModuleHandle(nullptr);

		WNDCLASSEX win_class = {};
		win_class.cbSize = sizeof(WNDCLASSEX);
		win_class.style = CS_HREDRAW | CS_VREDRAW;
		win_class.lpfnWndProc =  WndProc;
		win_Class.cbClsExtra = 0;
		win_class.cbWndExtra = 0;
		win_class.hInstance = Inst;
		win_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		win_class.lpszClassName = class_name;
		RegisterClassEx(&win_class);

		const DWORD win_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_OVERLAPPEDWINDOW;

		RECT win_rect = {0, 0, 1280, 720};
		AdjustWindowRect(&win_rect, win_style, false);

		hwnd = CreateWindowEx(WS_EX_APPWINDOW, class_name, Title, win_style, 0, 0,
				win_rect.right - win_rect.left, win_rect.bottom - win_rect.top, nullptr, nullptr, Inst, nullptr);

		SetForegroundWindow(hwnd);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) this);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	void CrossWindow::destoryWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClassW((LPCWSTR)"LunaLuxEngine_WindowClass", Inst);
	}

	HWND CrossWindow::getWindow()
	{
		return hwnd;
	};
#endif
	void CrossWindow::setTitle(char* title)
	{
		Title = title;
	}
	bool CrossWindow::shouldClose()
	{
		return  WIN_SHOULD_CLOSE; 
	}

	CrossWindow* CrossWindow::get()
	{
		return window;
	}

	void CrossWindow::setShouldClose(bool in)
	{
		this->WIN_SHOULD_CLOSE = in;
	}

}