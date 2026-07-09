#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_PAINT)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HBRUSH brush = CreateSolidBrush(RGB(255,255,255));
        FillRect(hdc, &ps.rcPaint, brush);
        DeleteObject(brush);

        HPEN pen = CreatePen(PS_SOLID, 3, RGB(0,0,0));
        SelectObject(hdc, pen);

        MoveToEx(hdc, 25, 5, NULL);
        LineTo(hdc, 25, 45);

        MoveToEx(hdc, 5, 25, NULL);
        LineTo(hdc, 45, 25);

        DeleteObject(pen);

        EndPaint(hwnd, &ps);
        return 0;
    }

    return DefWindowProc(hwnd,msg,wParam,lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,int)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CursorOverlay";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST |
        WS_EX_LAYERED |
        WS_EX_TRANSPARENT |
        WS_EX_TOOLWINDOW,
        "CursorOverlay",
        "",
        WS_POPUP,
        0,0,50,50,
        NULL,NULL,hInstance,NULL);

    // делаем белый цвет прозрачным
    SetLayeredWindowAttributes(
        hwnd,
        RGB(255,255,255),
        0,
        LWA_COLORKEY);

    ShowWindow(hwnd,SW_SHOW);

    SetTimer(hwnd,1,16,NULL);

    MSG msg;

    while(GetMessage(&msg,NULL,0,0))
    {
        if(msg.message==WM_TIMER)
        {
            POINT p;
            GetCursorPos(&p);

            SetWindowPos(
                hwnd,
                HWND_TOPMOST,
                p.x-25,
                p.y-25,
                50,
                50,
                SWP_NOACTIVATE);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
