
//-------------------------------------------------------------------
//	ShowSort
//	main.cpp
//	建立窗体、以及接收键盘事件
//-------------------------------------------------------------------

#include"ShowSort.h"



char WINDOWS_NAME[30] = "ShowSort";
BYTE buffer[SCREEN_WIDTH*SCREEN_HEIGHT*bits / 8];
static HDC screen_hdc;
static HWND screen_hwnd;
static HDC hCompatibleDC;	//兼容HDC
static HBITMAP hCompatibleBitmap; //兼容BITMAP
static HBITMAP hOldBitmap;	//旧的BITMAP
static BITMAPINFO binfo;	//BITMAPINFO结构体
const int SCREEN_TOP = 50;
const int SCREEN_LEFT = 100;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrivInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitData();

	WNDCLASSEX wndClass = { 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszClassName = "wndClass";
	wndClass.lpszMenuName = 0;
	wndClass.lpfnWndProc = WndProc;			//window过程函数的名字 可以随便改

	//注册窗体
	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}
	//创建窗体
	HWND hWnd = CreateWindow("wndClass",
		WINDOWS_NAME,
		WS_OVERLAPPEDWINDOW,
		SCREEN_LEFT,
		SCREEN_TOP,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//显示窗体 然后 更新
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = 24;
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = SCREEN_WIDTH;

	//获取屏幕HDC
	screen_hwnd = hWnd;
	screen_hdc = GetDC(screen_hwnd);

	//获取兼容HDC 和兼容Bitmap，兼容Bitmap选入兼容HDC
	hCompatibleDC = CreateCompatibleDC(screen_hdc);
	hCompatibleBitmap = CreateCompatibleBitmap(screen_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hCompatibleBitmap);

	int frames = 0;
	Draw();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		Sort();
		if (PeekMessage(&msg,
			0,
			0,
			0,
			PM_REMOVE)
			)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	UnregisterClass("wndClass", hInstance);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_ESCAPE:
			exit(0);
		case VK_UP:
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
	return 0;
}

void PutBufferToScreen()
{
	SetDIBits(screen_hdc, hCompatibleBitmap, 0, SCREEN_HEIGHT, buffer, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);
	BitBlt(screen_hdc, -1, -1, SCREEN_WIDTH, SCREEN_HEIGHT, hCompatibleDC, 0, 0, SRCCOPY);
}

