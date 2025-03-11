#include <windows.h>
#include <stdio.h>
#include <process.h>

#define IDC_MAIN_EDIT 101
#define IDC_MAIN_BUTTON 102

HWND hEdit;
HANDLE hProcess;

// Функция для чтения вывода asOS.exe и отображения его в текстовом поле
unsigned __stdcall ReadOutput(void* pArguments) {
    HANDLE hPipeRead = (HANDLE)pArguments;
    char buffer[1024];
    DWORD dwRead;

    while (ReadFile(hPipeRead, buffer, sizeof(buffer) - 1, &dwRead, NULL) && dwRead) {
        buffer[dwRead] = '\0';
        SendMessage(hEdit, EM_SETSEL, -1, -1);
        SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
    }

    return 0;
}

// Функция для запуска asOS.exe и перенаправления его вывода
void StartAsOS(HWND hwnd) {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hPipeRead, hPipeWrite;
    CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hPipeWrite;
    si.hStdError = hPipeWrite;

    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL, "asOS.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        hProcess = pi.hProcess;
        CloseHandle(pi.hThread);
        CloseHandle(hPipeWrite);

        _beginthreadex(NULL, 0, ReadOutput, hPipeRead, 0, NULL);
    } else {
        MessageBox(hwnd, "Failed to start asOS.exe", "Error", MB_OK | MB_ICONERROR);
    }
}

// Обработчик сообщений окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 
                0, 0, 640, 480, hwnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
            CreateWindow("BUTTON", "Start asOS", 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
                10, 490, 100, 30, hwnd, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_MAIN_BUTTON) {
                StartAsOS(hwnd);
            }
            break;
        }
        case WM_CLOSE:
            if (hProcess) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Точка входа
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "asOSInterfaceClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "asOSInterfaceClass", "asOS Interface", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 660, 560, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}