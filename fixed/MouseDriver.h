#pragma once
#include <windows.h>
#include <string>

class MouseDriver
{
public:
    enum MouseFlags : short
    {
        None = 0,
        LeftButtonDown = 1,
        LeftButtonUp = 2,
        RightButtonDown = 4,
        RightButtonUp = 8,
        MiddleButtonDown = 16,
        MiddleButtonUp = 32,
        XButton1Down = 64,
        XButton1Up = 128,
        XButton2Down = 256,
        XButton2Up = 512,
        MouseWheel = 1024,
        MouseHorizontalWheel = 2048
    };

    enum MouseButton
    {
        Left,
        Right,
        Middle
    };

    struct NF_MOUSE_REQUEST
    {
        int x;
        int y;
        short ButtonFlags;
    };

    MouseDriver();
    ~MouseDriver();

    bool Initialize();
    bool MouseMove(int x, int y, MouseFlags buttonFlags = None);
    bool MouseButtonDown(MouseButton button);
    bool MouseButtonUp(MouseButton button);
    bool MouseClick(MouseButton button, int delay = 10);
    bool IsInitialized() const;
    void Cleanup();

private:
    HANDLE deviceHandle;
    static const DWORD IOCTL_MOUSE_MOVE = 0x23FACC00;

    MouseDriver(const MouseDriver&) = delete;
    MouseDriver& operator=(const MouseDriver&) = delete;
};