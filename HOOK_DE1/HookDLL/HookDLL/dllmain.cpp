// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HWND hWnd;
HHOOK hMyHook1;
HHOOK hMyHook2;
HINSTANCE hInstance;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	hInstance = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

INT InitMouseHook(HWND hwndYourWindow)
{
	hWnd = hwndYourWindow;
	hMyHook1 = SetWindowsHookEx(WH_MOUSE, MouseProc, hInstance, 0);
	hMyHook2 = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, hInstance, 0);
	if (hMyHook1 != NULL && hMyHook2 != NULL)
	{
		return 1;
	}
	return 0;
}
bool flag = false;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
			case WM_LBUTTONDOWN:
			{
				if (flag == true)
					return -1;
				else
					return 0;
			}
			default:
				break;
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

INT UninstallMouseHook()
{
	if (hMyHook1 != NULL && hMyHook2 != NULL)
	{
		flag = false;
		UnhookWindowsHookEx(hMyHook1);
		UnhookWindowsHookEx(hMyHook2);
	}
	return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		if (wParam == 13)
			flag = true;
		else if (wParam == 17)
			flag = false;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

