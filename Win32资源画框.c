#include<Windows.h>
#include"resource.h"

BOOL Login(LPWSTR lpszUsername,LPWSTR lpszPassword)
{
	if (!wcscmp(lpszUsername,L"admin"))
	{
		if (!wcscmp(lpszPassword, L"123456"))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;

}

BOOL CALLBACK DialogProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	HWND hUsername = NULL;
	HWND hPassword = NULL;
	WCHAR Username[20] = { 0 };
	WCHAR Password[20] = { 0 };

	switch (uMsg)
	{

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_LOGIN:
			//MessageBoxW(hWnd, L"Logging...", L"Message", 0);

			hUsername = GetDlgItem(hWnd, IDC_EDIT_USERNAME);
			hPassword = GetDlgItem(hWnd, IDC_EDIT_PASSWORD);
			GetWindowTextW(hUsername, Username, sizeof(Username) / 2 - 1);
			GetWindowTextW(hPassword, Password, sizeof(Password) / 2 - 1);

			if (Login(Username,Password))
			{
				MessageBoxW(hWnd, L"Login Success", L"Message", 0);
				return TRUE;
			}
			else
			{
				MessageBoxW(hWnd, L"Login Fail", L"Message", 0);
				return TRUE;
			}
			return TRUE;	//自己处理完是TRUE
		case IDC_BUTTON_REGISTER:
			MessageBoxW(hWnd, L"Cannot Register", L"Message", MB_OK);
			return TRUE;
		}

	}
	return FALSE;
}

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPreInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);

	return 0;
}


////////////////////////////
/*
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ 生成的包含文件。
// 供 Win32StudyDT.rc 使用
//
#define IDD_DIALOG_MAIN                 101
#define IDC_BUTTON_LOGIN                1001
#define IDC_BUTTON_REGISTER             1002
#define IDC_EDIT_USERNAME               1003
#define IDC_EDIT_PASSWORD               1004

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        103
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1004
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
*/