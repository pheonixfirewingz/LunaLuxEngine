//
// Created by digitech on 24/10/2019.
//

#include "X11Interface.h"

#ifdef __linux__

void X11Interface::createDisplay()
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
  swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

  win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

  XMapWindow(dpy, win);

  XStoreName(dpy, win, title);

  glc = glXCreateContext(dpy, vi, nullptr, GL_TRUE);
  glXMakeCurrent(dpy, win, glc);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,width,height);
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void X11Interface::destroyWindow()
{
  glXMakeCurrent(dpy, None, nullptr);
  XFree(vi);
  glXDestroyContext(dpy, glc);
  XDestroyWindow(dpy, win);
  XSync(dpy, false);
  XCloseDisplay(dpy);
}


void X11Interface::updateDisplay()
{
  XNextEvent(dpy, &xev);

  if(xev.type == Expose)
  {
    XGetWindowAttributes(dpy, win, &gwa);
    glXSwapBuffers(dpy, win);
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  else if(xev.type == ConfigureNotify)
  {
    glViewport(0, 0, xev.xconfigure.width, xev.xconfigure.height);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}
#endif