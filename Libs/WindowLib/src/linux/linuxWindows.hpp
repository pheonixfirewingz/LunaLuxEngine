#pragma once
//
// Created by digitech on 15/03/2021.
//
// TODO: add documentation.
#if __has_include(<xcb/xcb.h>)
#    include <atomic>
#    include <cstring>
#    include <ctime>
#    include <tuple>
#    include <xcb/xcb.h>

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
    xcbContext *cxt;
    xcb_screen_t *screen;
    xcb_intern_atom_reply_t *atom_wm_delete_window;
    std::atomic_bool shouldClose{false}, isInWindow{false}, isRest{false}, keys[256]{}, buttons[3]{};
    std::atomic_int64_t x = 0,y = 0;

    bool isWindowActive()
    {
        return isInWindow;
    }
  public:
    explicit LinuxWindow(const char *title, const int width, const int height)
    {
        printf("LunaLuxWindowLib: mouse wheel delta is not (available/implemented)\n");
        cxt = new xcbContext();
        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        cxt->con = xcb_connect(nullptr, nullptr);
        screen = xcb_setup_roots_iterator(xcb_get_setup(cxt->con)).data;
        uint32_t values[2];
        values[0] = screen->white_pixel;
        values[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                    XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                    XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW;

        cxt->win = xcb_generate_id(cxt->con);

        /* Create the window */
        xcb_create_window(cxt->con, XCB_COPY_FROM_PARENT, cxt->win, screen->root, 0, 0, width, height, 0,
                          XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, values);

        /* Magic code that will send notification when window is destroyed */
        xcb_intern_atom_cookie_t cookie = xcb_intern_atom(cxt->con, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(cxt->con, cookie, nullptr);

        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(cxt->con, 0, 16, "WM_DELETE_WINDOW");
        atom_wm_delete_window = xcb_intern_atom_reply(cxt->con, cookie2, nullptr);

        xcb_change_property(cxt->con, XCB_PROP_MODE_REPLACE, cxt->win, (*reply).atom, 4, 32, 1,
                            &(*atom_wm_delete_window).atom);
        free(reply);

        xcb_change_property(cxt->con, XCB_PROP_MODE_REPLACE, cxt->win, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                            std::strlen(title), title);

        /* Map the window on the screen */
        xcb_map_window(cxt->con, cxt->win);

        const uint32_t coords[] = {100, 100};
        xcb_configure_window(cxt->con, cxt->win, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);
        /* Make sure commands are sent before we pause, so window is shown */
        xcb_flush(cxt->con);
    }

    void *GetNativeWindow()
    {
        return cxt;
    }

    void ChangeWindowTitle(const char *title)
    {
        xcb_change_property(cxt->con, XCB_PROP_MODE_REPLACE, cxt->win, XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING, 8,std::strlen(title), title);
        xcb_flush(cxt->con);
    }

    [[nodiscard]] bool ShouldClose() const
    {
        return shouldClose;
    }

    std::tuple<int, int> GetWindowSize()
    {
        xcb_get_geometry_reply_t *geom = xcb_get_geometry_reply(cxt->con,xcb_get_geometry(cxt->con,cxt->win),nullptr);
        return {geom->width, geom->height};
    }

    void Update()
    {
        xcb_generic_event_t *event = xcb_poll_for_event(cxt->con);
        if (event == nullptr) return;

        if(!isWindowActive())
        {
            if(!isRest)
            {
                for(uint8_t i = 0; i < 255; i++) keys[i] = false;

                for(uint8_t i = 0; i < 2; i++) buttons[i] = false;
                isRest = true;
            }
        }

        switch (event->response_type & ~0x80)
        {
        case XCB_KEY_PRESS: {
            if(isWindowActive())
            {
                auto key = reinterpret_cast<xcb_key_press_event_t *>(event);
                keys[key->detail] = true;
            }
        }
        break;
        case XCB_KEY_RELEASE:    {
            if(isWindowActive())
            {
                auto key = reinterpret_cast<xcb_key_release_event_t *>(event);
                keys[key->detail] = false;
            }
        }
        break;
        case XCB_BUTTON_PRESS:   {
            if(isWindowActive())
            {
                auto button = reinterpret_cast<xcb_button_press_event_t *>(event);
                buttons[button->detail] = true;
            }
        } break;
        case XCB_BUTTON_RELEASE: {
            if(isWindowActive())
            {
                auto button = reinterpret_cast<xcb_button_release_event_t *>(event);
                buttons[button->detail] = false;
            }
        } break;
        case XCB_MOTION_NOTIFY:  {
            if(isWindowActive())
            {
                auto mouse_move = reinterpret_cast<xcb_motion_notify_event_t *>(event);
                x = mouse_move->event_x;
                y = mouse_move->event_y;
            }
        } break;
        case XCB_ENTER_NOTIFY: {
            isInWindow = true;
            isRest = false;
        } break;
        case XCB_LEAVE_NOTIFY: {
            isInWindow = false;
        } break;
        case XCB_CLIENT_MESSAGE:
            if ((*(xcb_client_message_event_t *)event).data.data32[0] == (*atom_wm_delete_window).atom)
            {
                shouldClose = true;
            }
            break;
        default:
            break;
        }
        free(event);
    }

    void Close()
    {
        xcb_destroy_window(cxt->con, cxt->win);
        xcb_disconnect(cxt->con);
        free(atom_wm_delete_window);
    }

    bool isKeyDown(uint8_t key)
    {
        if(key == 255)
        {
            printf("LunaLuxEngine - Linux: this key is not mapped\n");
            return false;
        }
        return keys[key];
    }

    bool isMouseDown(uint8_t button)
    {
        return buttons[button];
    }

    uint64_t getWheelDelta()
    {
        return 0;
    }

    std::tuple<int64_t, int64_t> getMousePosition()
    {
        return {x, y};
    }

    static uint64_t getTime()
    {
        const uint64_t s = 1000, ms = 1000 * s, ns = 1000 * ms;
        timespec currTime{};
        clock_gettime(CLOCK_MONOTONIC, &currTime);
        return static_cast<uint64_t>(currTime.tv_sec) * ns + static_cast<uint64_t>(currTime.tv_nsec);
    }
};
} // namespace LunaLux
#endif