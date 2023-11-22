#include <windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(30, 31, 38));
    wc.lpszClassName = L"test_class";
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindow(wc.lpszClassName, L"Ellipsed window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 500, 500, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        UnregisterClass(wc.lpszClassName, hInstance);
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_OK | MB_ICONERROR);
        return 0;
    }

    RECT rc;
    GetWindowRect(hWnd, &rc);
    HRGN rgn = CreateEllipticRgn(0, 0, rc.right - rc.left, rc.bottom - rc.top);
    SetWindowRgn(hWnd, rgn, TRUE);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
        TranslateMessage(&msg);
    }
    UnregisterClass(wc.lpszClassName, hInstance);
    return (int)msg.wParam;
}