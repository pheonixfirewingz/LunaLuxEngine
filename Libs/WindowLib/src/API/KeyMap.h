#pragma once
//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
/*
 * this is used to provide the Window.h with the current operating systems keyboard key map so the user can ask the
 * library for if a key is down. it will also provide the mouse button map as well.
 */
#include <cinttypes>
#if __has_include(<windows.h>)
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#    undef VK_NO_NAME
#    define VK_NO_NAME 0xFF
namespace LunaLux
{
[[maybe_unused]] const static uint8_t LLE_MOUSE_LEFT = 0x01;
[[maybe_unused]] const static uint8_t LLE_MOUSE_RIGHT = 0x02;
[[maybe_unused]] const static uint8_t LLE_MOUSE_WHEEL_CLICK = 0x03;

[[maybe_unused]] const static uint8_t LLE_KEY_0 = 0x30;
[[maybe_unused]] const static uint8_t LLE_KEY_1 = 0x31;
[[maybe_unused]] const static uint8_t LLE_KEY_2 = 0x32;
[[maybe_unused]] const static uint8_t LLE_KEY_3 = 0x33;
[[maybe_unused]] const static uint8_t LLE_KEY_4 = 0x34;
[[maybe_unused]] const static uint8_t LLE_KEY_5 = 0x35;
[[maybe_unused]] const static uint8_t LLE_KEY_6 = 0x36;
[[maybe_unused]] const static uint8_t LLE_KEY_7 = 0x37;
[[maybe_unused]] const static uint8_t LLE_KEY_8 = 0x38;
[[maybe_unused]] const static uint8_t LLE_KEY_9 = 0x39;
[[maybe_unused]] const static uint8_t LLE_KEY_A = 0x41;
[[maybe_unused]] const static uint8_t LLE_KEY_B = 0x42;
[[maybe_unused]] const static uint8_t LLE_KEY_C = 0x43;
[[maybe_unused]] const static uint8_t LLE_KEY_D = 0x44;
[[maybe_unused]] const static uint8_t LLE_KEY_E = 0x45;
[[maybe_unused]] const static uint8_t LLE_KEY_F = 0x46;
[[maybe_unused]] const static uint8_t LLE_KEY_G = 0x47;
[[maybe_unused]] const static uint8_t LLE_KEY_H = 0x48;
[[maybe_unused]] const static uint8_t LLE_KEY_I = 0x49;
[[maybe_unused]] const static uint8_t LLE_KEY_J = 0x4A;
[[maybe_unused]] const static uint8_t LLE_KEY_K = 0x4B;
[[maybe_unused]] const static uint8_t LLE_KEY_L = 0x4C;
[[maybe_unused]] const static uint8_t LLE_KEY_M = 0x4D;
[[maybe_unused]] const static uint8_t LLE_KEY_N = 0x4E;
[[maybe_unused]] const static uint8_t LLE_KEY_O = 0x4F;
[[maybe_unused]] const static uint8_t LLE_KEY_P = 0x50;
[[maybe_unused]] const static uint8_t LLE_KEY_Q = 0x51;
[[maybe_unused]] const static uint8_t LLE_KEY_R = 0x52;
[[maybe_unused]] const static uint8_t LLE_KEY_S = 0x53;
[[maybe_unused]] const static uint8_t LLE_KEY_T = 0x54;
[[maybe_unused]] const static uint8_t LLE_KEY_U = 0x55;
[[maybe_unused]] const static uint8_t LLE_KEY_V = 0x56;
[[maybe_unused]] const static uint8_t LLE_KEY_W = 0x57;
[[maybe_unused]] const static uint8_t LLE_KEY_X = 0x58;
[[maybe_unused]] const static uint8_t LLE_KEY_Y = 0x59;
[[maybe_unused]] const static uint8_t LLE_KEY_Z = 0x5A;
[[maybe_unused]] const static uint8_t LLE_KEY_APOSTROPHE = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_BACKSLASH = VK_NONAME;  // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_COMMA = VK_OEM_COMMA;
[[maybe_unused]] const static uint8_t LLE_KEY_GRAVE_ACCENT = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_BRACKET = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_MINUS = VK_OEM_MINUS;
[[maybe_unused]] const static uint8_t LLE_KEY_PERIOD = VK_OEM_PERIOD;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_BRACKET = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_SEMICOLON = VK_NONAME;     // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_SLASH = VK_NONAME;         // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_WORLD_2 = VK_NONAME;       // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_BACKSPACE = VK_BACK;
[[maybe_unused]] const static uint8_t LLE_KEY_DELETE = VK_DELETE;
[[maybe_unused]] const static uint8_t LLE_KEY_END = VK_END;
[[maybe_unused]] const static uint8_t LLE_KEY_ENTER = VK_EXECUTE;
[[maybe_unused]] const static uint8_t LLE_KEY_ESCAPE = VK_ESCAPE;
[[maybe_unused]] const static uint8_t LLE_KEY_HOME = VK_HOME;
[[maybe_unused]] const static uint8_t LLE_KEY_INSERT = VK_INSERT;
[[maybe_unused]] const static uint8_t LLE_KEY_MENU = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_PAGE_DOWN = VK_NEXT;
[[maybe_unused]] const static uint8_t LLE_KEY_PAGE_UP = VK_PRIOR;
[[maybe_unused]] const static uint8_t LLE_KEY_PAUSE = VK_PAUSE;
[[maybe_unused]] const static uint8_t LLE_KEY_SPACE = VK_SPACE;
[[maybe_unused]] const static uint8_t LLE_KEY_TAB = VK_TAB;
[[maybe_unused]] const static uint8_t LLE_KEY_CAPS_LOCK = VK_CAPITAL;
[[maybe_unused]] const static uint8_t LLE_KEY_NUM_LOCK = VK_NUMLOCK;
[[maybe_unused]] const static uint8_t LLE_KEY_SCROLL_LOCK = VK_SCROLL;
[[maybe_unused]] const static uint8_t LLE_KEY_F1 = VK_F1;
[[maybe_unused]] const static uint8_t LLE_KEY_F2 = VK_F2;
[[maybe_unused]] const static uint8_t LLE_KEY_F3 = VK_F3;
[[maybe_unused]] const static uint8_t LLE_KEY_F4 = VK_F4;
[[maybe_unused]] const static uint8_t LLE_KEY_F5 = VK_F5;
[[maybe_unused]] const static uint8_t LLE_KEY_F6 = VK_F6;
[[maybe_unused]] const static uint8_t LLE_KEY_F7 = VK_F7;
[[maybe_unused]] const static uint8_t LLE_KEY_F8 = VK_F8;
[[maybe_unused]] const static uint8_t LLE_KEY_F9 = VK_F9;
[[maybe_unused]] const static uint8_t LLE_KEY_F10 = VK_F10;
[[maybe_unused]] const static uint8_t LLE_KEY_F11 = VK_F11;
[[maybe_unused]] const static uint8_t LLE_KEY_F12 = VK_F12;
[[maybe_unused]] const static uint8_t LLE_KEY_F13 = VK_F13;
[[maybe_unused]] const static uint8_t LLE_KEY_F14 = VK_F14;
[[maybe_unused]] const static uint8_t LLE_KEY_F15 = VK_F15;
[[maybe_unused]] const static uint8_t LLE_KEY_F16 = VK_F16;
[[maybe_unused]] const static uint8_t LLE_KEY_F17 = VK_F17;
[[maybe_unused]] const static uint8_t LLE_KEY_F18 = VK_F18;
[[maybe_unused]] const static uint8_t LLE_KEY_F19 = VK_F19;
[[maybe_unused]] const static uint8_t LLE_KEY_F20 = VK_F20;
[[maybe_unused]] const static uint8_t LLE_KEY_F21 = VK_F21;
[[maybe_unused]] const static uint8_t LLE_KEY_F22 = VK_F22;
[[maybe_unused]] const static uint8_t LLE_KEY_F23 = VK_F23;
[[maybe_unused]] const static uint8_t LLE_KEY_F24 = VK_F24;
[[maybe_unused]] const static uint8_t LLE_KEY_ALT = VK_MENU;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_ALT = VK_LMENU;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_ALT = VK_RMENU;
[[maybe_unused]] const static uint8_t LLE_KEY_CONTROL = VK_CONTROL;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_CONTROL = VK_LCONTROL;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_CONTROL = VK_RCONTROL;
[[maybe_unused]] const static uint8_t LLE_KEY_SHIFT = VK_SHIFT;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_SHIFT = VK_LSHIFT;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_SHIFT = VK_RSHIFT;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_SUPER = VK_LWIN;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_SUPER = VK_RWIN;
[[maybe_unused]] const static uint8_t LLE_KEY_PRINT_SCREEN = VK_SNAPSHOT;
[[maybe_unused]] const static uint8_t LLE_KEY_DOWN = VK_DOWN;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT = VK_LEFT;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT = VK_RIGHT;
[[maybe_unused]] const static uint8_t LLE_KEY_UP = VK_UP;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_0 = VK_NUMPAD0;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_1 = VK_NUMPAD1;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_2 = VK_NUMPAD2;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_3 = VK_NUMPAD3;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_4 = VK_NUMPAD4;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_5 = VK_NUMPAD5;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_6 = VK_NUMPAD6;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_7 = VK_NUMPAD7;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_8 = VK_NUMPAD8;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_9 = VK_NUMPAD9;
[[maybe_unused]] const static uint8_t LLE_KEY_ADD = VK_ADD;
[[maybe_unused]] const static uint8_t LLE_KEY_DECIMAL = VK_DECIMAL;
[[maybe_unused]] const static uint8_t LLE_KEY_DIVIDE = VK_DIVIDE;
[[maybe_unused]] const static uint8_t LLE_KEY_EQUAL = VK_NONAME; // needs finding
[[maybe_unused]] const static uint8_t LLE_KEY_MULTIPLY = VK_MULTIPLY;
[[maybe_unused]] const static uint8_t LLE_KEY_SUBTRACT = VK_SUBTRACT;
} // namespace LunaLux
#elif __has_include(<xcb/xcb.h>)
#    define VK_NO_NAME 255
namespace LunaLux
{
[[maybe_unused]] const static uint8_t LLE_MOUSE_LEFT = 1;
[[maybe_unused]] const static uint8_t LLE_MOUSE_RIGHT = 3;
[[maybe_unused]] const static uint8_t LLE_MOUSE_WHEEL_CLICK = 2;

[[maybe_unused]] const static uint8_t LLE_KEY_1 = 10;
[[maybe_unused]] const static uint8_t LLE_KEY_2 = 11;
[[maybe_unused]] const static uint8_t LLE_KEY_3 = 12;
[[maybe_unused]] const static uint8_t LLE_KEY_4 = 13;
[[maybe_unused]] const static uint8_t LLE_KEY_5 = 14;
[[maybe_unused]] const static uint8_t LLE_KEY_6 = 15;
[[maybe_unused]] const static uint8_t LLE_KEY_7 = 16;
[[maybe_unused]] const static uint8_t LLE_KEY_8 = 17;
[[maybe_unused]] const static uint8_t LLE_KEY_9 = 18;
[[maybe_unused]] const static uint8_t LLE_KEY_0 = 19;
[[maybe_unused]] const static uint8_t LLE_KEY_A = 38;
[[maybe_unused]] const static uint8_t LLE_KEY_B = 56;
[[maybe_unused]] const static uint8_t LLE_KEY_C = 54;
[[maybe_unused]] const static uint8_t LLE_KEY_D = 40;
[[maybe_unused]] const static uint8_t LLE_KEY_E = 26;
[[maybe_unused]] const static uint8_t LLE_KEY_F = 41;
[[maybe_unused]] const static uint8_t LLE_KEY_G = 42;
[[maybe_unused]] const static uint8_t LLE_KEY_H = 43;
[[maybe_unused]] const static uint8_t LLE_KEY_I = 31;
[[maybe_unused]] const static uint8_t LLE_KEY_J = 44;
[[maybe_unused]] const static uint8_t LLE_KEY_K = 45;
[[maybe_unused]] const static uint8_t LLE_KEY_L = 46;
[[maybe_unused]] const static uint8_t LLE_KEY_M = 58;
[[maybe_unused]] const static uint8_t LLE_KEY_N = 57;
[[maybe_unused]] const static uint8_t LLE_KEY_O = 32;
[[maybe_unused]] const static uint8_t LLE_KEY_P = 33;
[[maybe_unused]] const static uint8_t LLE_KEY_Q = 24;
[[maybe_unused]] const static uint8_t LLE_KEY_R = 27;
[[maybe_unused]] const static uint8_t LLE_KEY_S = 39;
[[maybe_unused]] const static uint8_t LLE_KEY_T = 28;
[[maybe_unused]] const static uint8_t LLE_KEY_U = 30;
[[maybe_unused]] const static uint8_t LLE_KEY_V = 55;
[[maybe_unused]] const static uint8_t LLE_KEY_W = 25;
[[maybe_unused]] const static uint8_t LLE_KEY_X = 53;
[[maybe_unused]] const static uint8_t LLE_KEY_Y = 29;
[[maybe_unused]] const static uint8_t LLE_KEY_Z = 52;
[[maybe_unused]] const static uint8_t LLE_KEY_APOSTROPHE = 0x0027;
[[maybe_unused]] const static uint8_t LLE_KEY_BACKSLASH = 0x005c;
[[maybe_unused]] const static uint8_t LLE_KEY_COMMA = 0x003a;
[[maybe_unused]] const static uint8_t LLE_KEY_GRAVE_ACCENT = 0x0060;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_BRACKET = 0x005b;
[[maybe_unused]] const static uint8_t LLE_KEY_MINUS = 0x002d;
[[maybe_unused]] const static uint8_t LLE_KEY_PERIOD = 0x002e;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_BRACKET = 0x005d;
[[maybe_unused]] const static uint8_t LLE_KEY_SEMICOLON = 0x003b;
[[maybe_unused]] const static uint8_t LLE_KEY_SLASH = 0x002f;
[[maybe_unused]] const static uint8_t LLE_KEY_WORLD_2 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_BACKSPACE = 22;
[[maybe_unused]] const static uint8_t LLE_KEY_DELETE = 119;
[[maybe_unused]] const static uint8_t LLE_KEY_END = 115;
[[maybe_unused]] const static uint8_t LLE_KEY_ENTER = 36;
[[maybe_unused]] const static uint8_t LLE_KEY_ESCAPE = 9;
[[maybe_unused]] const static uint8_t LLE_KEY_HOME = 110;
[[maybe_unused]] const static uint8_t LLE_KEY_INSERT = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_MENU = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_PAGE_DOWN = 117;
[[maybe_unused]] const static uint8_t LLE_KEY_PAGE_UP = 112;
[[maybe_unused]] const static uint8_t LLE_KEY_PAUSE = 127;
[[maybe_unused]] const static uint8_t LLE_KEY_SPACE = 0x0020;
[[maybe_unused]] const static uint8_t LLE_KEY_TAB = 23;
[[maybe_unused]] const static uint8_t LLE_KEY_CAPS_LOCK = 66;
[[maybe_unused]] const static uint8_t LLE_KEY_NUM_LOCK = 77;
[[maybe_unused]] const static uint8_t LLE_KEY_SCROLL_LOCK = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F1 = 67;
[[maybe_unused]] const static uint8_t LLE_KEY_F2 = 68;
[[maybe_unused]] const static uint8_t LLE_KEY_F3 = 69;
[[maybe_unused]] const static uint8_t LLE_KEY_F4 = 70;
[[maybe_unused]] const static uint8_t LLE_KEY_F5 = 71;
[[maybe_unused]] const static uint8_t LLE_KEY_F6 = 72;
[[maybe_unused]] const static uint8_t LLE_KEY_F7 = 73;
[[maybe_unused]] const static uint8_t LLE_KEY_F8 = 74;
[[maybe_unused]] const static uint8_t LLE_KEY_F9 = 75;
[[maybe_unused]] const static uint8_t LLE_KEY_F10 = 76;
[[maybe_unused]] const static uint8_t LLE_KEY_F11 = 95;
[[maybe_unused]] const static uint8_t LLE_KEY_F12 = 96;
[[maybe_unused]] const static uint8_t LLE_KEY_F13 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F14 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F15 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F16 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F17 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F18 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F19 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F20 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F21 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F22 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F23 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_F24 = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_ALT = 64;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_ALT = 108;
[[maybe_unused]] const static uint8_t LLE_KEY_ALT = LLE_KEY_LEFT_ALT;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_CONTROL = 37;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_CONTROL = VK_NO_NAME;
[[maybe_unused]] const static uint8_t LLE_KEY_CONTROL = LLE_KEY_LEFT_CONTROL;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_SHIFT = 50;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_SHIFT = 62;
[[maybe_unused]] const static uint8_t LLE_KEY_SHIFT = LLE_KEY_LEFT_SHIFT;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT_SUPER = 133;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT_SUPER = LLE_KEY_LEFT_SUPER;
[[maybe_unused]] const static uint8_t LLE_KEY_DOWN = 116;
[[maybe_unused]] const static uint8_t LLE_KEY_LEFT = 113;
[[maybe_unused]] const static uint8_t LLE_KEY_RIGHT = 114;
[[maybe_unused]] const static uint8_t LLE_KEY_UP = 111;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_0 = 90;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_1 = 87;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_2 = 88;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_3 = 89;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_4 = 83;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_5 = 84;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_6 = 85;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_7 = 79;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_8 = 80;
[[maybe_unused]] const static uint8_t LLE_KEY_NUMPAD_9 = 81;
[[maybe_unused]] const static uint8_t LLE_KEY_ADD = 86;
[[maybe_unused]] const static uint8_t LLE_KEY_DECIMAL = 91;
[[maybe_unused]] const static uint8_t LLE_KEY_DIVIDE = 106;
[[maybe_unused]] const static uint8_t LLE_KEY_EQUAL = 21;
[[maybe_unused]] const static uint8_t LLE_KEY_MULTIPLY = 63;
[[maybe_unused]] const static uint8_t LLE_KEY_SUBTRACT = 82;
} // namespace LunaLux
#endif