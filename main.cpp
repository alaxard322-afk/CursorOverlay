#include <windows.h>

HINSTANCE hInst;
POINT mousePos;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            GetCursorPos(&mousePos);

            SetBkMode(hdc, TRANSPARENT);

            HPEN pen = CreatePen(PS_SOLID, 3, RGB(0,0,0));
            HPEN oldPen = (HPEN)SelectObject(hdc, pen);

            MoveToEx(hdc, 20, 5, NULL);
            LineTo(hdc, 20, 45);

            MoveToEx(hdc, 5, 25, NULL);
            LineTo(hdc, 45, 25);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_TIMER:
        {
            POINT p;
            GetCursorPos(&p);

            SetWindowPos(hwnd,
                HWND_TOPMOST,
                p.x-25,
                p.y-25,
                50,
                50,
                SWP_NOACTIVATE);

            InvalidateRect(hwnd,NULL,FALSE);
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hwnd,msg,wParam,lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE,
                   LPSTR,
                   int)
{
    hInst=hInstance;

    WNDCLASS wc={0};
    wc.lpfnWndProc=WndProc;
    wc.hInstance=hInstance;
    wc.lpszClassName="CursorOverlay";

    RegisterClass(&wc);

    HWND hwnd=CreateWindowEx(
        WS_EX_TOPMOST |
        WS_EX_LAYERED |
        WS_EX_TRANSPARENT |
        WS_EX_TOOLWINDOW,
        "CursorOverlay",
        "",
        WS_POPUP,
        0,0,50,50,
        NULL,NULL,hInstance,NULL);

    SetLayeredWindowAttributes(hwnd,0,255,LWA_ALPHA);

    ShowWindow(hwnd,SW_SHOW);

    SetTimer(hwnd,1,16,NULL);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
