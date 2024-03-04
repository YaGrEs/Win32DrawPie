// WindowsProject1.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <gdiplus.h>
#include <wingdi.h>
#include <cwchar>
#include <tchar.h>
#include <strsafe.h>
#include <cmath>
#include <string>
#include <sstream>

#include "resource.h"
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

WCHAR* buf = new WCHAR[50];
WCHAR* buf2 = new WCHAR[50];
WCHAR* buf3 = new WCHAR[50];
WCHAR* buf4 = new WCHAR[50];
WCHAR* buf5 = new WCHAR[50];
WCHAR* buf6 = new WCHAR[50];
WCHAR* buf7 = new WCHAR[50];
WCHAR* buf8 = new WCHAR[50];

int counts[4] = {-1, -1, -1, -1};

double percent(int curr) {
	int sum = counts[0] + counts[1] + counts[2] + counts[3];
	double rct = ((100.0 * curr) / sum);
	return rct;
}
int mathematic(int curr) {
	int sum = counts[0] + counts[1] + counts[2] + counts[3];
	int rct = ((360 * curr) / sum);
	return rct;
}
BOOL check(WCHAR* a){
	int r = 0;
	for (int i = 0; i < wcslen(a); i++) {
		char c = a[i];
		if (((int)c < 48) && ((int)c > 57)) {
			r = 1;
			break;
		}
	}
	if (r == 1) return FALSE;
	else return TRUE;
}
VOID OnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen      pen(Color(100, 0, 0, 0));
	RectF ellipseRect(100, 100, 100, 100);
	REAL start = 0.0f;
	for (int i = 0; i < 4; i++) {
		SolidBrush solidBrush(Color(100, std::rand() % 255, std::rand() % 255, std::rand() % 255));
		graphics.DrawPie(&pen, ellipseRect, start, mathematic(counts[i]));
		graphics.FillPie(&solidBrush, ellipseRect, start, mathematic(counts[i]));
		start = mathematic(counts[i]) + start;
	}
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	HWND hMainWnd;
	HWND hwndButton;
	HWND hwndEdit;
	HWND hwndEditBig;
	MSG msg;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_HELP);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MyClass";
	wc.hIconSm = LoadIcon(NULL, IDI_ERROR);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Cannot register class", L"Error", MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(L"MyClass", L"Draw pie", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_OVERLAPPEDWINDOW) & ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX), 0, 0, 640, 480, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, NULL);
	if (!hMainWnd) {
		MessageBox(NULL, L"Cannot create main window", L"Error", MB_OK);
		return 0;
	}
	hwndButton = CreateWindow(L"BUTTON",  L"OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 252, 300, 100, 100, hMainWnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(hMainWnd, GWLP_HINSTANCE), NULL);
	int ID1 = 2;
	int ID2 = 6;
	int y = 50;
	for (int i = 0; i < 4; i++) {
		hwndEditBig = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 200, y, 100, 30, hMainWnd, (HMENU)ID1, (HINSTANCE)GetWindowLongPtr(hMainWnd, GWLP_HINSTANCE), NULL);
		hwndEdit = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 350, y, 40, 30, hMainWnd, (HMENU)ID2, (HINSTANCE)GetWindowLongPtr(hMainWnd, GWLP_HINSTANCE), NULL);
		ID1++;
		ID2++;
		y += 50;
	}
	ShowWindow(hMainWnd, nCmdShow);
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE h;
	h = GetModuleHandle(NULL);
	HICON hIcon;
	HICON sm;
	switch (uMsg)
	{
	case WM_CREATE:
		hIcon = LoadIcon(h, MAKEINTRESOURCE(IDI_ICON1));
		sm = (HICON)LoadImage(h, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		SetClassLongPtr(hWnd, GCLP_HICON, (LONG_PTR)hIcon);
		SetClassLongPtr(hWnd, GCLP_HICONSM, (LONG_PTR)sm);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (wParam == 1) {
			GetDlgItemText(hWnd, 2, buf, 50);
			GetDlgItemText(hWnd, 3, buf2, 50);
			GetDlgItemText(hWnd, 4, buf3, 50);
			GetDlgItemText(hWnd, 5, buf4, 50);
			GetDlgItemText(hWnd, 6, buf5, 50);
			GetDlgItemText(hWnd, 7, buf6, 50);
			GetDlgItemText(hWnd, 8, buf7, 50);
			GetDlgItemText(hWnd, 9, buf8, 50);
			if (check(buf5) == FALSE || check(buf6) == FALSE || check(buf7) == FALSE || check(buf8) == FALSE) {
				MessageBox(NULL, L"DONT TYPE TEXT IN NUMBER FIELDS", L"Error", MB_OK);
				delete buf5;
				delete buf6;
				delete buf7;
				delete buf8;
				buf5 = new WCHAR[50];
				buf6 = new WCHAR[50];
				buf7 = new WCHAR[50];
				buf8 = new WCHAR[50];
			}
			else {
				counts[0] = _wtoi(buf5);
				counts[1] = _wtoi(buf6);
				counts[2] = _wtoi(buf7);
				counts[3] = _wtoi(buf8);
				DialogBox(h, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc);
			}
		}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	HDC hd;
	PAINTSTRUCT p;
	RECT rct;
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
		}
		break;
	case WM_PAINT:
		std::wstringstream ss;
		ss << percent(counts[0]);
		wcscat(buf, L" ");
		wcscat(buf, ss.str().c_str());
		wcscat(buf, L"%");
		ss << percent(counts[0]);
		SetDlgItemText(hDlg, IDC_STATIC1, buf);
		std::wstringstream ss2;
		ss2 << percent(counts[1]);
		wcscat(buf2, L" ");
		wcscat(buf2, ss2.str().c_str());
		wcscat(buf2, L"%");
		SetDlgItemText(hDlg, IDC_STATIC2, buf2);
		std::wstringstream ss3;
		ss3 << percent(counts[2]);
		wcscat(buf3, L" ");
		wcscat(buf3, ss3.str().c_str());
		wcscat(buf3, L"%");
		SetDlgItemText(hDlg, IDC_STATIC3, buf3);
		std::wstringstream ss4;
		ss4 << percent(counts[3]);
		wcscat(buf4, L" ");
		wcscat(buf4, ss4.str().c_str());
		wcscat(buf4, L"%");
		SetDlgItemText(hDlg, IDC_STATIC4, buf4);
		hd = BeginPaint(hDlg, &p);
		GetClientRect(hDlg, &rct);
		OnPaint(hd);
	}
	return FALSE;
}