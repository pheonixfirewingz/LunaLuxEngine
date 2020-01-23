//
// Created by digitech on 24/10/2019.
//
#ifndef LUNALUXENGINE_X11INTERFACE_H
#define LUNALUXENGINE_X11INTERFACE_H
#include "Window.h"
#if defined(__linux__)
#include<cstdio>
#include<cstdlib>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

class X11Interface: public Window
{
 private:
  Display                 *dpy{};
  Window                  root{};
  XVisualInfo             *vi{};
  Colormap                cmap{};
  XSetWindowAttributes    swa{};
  Window                  win{};
  GLXContext              glc{};
  XWindowAttributes       gwa{};
  XEvent                  xev{};
 public:
  void createDisplay();
  void updateDisplay();
  void destroyWindow();
};
#endif
#endif //LUNALUXENGINE_X11INTERFACE_H
