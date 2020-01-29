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
			return DefWindowProcA(hWnd, Msg, wParam, lParam);
		}
		return 0;
	}

	void CrossWindow::createWindow()
	{
		WIN_SHOULD_CLOSE = false;
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

	void CrossWindow::destoryWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClassW((LPCWSTR)Title, Inst);
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