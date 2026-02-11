#include "MouseDriver.h"
#include <iostream>

MouseDriver::MouseDriver() : deviceHandle(INVALID_HANDLE_VALUE) {}

MouseDriver::~MouseDriver()
{
    Cleanup();
}

bool MouseDriver::Initialize()
{
    try
    {
        std::string deviceName = "\\\\.\\cla300";

        deviceHandle = CreateFileA(deviceName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (deviceHandle == INVALID_HANDLE_VALUE)
        {
            DWORD error = GetLastError();
            return false;
        }
        std::cout << "[+] driver initialized successfully" << std::endl;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool MouseDriver::MouseMove(int x, int y, MouseFlags buttonFlags)
{
    if (deviceHandle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    try
    {
        NF_MOUSE_REQUEST request;
        request.x = x;
        request.y = y;
        request.ButtonFlags = (short)buttonFlags;

        DWORD bytesReturned = 0;
        BOOL result = DeviceIoControl(deviceHandle, IOCTL_MOUSE_MOVE, &request, sizeof(NF_MOUSE_REQUEST), NULL, 0, &bytesReturned, NULL);

        if (!result)
        {
            DWORD error = GetLastError();
        }

        return result != FALSE;
    }
    catch (...)
    {
        return false;
    }
}

bool MouseDriver::MouseButtonDown(MouseButton button)
{
    if (deviceHandle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    try
    {
        MouseFlags flags = None;
        switch (button)
        {
        case Left:
            flags = LeftButtonDown;
            break;
        case Right:
            flags = RightButtonDown;
            break;
        case Middle:
            flags = MiddleButtonDown;
            break;
        }

        NF_MOUSE_REQUEST request;
        request.x = 0;
        request.y = 0;
        request.ButtonFlags = (short)flags;

        DWORD bytesReturned = 0;
        BOOL result = DeviceIoControl(deviceHandle, IOCTL_MOUSE_MOVE, &request, sizeof(NF_MOUSE_REQUEST), NULL, 0, &bytesReturned, NULL);

        if (!result)
        {
            DWORD error = GetLastError();
        }

        return result != FALSE;
    }
    catch (...)
    {
        return false;
    }
}

bool MouseDriver::MouseButtonUp(MouseButton button)
{
    if (deviceHandle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    try
    {
        MouseFlags flags = None;
        switch (button)
        {
        case Left:
            flags = LeftButtonUp;
            break;
        case Right:
            flags = RightButtonUp;
            break;
        case Middle:
            flags = MiddleButtonUp;
            break;
        }

        NF_MOUSE_REQUEST request;
        request.x = 0;
        request.y = 0;
        request.ButtonFlags = (short)flags;

        DWORD bytesReturned = 0;
        BOOL result = DeviceIoControl(deviceHandle, IOCTL_MOUSE_MOVE, &request, sizeof(NF_MOUSE_REQUEST), NULL, 0, &bytesReturned, NULL);

        if (!result)
        {
            DWORD error = GetLastError();
        }

        return result != FALSE;
    }
    catch (...)
    {
        return false;
    }
}

bool MouseDriver::MouseClick(MouseButton button, int delay)
{
    bool downResult = MouseButtonDown(button);
    if (!downResult) return false;

    Sleep(delay);

    bool upResult = MouseButtonUp(button);
    return upResult;
}

bool MouseDriver::IsInitialized() const
{
    return deviceHandle != INVALID_HANDLE_VALUE;
}

void MouseDriver::Cleanup()
{
    if (deviceHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(deviceHandle);
        deviceHandle = INVALID_HANDLE_VALUE;
    }
}