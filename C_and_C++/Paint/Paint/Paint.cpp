#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <WindowsX.h>
#include <vector>
#include <queue>
#include <d2d1.h>
#include "framework.h"
using namespace std;

#define ID_COMBOBOX_1 10001
#define ID_COMBOBOX_2 10002
#define ID_COMBOBOX_3 10003
#define ID_BUTTON_1 10004
#define ID_CHECKBOX_1 10005
#define ID_SCROLLBAR_RED_COLOR 10006
#define ID_SCROLLBAR_GREEN_COLOR 10007
#define ID_SCROLLBAR_BLUE_COLOR 10008

#define SetRValue(c, r) ((COLORREF)((c & 0x00FFFF00) | ((BYTE)(r))))
#define SetGValue(c, g) ((COLORREF)((c & 0x00FF00FF) | ((BYTE)(g) << 8)))
#define SetBValue(c, b) ((COLORREF)((c & 0x0000FFFF) | ((BYTE)(b) << 16)))

const int x_size = 750, y_size = 500;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Paint");

HWND hwnd;
HDC hdc;
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void OnLButtonDown(int x, int y);
void OnLButtonUp(int x, int y);
void OnMouseMove(int x, int y);
void EnableCustomColor(bool enable);

enum class TOOLS {
    PEN,
    ERASER,
    RECT,
    ELLIPSE,
    FILLING
};
 
TOOLS tool = TOOLS::PEN;
COLORREF color = RGB(0, 0, 0);
int width = 3;

struct LINE {
    int x1, y1, x2, y2;
};

bool mouse_down = false;
bool solid = false;
POINT point;

HWND hWndComboBox1, hWndComboBox2, hWndComboBox3;
HWND hwndButton;
HWND hWndCheckBox;
HWND hMT;
HWND hCstmClrT, hRT, hGT, hBT, hRScroll, hGScroll, hBScroll;

