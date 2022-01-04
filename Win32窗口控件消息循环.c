#include<Windows.h>
#include<stdio.h>

HINSTANCE hAppInstance;

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	//printf("%x\n", uMsg);

	switch (uMsg)
	{
	case WM_DESTROY:
	{
		MessageBoxW(hWnd, L"我关闭了", 0, 0);
		//ExitProcess(0);
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
		printf("virtual-key code=0x%x\n", wParam);
		switch (wParam)
		{
		case VK_HOME:
			MessageBoxA(0, "HOME", 0, 0);
			return 0;

		default:
			//MessageBoxA(0, 0, 0, 0);
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	case WM_COMMAND:
		//LOWORD(wParam)为控件的ID，使用CreateWindow()创建控件时的hMenu值
		printf("Control-defined notification code=%d\tControl identifier=%d\n", HIWORD(wParam), LOWORD(wParam));
		switch (LOWORD(wParam))
		{
		case 1001:
			MessageBoxA(0, "按钮被按下", 0, 0);
			return 0;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	//return 0;

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CreateButton(HWND hWnd)
{
	HWND hPushButton = NULL;
	HWND hRadio = NULL;
	HWND hCheckBox = NULL;
	//BS_PUSHBUTTON | BS_DEFPUSHBUTTON
	hPushButton = CreateWindow(L"button", L"按钮", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON, 10, 10, 100, 50, hWnd, (HMENU)1001, hAppInstance, NULL);
	/*
	hPushButton = CreateWindow(
		TEXT("button"),
		TEXT("普通按钮"),
		//WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,						
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
		10, 10,
		80, 20,
		hWnd,
		(HMENU)1001,		//子窗口ID
		hAppInstance,
		NULL);
	*/
	hRadio = CreateWindowExW(0, L"button", L"CheckBox", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX, 10, 70, 100, 50, hWnd, (HMENU)1002, hAppInstance, NULL);
	hCheckBox = CreateWindowExW(0, L"button", L"Radio", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 130, 100, 50, hWnd, (HMENU)1003, hAppInstance, NULL);


}

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPreInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	
	//SetDebugConsole();

	hAppInstance = hInstance;
	//窗口的类名
	WCHAR className[] = L"My First Window";

	// 创建窗口类的对象 
	WNDCLASS wndclass = { 0 };						//一定要先将所有值赋值
	wndclass.hbrBackground = (HBRUSH)COLOR_MENU;						//窗口的背景色
	wndclass.lpfnWndProc = WindowProc;						//窗口过程函数
	wndclass.lpszClassName = className;						//窗口类的名字
	wndclass.hInstance = hInstance;						//定义窗口类的应用程序的实例句柄

	RegisterClass(&wndclass);

	// 创建窗口  
	HWND hwnd = CreateWindow(
		className,				//类名
		TEXT("我的第一个窗口"),				//窗口标题
		WS_OVERLAPPEDWINDOW,				//窗口外观样式 
		10,				//相对于父窗口的X坐标
		10,				//相对于父窗口的Y坐标
		600,				//窗口的宽度  
		300,				//窗口的高度  
		NULL,				//父窗口句柄，为NULL  
		NULL,				//菜单句柄，为NULL  
		hInstance,				//当前应用程序的句柄  
		NULL);				//附加数据一般为NULL

	if (hwnd == NULL)					//是否创建成功  
		return 0;

	CreateButton(hwnd);
	// 显示窗口  
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

/*自写
#include<Windows.h>

HINSTANCE hAppInstance;

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_HOME:
            MessageBoxW(hWnd, L"HOME", NULL, NULL);
            return 0;
        }

    case WM_COMMAND:
        switch (wParam)
        {
        case 1001:
            MessageBoxW(hWnd, L"按钮被按下", 0, 0);
            return 0;
        }

    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CreateButton(HWND hWnd)
{
    HWND hPushButton = NULL;
    HWND hCheckBox = NULL;
    HWND hRadio = NULL;

    hPushButton = CreateWindowExW(0, L"button", L"PushButton", BS_PUSHBUTTON | BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE, 10, 10, 100, 50, hWnd, (HMENU)1001, hAppInstance, NULL);
    hCheckBox = CreateWindowExW(0, L"button", L"CheckBox", BS_AUTOCHECKBOX | BS_CHECKBOX | WS_CHILD | WS_VISIBLE, 10, 70, 100, 50, hWnd, (HMENU)1002, hAppInstance, NULL);
    hRadio = CreateWindowExW(0, L"button", L"Radio", BS_RADIOBUTTON | WS_CHILD | WS_VISIBLE, 10, 130, 100, 50, hWnd, (HMENU)1003, hAppInstance, NULL);

}


int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    hAppInstance = hInstance;

    WCHAR lpszClassName[] = L"MyWndClass";
    WNDCLASS wndclass = { 0 };

    wndclass.lpszClassName = lpszClassName;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)COLOR_MENU;
    wndclass.lpfnWndProc = WndProc;

    RegisterClass(&wndclass);

    HWND hWnd = CreateWindow(lpszClassName, L"测试", WS_OVERLAPPEDWINDOW, 100, 100, 600, 300, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        return 0;
    }

    CreateButton(hWnd);

    ShowWindow(hWnd, SW_SHOW);

    MSG msg = { 0 };
    while (GetMessage(&msg, 0, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;

}
*/