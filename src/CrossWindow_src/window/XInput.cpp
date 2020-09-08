//
// Created by luket on 05/06/2020.
//
#include "../Input.h"
#ifdef LLE_XBOX
#include <minwinbase.h>
#include <winerror.h>
namespace LunaLuxEngine::window_api
{
    Controller::Controller(int num)
    {
        _controllerNum = num - 1;
    }

    Controller::~Controller()
    {

    }

    XINPUT_STATE Controller::getState()
    {
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        XInputGetState(_controllerNum, &_controllerState);

        return _controllerState;
    }

    bool Controller::isConnected()
    {
        ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

        DWORD Result = XInputGetState(_controllerNum, &_controllerState);

        return Result == ERROR_SUCCESS;

    }

    void Controller::vibrate(int left, int right)
    {
        XINPUT_VIBRATION v;

        ZeroMemory(&v, sizeof(XINPUT_VIBRATION));

        v.wLeftMotorSpeed = left;
        v.wRightMotorSpeed = right;

        XInputSetState(_controllerNum, &v);
    }
}
#endif