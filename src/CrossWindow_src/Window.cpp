#include "Window.h"
#include "Thread.h"

void LunaLuxEngine::window_api::CrossWindow::initWindow(WindowInfo& windowInfo)
{
    {
        if(windowInfo.debug)
        {
            Thread *thread = new Thread();
            thread->outputThreadInfo();
        }
    }
    if (windowInfo.windowType == WindowType::Win32Window) window = new Win32Window();
    else if (windowInfo.windowType == WindowType::X11Window) window = new X11Window();
    else WindowPanic::get()->panic("could not set window type");

    window->info = windowInfo;
    window->setSize(window->info.width,window->info.height);
    window->setTitle(window->info.title);
    OpenGLMode = window->info.HaveWindowCreateOpenGLContext;
    if(window->info.HaveWindowCreateOpenGLContext)
    {
        LOG("CrossWindow creates the context but you will need glad or glew to get the opengl functions")
    }
    this->createWindow();
}

float LunaLuxEngine::window_api::CrossWindow::getAspectRatio()
{
    return window->getWindowW() / window->getWindowH();
}
