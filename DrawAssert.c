#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"
#include <string.h>

HWND hBtnIgnore;
HWND hBtnIgnoreAll;
HWND hBtnAbort;
HINSTANCE hInst;
char* FileName;
int NumberLine;
int return_value;
char* Message;
int Ign = 0;
ASSERT* tmpAssert;


ASSERT* Temp(ASSERT* MyAssert, BOOL FatalError)
{
	if (Ign == 1 && FatalError == FALSE)
	{
		for (int i = 0; i < MyAssert->CountAssert; i++)
		{
			MyAssert[i].ignore = TRUE;
		}
		return tmpAssert;
	}
	else
	{
		FileName = MyAssert[MyAssert->index].FileName;
		NumberLine = MyAssert[MyAssert->index].NumberLine;
		Message = MyAssert[MyAssert->index].message;
		return_value = MyAssert[MyAssert->index].return_value;
		tmpAssert = MyAssert;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		if (lParam == (LPARAM)hBtnAbort)
		{
			exit(1);
		}
		if (lParam == (LPARAM)hBtnIgnore)
		{
			DestroyWindow(hWnd);
			PostQuitMessage(0);
		}
		if (lParam == (LPARAM)hBtnIgnoreAll)
		{
			Ign = 1;
			Temp(tmpAssert, FALSE);
			DestroyWindow(hWnd);
			PostQuitMessage(0);
		}
		break;
	case WM_CREATE:
		hBtnIgnore = CreateWindow("button", "Игнорировать",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 200, 120, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtnIgnore, SW_SHOWNORMAL);
		hBtnIgnoreAll = CreateWindow("button", "Игнорировать все",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			150, 200, 130, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtnIgnoreAll, SW_SHOWNORMAL);
		hBtnAbort = CreateWindow("button", "Прервать",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			300, 200, 120, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtnAbort, SW_SHOWNORMAL);
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOutA(hdc, 10, 10, "FILE : ", strlen("FILE : "));
		TextOutA(hdc, 50, 10, FileName, strlen(FileName));

		char Num[100];
		_itoa(NumberLine, Num, 100);
		TextOutA(hdc, 10, 30, "LINE : ", strlen("LINE : "));
		TextOutA(hdc, 50, 30, Num, strlen(Num));

		TextOutA(hdc, 10, 50, Message, strlen(Message));
		
		EndPaint(hWnd, &ps);
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinAssert(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	WNDCLASS w;
	HWND As;
	
	w.cbClsExtra = w.cbWndExtra = 0;
	w.style = 0;
	w.lpfnWndProc = WndProc;
	w.hInstance = NULL;
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	w.lpszMenuName = NULL;
	w.lpszClassName = "Assert1";
	RegisterClass(&w);
	As = CreateWindow("Assert1", "ASSERT!!!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 440, 300, NULL, NULL, NULL, NULL);

	if (!As) { return 0; }
	ShowWindow(As, SW_NORMAL);
	UpdateWindow(As);

	Ign = 0;

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProcFatalError(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		if (lParam == (LPARAM)hBtnAbort)
		{
			exit(return_value);
		}
		break;
	case WM_CREATE:
		hBtnAbort = CreateWindow("button", "Прервать",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			300, 200, 120, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtnAbort, SW_SHOWNORMAL);
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOutA(hdc, 10, 10, "FILE : ", strlen("FILE : "));
		TextOutA(hdc, 50, 10, FileName, strlen(FileName));

		char Num[100];
		_itoa(NumberLine, Num, 100);
		TextOutA(hdc, 10, 30, "LINE : ", strlen("LINE : "));
		TextOutA(hdc, 50, 30, Num, strlen(Num));

		TextOutA(hdc, 10, 50, Message, strlen(Message));

		_itoa(return_value, Num, 100);
		TextOutA(hdc, 10, 70, "return ", strlen("return "));
		TextOutA(hdc, 50, 70, Num, strlen(Num));

		EndPaint(hWnd, &ps);
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinFatalError(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	WNDCLASS wc;
	HWND Fe;
	
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProcFatalError;
	wc.hInstance = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "FatalError";
	RegisterClass(&wc);
	Fe = CreateWindow("FatalError", "FatalError!!!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 440, 300, NULL, NULL, NULL, NULL);

	if (!Fe) { return 0; }
	ShowWindow(Fe, SW_NORMAL);
	UpdateWindow(Fe);

	Ign = 0;

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}