RECT SampleRect;

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), 
                  _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, x_size, y_size, NULL,
                             NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"),
                   _T("Windows Desktop Guided Tour"), NULL);

        return 1;
    }   

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    hwnd = hWnd;
    hdc = GetDC(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdct;
    TCHAR greeting[] = _T("Hello, Windows desktop!");

    switch (message) {
        case WM_CREATE: {
            //painting tools
            CreateWindow(_T("STATIC"), _T("Tool:"), SS_CENTER | WS_CHILD | WS_VISIBLE,
                10, 0, 70, 15, hWnd, NULL, hInst, NULL);

            hWndComboBox1 = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN,
                10, 15, 70, y_size, hWnd, (HMENU)ID_COMBOBOX_1,
                (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

            SendMessage(hWndComboBox1, CB_ADDSTRING, 0, (LPARAM)L"Pen");
            SendMessage(hWndComboBox1, CB_ADDSTRING, 0, (LPARAM)L"Eraser");
            SendMessage(hWndComboBox1, CB_ADDSTRING, 0, (LPARAM)L"Rect");
            SendMessage(hWndComboBox1, CB_ADDSTRING, 0, (LPARAM)L"Ellipse");
            SendMessage(hWndComboBox1, CB_ADDSTRING, 0, (LPARAM)L"Filling");

            SendMessage(hWndComboBox1, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

            //checkbox
            hWndCheckBox = CreateWindow(L"BUTTON", L"Solid", WS_TABSTOP | WS_CHILD | BS_CHECKBOX | BST_CHECKED,
                10, 40, 70, 24, hWnd, (HMENU)ID_CHECKBOX_1,
                (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

            //painting size
            CreateWindow(_T("STATIC"), _T("Size:"), SS_CENTER | WS_CHILD | WS_VISIBLE,
                80, 0, 70, 15, hWnd, NULL, hInst, NULL);

            hWndComboBox3 = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                80, 15, 70, y_size, hWnd, (HMENU)ID_COMBOBOX_3,
                (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"1");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"3");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"5");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"10");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"30");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_3), CB_ADDSTRING, 0, (LPARAM)L"50");

            SendMessage(hWndComboBox3, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);

            //"clear all" button
            hwndButton = CreateWindow(L"BUTTON", L"Clear all", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                160, 0, 70, 40, hWnd, (HMENU)ID_BUTTON_1,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
            
            //painting colors
            CreateWindow(_T("STATIC"), _T("Color:"), SS_CENTER | WS_CHILD | WS_VISIBLE,
                240, 0, 70, 15, hWnd, NULL, hInst, NULL);

            hWndComboBox2 = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                240, 15, 70, y_size, hWnd, (HMENU)ID_COMBOBOX_2,
                (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Black");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Red");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Green");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Blue");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Yellow");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Aqua");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Fuchsia");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Pink");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Gray");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Khaki");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"White");
            SendMessage(GetDlgItem(hWnd, ID_COMBOBOX_2), CB_ADDSTRING, 0, (LPARAM)L"Custom");

            SendMessage(hWndComboBox2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
            //menu text
            hMT = CreateWindow(_T("STATIC"), _T("***   Welcome to paint!   ***"), SS_CENTER | WS_CHILD | WS_VISIBLE,
                320, 0, 265, 15, hWnd, NULL,
                hInst, NULL);

            //Custom color
            hCstmClrT = CreateWindow(_T("STATIC"), _T("Custom color:"), SS_CENTER | WS_CHILD,
                320, 0, 265, 15, hWnd, NULL,
                hInst, NULL);
           
            hRT = CreateWindow(_T("STATIC"), _T("R"), SS_CENTER | WS_CHILD,
                320, 15, 10, 15, hWnd, NULL,
                hInst, NULL);
            hGT = CreateWindow(_T("STATIC"), _T("G"), SS_CENTER | WS_CHILD,
                320, 30, 10, 15, hWnd, NULL,
                hInst, NULL, hInst, NULL);
            hBT = CreateWindow(_T("STATIC"), _T("B"), SS_CENTER | WS_CHILD,
                320, 45, 10, 15, hWnd, NULL,
                hInst, NULL);

            hRScroll = CreateWindow(_T("SCROLLBAR"), _T("R"), WS_CHILD,
                330, 15, 255, 15, hWnd, (HMENU)ID_SCROLLBAR_RED_COLOR, hInst, NULL);
            SetScrollRange(hRScroll, SB_CTL, 0, 255, TRUE);

            hGScroll = CreateWindow(_T("SCROLLBAR"), _T(""), WS_CHILD,
                330, 30, 255, 15, hWnd, (HMENU)ID_SCROLLBAR_GREEN_COLOR, hInst, NULL);
            SetScrollRange(hGScroll, SB_CTL, 0, 255, TRUE);

            hBScroll = CreateWindow(_T("SCROLLBAR"), _T(""), WS_CHILD,
                330, 45, 255, 15, hWnd, (HMENU)ID_SCROLLBAR_BLUE_COLOR, hInst, NULL);
            SetScrollRange(hBScroll, SB_CTL, 0, 255, TRUE);
            
            //sample
            CreateWindow(_T("STATIC"), _T("Sample:"), SS_CENTER | WS_CHILD | WS_VISIBLE,
                610, 0, 110, 15, hWnd, NULL,
                hInst, NULL);
            SampleRect.top = 15;
            SampleRect.bottom = 65;
            SampleRect.left = 600;
            SampleRect.right = 730;
            //перерисовка sample
            InvalidateRect(hWnd, &SampleRect, 1);
        }
        case WM_PAINT: {
            hdct = BeginPaint(hWnd, &ps);
            hdct = hdc;
            //sample line
            HPEN pen = CreatePen(PS_SOLID, width, color);
            SelectObject(hdc, pen);
            MoveToEx(hdc, 630, 40, NULL);
            LineTo(hdc, 700, 40);
            DeleteObject(pen);

            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY: {
            return 0;
        }
        case WM_LBUTTONDOWN: {
            OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
            return 0; 
        }
        case WM_LBUTTONUP: {
            OnLButtonUp(LOWORD(lParam), HIWORD(lParam));
            return 0; 
        }
        case WM_MOUSEMOVE: {
            OnMouseMove(LOWORD(lParam), HIWORD(lParam));
            return 0; 
        }
        case WM_COMMAND: {
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                int ind;
                switch (LOWORD(wParam)) {
                case ID_COMBOBOX_1:
                    ind = SendMessage(hWndComboBox1, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                    switch (ind) {
                    case 0:
                        tool = TOOLS::PEN;
                        ShowWindow(hWndCheckBox, SW_HIDE);
                        break;
                    case 1:
                        tool = TOOLS::ERASER;
                        ShowWindow(hWndCheckBox, SW_HIDE);
                        break;
                    case 2:
                        tool = TOOLS::RECT;
                        ShowWindow(hWndCheckBox, SW_SHOW);
                        break;
                    case 3:
                        tool = TOOLS::ELLIPSE;
                        ShowWindow(hWndCheckBox, SW_SHOW);
                        break;
                    case 4:
                        tool = TOOLS::FILLING;
                        ShowWindow(hWndCheckBox, SW_HIDE);
                        break;
                    default:
                        break;
                    }
                    break;

                case ID_COMBOBOX_2:
                    ind = SendMessage(hWndComboBox2, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                    switch (ind) {
                    case 0:
                        color = RGB(0, 0, 0);
                        EnableCustomColor(false);
                        break;
                    case 1:
                        color = RGB(255, 0, 0);
                        EnableCustomColor(false);
                        break;
                    case 2:
                        color = RGB(0, 255, 0);
                        EnableCustomColor(false);
                        break;
                    case 3:
                        color = RGB(0, 0, 255);
                        EnableCustomColor(false);
                        break;
                    case 4:
                        color = RGB(255, 255, 0);
                        EnableCustomColor(false);
                        break;
                    case 5:
                        color = RGB(0, 255, 255);
                        EnableCustomColor(false);
                        break;
                    case 6:
                        color = RGB(255, 0, 255);
                        EnableCustomColor(false);
                        break;
                    case 7:
                        color = RGB(255, 192, 203);
                        EnableCustomColor(false);
                        break;
                    case 8:
                        color = RGB(128, 128, 128);
                        EnableCustomColor(false);
                        break;
                    case 9:
                        color = RGB(189, 183, 107);
                        EnableCustomColor(false);
                        break;
                    case 10:
                        color = RGB(255, 255, 255);
                        EnableCustomColor(false);
                        break;
                    case 11:
                        EnableCustomColor(true);
                    default:
                        break;
                    }
                    break;

                case ID_COMBOBOX_3:
                    ind = SendMessage(hWndComboBox3, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                    switch (ind) {
                    case 0:
                        width = 1;
                        break;
                    case 1:
                        width = 3;
                        break;
                    case 2:
                        width = 5;
                        break;
                    case 3:
                        width = 10;
                        break;
                    case 4:
                        width = 30;
                        break;
                    case 5:
                        width = 50;
                        break;
                    default:
                        break;
                    }
                    //перерисовка sample
                    InvalidateRect(hWnd, &SampleRect, 1);
                    break;
                default:
                    break;
                }
            }
            case WM_VSCROLL:
            case WM_HSCROLL: {
                int scrollNum = -1 ,clrNum = 0;
                if (hRScroll == (HWND)lParam) {
                    scrollNum = 0;
                    clrNum = GetRValue(color);
                } else if (hGScroll == (HWND)lParam) {
                    scrollNum = 1;
                    clrNum = GetGValue(color);
                } else if (hBScroll == (HWND)lParam) {
                    scrollNum = 2;
                    clrNum = GetBValue(color);
                }
                
                switch (LOWORD(wParam)) {
                    case SB_PAGERIGHT: //на страницу вправо
                        clrNum += 10;
                        break;
                    case SB_LINERIGHT: //на одну позицию вправо
                        clrNum += 1;
                        break;
                    case SB_PAGELEFT: //на страницу влево
                        clrNum -= 10;
                        break;
                    case SB_LINELEFT: //на одну позицию влево
                        clrNum -= 1;
                        break;
                    case SB_TOP: //максимальное значение
                        clrNum = 255;
                        break;
                    case SB_BOTTOM: //минимальное значение
                        clrNum = 0;
                        break;
                    case SB_THUMBPOSITION: //произвольное перемещение
                    case SB_THUMBTRACK:
                        clrNum = HIWORD(wParam);
                        break;
                    default: 
                        break;
                }
                if (scrollNum == 0) {
                    SetScrollPos(hRScroll, SB_CTL, clrNum, TRUE);
                    color = SetRValue(color, clrNum);
                } else if (scrollNum == 1) {
                    SetScrollPos(hGScroll, SB_CTL, clrNum, TRUE);
                    color = SetGValue(color, clrNum);
                } else if (scrollNum == 2) {
                    SetScrollPos(hBScroll, SB_CTL, clrNum, TRUE);
                    color = SetBValue(color, clrNum);
                }
                //перерисовка sample
                InvalidateRect(hWnd, &SampleRect, 1);
            }
            // "clear all" button and checkbox
            if (LOWORD(wParam) == ID_BUTTON_1) {
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (LOWORD(wParam) == ID_CHECKBOX_1) {
                solid = !solid;
            }
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

void OnLButtonDown(int x, int y)
{
    switch (tool) {
        case TOOLS::PEN:
        case TOOLS::ERASER:
        {
            mouse_down = TRUE;
            point.x = x;
            point.y = y;
            return;
        }

        case TOOLS::RECT:
        case TOOLS::ELLIPSE:
        {
            point.x = x;
            point.y = y;
            return;
        }

        case TOOLS::FILLING:
        {
            HDC hdc = GetDC(hwnd);
            HBRUSH br = CreateSolidBrush(color);
            SelectObject(hdc, br);
            ExtFloodFill(hdc, x, y, GetPixel(hdc, x, y), FLOODFILLSURFACE);
            DeleteObject(br);
            ReleaseDC(hwnd, hdc);
            return;
        }

        default: 
            return;
    }
}

void OnLButtonUp(int x, int y)
{
    switch (tool) {
    case TOOLS::PEN:
    {
        if (mouse_down) {
            HDC hdc = GetDC(hwnd);
            HPEN pen = CreatePen(PS_SOLID, width, color);
            SelectObject(hdc, pen);
            MoveToEx(hdc, point.x, point.y, NULL);
            LineTo(hdc, point.x = x, point.y = y);
            DeleteObject(pen);
            ReleaseDC(hwnd, hdc);
        }
        mouse_down = false;
        return;
    }
    case TOOLS::ERASER:
    {
        if (mouse_down) {
            HDC hdc = GetDC(hwnd);
            HPEN pen = CreatePen(PS_SOLID, width, RGB(255,255,255));
            SelectObject(hdc, pen);
            MoveToEx(hdc, point.x, point.y, NULL);
            LineTo(hdc, point.x = x, point.y = y);
            DeleteObject(pen);
            ReleaseDC(hwnd, hdc);
        }
        mouse_down = false;
        return;
    }
    case TOOLS::ELLIPSE:
    case TOOLS::RECT:
    {
        HDC hdc = GetDC(hwnd);
        HPEN pen = CreatePen(PS_SOLID, width, color);
        SelectObject(hdc, pen);
        HBRUSH brush = NULL;
        if (solid) {
            brush = CreateSolidBrush(color);
            SelectObject(hdc, brush);
        }
        int dx = abs(x - point.x);
        int dy = abs(y - point.y);
        if (tool == TOOLS::ELLIPSE) {
            Ellipse(hdc, point.x - dx, point.y - dy, point.x + dx, point.y + dy);
        }
        else {
            Rectangle(hdc, point.x - dx, point.y - dy, point.x + dx, point.y + dy);
        }
        DeleteObject(pen);
        if (brush) {
            DeleteObject(brush);
        }
        ReleaseDC(hwnd, hdc);
        return;
    }
    default:
        return;
    }
}

void OnMouseMove(int x, int y)
{
    switch (tool) {
    case TOOLS::PEN:
    {
        if (mouse_down)
        {
            HDC hdc = GetDC(hwnd);
            HPEN pen = CreatePen(PS_SOLID, width, color);
            SelectObject(hdc, pen);
            MoveToEx(hdc, point.x, point.y, NULL);
            LineTo(hdc, point.x = x, point.y = y);
            DeleteObject(pen);
            ReleaseDC(hwnd, hdc);
        }
        return;
    }
    case TOOLS::ERASER:
    {
        if (mouse_down)
        {
            HDC hdc = GetDC(hwnd);
            HPEN pen = CreatePen(PS_SOLID, width, RGB(255, 255, 255));
            SelectObject(hdc, pen);
            MoveToEx(hdc, point.x, point.y, NULL);
            LineTo(hdc, point.x = x, point.y = y);
            DeleteObject(pen);
            ReleaseDC(hwnd, hdc);
        }
        return;
    }
    case TOOLS::ELLIPSE:
    {
        return;
    }
    case TOOLS::RECT:
    {
        return;
    }
    default:
        return;
    }
}

void EnableCustomColor(bool enable) {
    int command1 = SW_HIDE,
        command2 = SW_SHOW;

    if (enable) {
        command1 = SW_SHOW;
        command2 = SW_HIDE;
        SetScrollPos(hRScroll, SB_CTL, GetRValue(color), TRUE);
        SetScrollPos(hGScroll, SB_CTL, GetGValue(color), TRUE);
        SetScrollPos(hBScroll, SB_CTL, GetBValue(color), TRUE);
    }

    //Custom color set
    ShowWindow(hCstmClrT, command1);
    ShowWindow(hRT, command1);
    ShowWindow(hGT, command1);
    ShowWindow(hBT, command1);
    ShowWindow(hRScroll, command1);
    ShowWindow(hGScroll, command1);
    ShowWindow(hBScroll, command1);

    //Menu text
    ShowWindow(hMT, command2);
}