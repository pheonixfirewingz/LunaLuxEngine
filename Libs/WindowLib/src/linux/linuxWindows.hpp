#pragma once
//
// Created by digitech on 15/03/2021.
//
// TODO: add documentation.
#include "../IO.hpp"
#include <X11/Xutil.h>
#include <cstring>
#include <time.h>
#include <tuple>
#include <xcb/xcb.h>

namespace LunaLux
{
struct xcbContext
{
    xcb_connection_t *con;
    xcb_window_t win;
};
class LinuxWindow
{
  private:
    xcbContext* context;
    xcb_screen_t *screen;
    xcb_intern_atom_reply_t *atom_wm_delete_window;
    bool shouldClose{false};

  public:
    const std::unique_ptr<IO> io = std::make_unique<IO>();

    explicit LinuxWindow(const char *title, const int width, const int height)
    {
        printf("LunaLuxWindowLib: keyboard and mouse are not available / implemented on linux the library will crash\n");
        context = new xcbContext();
        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        context->con = xcb_connect(NULL, NULL);
        screen = xcb_setup_roots_iterator(xcb_get_setup(context->con)).data;
        uint32_t values[2];
        values[0] = screen->white_pixel;
        values[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION;
        context->win = xcb_generate_id(context->con);
        
        /* Create the window */
        xcb_create_window(context->con, XCB_COPY_FROM_PARENT, context->win, screen->root, 0, 0, width, height,0,
                          XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, values);

        /* Magic code that will send notification when window is destroyed */
        xcb_intern_atom_cookie_t cookie = xcb_intern_atom(context->con, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(context->con, cookie, 0);

        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(context->con, 0, 16, "WM_DELETE_WINDOW");
        atom_wm_delete_window = xcb_intern_atom_reply(context->con, cookie2, 0);

        xcb_change_property(context->con, XCB_PROP_MODE_REPLACE, context->win,
                            (*reply).atom, 4, 32, 1,&(*atom_wm_delete_window).atom);
        free(reply);

        xcb_change_property(context->con,XCB_PROP_MODE_REPLACE,context->win,XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING,8,std::strlen(title),title);
        /* Map the window on the screen */
        xcb_map_window(context->con, context->win);

        const uint32_t coords[] = {100, 100};
        xcb_configure_window(context->con, context->win, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);
        /* Make sure commands are sent before we pause, so window is shown */
        xcb_flush(context->con);
    }

    void *GetNativeWindow()
    {
        return context;
    }

    void ChangeWindowTitle(const char *title)
    {
        xcb_change_property(context->con,XCB_PROP_MODE_REPLACE,context->win,XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING,8,std::strlen(title),title);
        xcb_flush(context->con);
    }

    [[nodiscard]] bool ShouldClose() const
    {
        return shouldClose;
    }

    std::tuple<int, int> GetWindowSize()
    {
        xcb_get_geometry_reply_t *geom = xcb_get_geometry_reply (context->con, xcb_get_geometry (context->con, context->win), NULL);
        return {geom->width, geom->height};
    }

    void Update()
    {
        xcb_generic_event_t *event = xcb_poll_for_event(context->con);
        if(event == nullptr)
        {
            return;
        }
        switch (event->response_type & ~0x80)
        {
        case XCB_EXPOSE:
        {
            xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
            break;
        }
        case XCB_CLIENT_MESSAGE:
            if ((*(xcb_client_message_event_t *)event).data.data32[0] == (*atom_wm_delete_window).atom)
            {
                shouldClose = true;
            }
            break;
        default:break;
        }
        free(event);
    }

    void Close()
    {
        xcb_destroy_window(context->con, context->win);
        xcb_disconnect(context->con);
        free(atom_wm_delete_window);
    }

    bool isKeyDown(uint8_t key)
    {
        return io->isButtonDown(key);
    }

    bool isMouseDown(uint8_t button)
    {
        return io->isButtonDown(button + 255);
    }

    uint64_t getWheelDelta()
    {
        return io->getWheelDelta();
    }

    std::tuple<int64_t, int64_t> getMousePosition()
    {
        return io->getPosition();
    }

    uint64_t getTime()
    {
        const long long ns_in_us = 1000;
        const long long ns_in_ms = 1000 * ns_in_us;
        const long long ns_in_s = 1000 * ns_in_ms;
        timespec currTime;
        clock_gettime(CLOCK_MONOTONIC, &currTime);
        return (uint64_t)currTime.tv_sec * ns_in_s + (uint64_t)currTime.tv_nsec;
    }
};

} // namespace LunaLux