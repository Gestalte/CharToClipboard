#include <windows.h>
#define UNICODE

#ifndef UNICODE
    #include <stdio.h>
#endif
#include <tchar.h>
#pragma comment(lib, "user32")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CenterWindow(HWND);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
                    
    MSG  msg;    
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Center";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
  
    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Char to Clipboard", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 240, 100, 0, 0, hInstance, 0);  

    while (GetMessage(&msg, NULL, 0, 0)) {
  
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

#define ID_BTN1 1
#define ID_BTN2 2
#define ID_BTN3 3
#define ID_BTN4 4

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    switch(msg) {
  
        case WM_CREATE: 
      
            CenterWindow(hwnd);

            CreateWindowW(L"Button", L"\u00EB", WS_VISIBLE | WS_CHILD , 5, 5, 50, 50, hwnd, (HMENU) ID_BTN1, NULL, NULL);   // ë
            CreateWindowW(L"Button", L"\u00EA", WS_VISIBLE | WS_CHILD , 60, 5, 50, 50, hwnd, (HMENU) ID_BTN2, NULL, NULL);  // ê
            CreateWindowW(L"Button", L"\u00E9", WS_VISIBLE | WS_CHILD , 115, 5, 50, 50, hwnd, (HMENU) ID_BTN3, NULL, NULL); // é
            CreateWindowW(L"Button", L"\u00EF", WS_VISIBLE | WS_CHILD , 170, 5, 50, 50, hwnd, (HMENU) ID_BTN4, NULL, NULL); // ï
            break;

        case WM_COMMAND:

        char* text;

        switch (LOWORD(wParam))
        {
        case ID_BTN1:
            text = "\u00EB"; // ë
            break;
        case ID_BTN2:
            text = "\u00EA"; // ê
            break;
        case ID_BTN3:
            text = "\u00E9"; // é
            break;
        case ID_BTN4:
            text = "\u00EF"; // ï
            break;
        default:
            text = "";
            break;
        }

        const size_t len = strlen(text) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), text, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        break;

        case WM_DESTROY: 
      
            PostQuitMessage(0);
            break;

        case WM_KEYDOWN:

        if (wParam == VK_ESCAPE){
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            //PostQuitMessage(0);
        }
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void CenterWindow(HWND hwnd) {

    RECT rc = {0};
    
    GetWindowRect(hwnd, &rc);
    int win_w = rc.right - rc.left;
    int win_h = rc.bottom - rc.top;

    int screen_w = GetSystemMetrics(SM_CXSCREEN);
    int screen_h = GetSystemMetrics(SM_CYSCREEN);
    
    SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w)/2, (screen_h - win_h)/2, 0, 0, SWP_NOSIZE);
}