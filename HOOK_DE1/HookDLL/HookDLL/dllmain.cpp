// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HHOOK hHook = NULL;
HINSTANCE hinstLib;
bool flag = false;

#define EXPORT __declspec(dllexport)

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	hinstLib = hModule;
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


LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_LBUTTONDOWN:
		{
			if (flag == true)
				return -1;
		}
		default:
			break;
		}
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
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

EXPORT void InitMouseHook(HWND hWnd)
{
	if (hHook != NULL) 
		return;
	hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseHookProc, hinstLib, 0);
	hHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Cài đặt Hook thành công!!", L"Thông báo", MB_OK);
	else
		MessageBox(hWnd, L"Cài đặt Hook không thành công!!", L"Thông báo", MB_OK);
}

EXPORT void UninstallMouseHook(HWND hWnd)
{
	if (hHook == NULL) 
		return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Xóa Hook thành công!!", L"Thông báo", MB_OK);
}