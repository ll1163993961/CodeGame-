// CodeGame.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CodeGame.h"
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//定义用户变量
int i, j, cahrnum, userscore=0;
int speed = 2;
int oldscore = 0;
RECT lprc;
HBRUSH hbr;
WCHAR szbuffer[100];
WCHAR scorebuffer[100];
HBITMAP hbitmap;


//定义用户函数
void drawbgimg(HINSTANCE hInst, HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HDC mdc = CreateCompatibleDC(hdc); // 创建兼容的缓存DC对象
	hbitmap = (HBITMAP)LoadImage(
		hInst,   // handle of the instance containing the image
		L"bgimg.bmp",  // name or identifier of image
		IMAGE_BITMAP,        // type of image
		450,     // desired width
		450,     // desired height
		LR_LOADFROMFILE        // load flags
	);
	SelectObject(mdc, hbitmap);
	BitBlt(hdc, 0, 0, 450, 450, mdc, 0, 0, SRCCOPY);
	DeleteObject(hbitmap);
	DeleteDC(mdc);
	ReleaseDC(hWnd, hdc);
}
void GameInit(HWND hWnd)
{
	i = 0;
	j = rand() % 420+10;
	cahrnum = rand() % 25 + 97;
	lprc = { j,i,50,i + 30 };
	hbr = CreateSolidBrush(RGB(255, 255, 255));
	/*HDC hdc = GetDC(hWnd);

	Rectangle(hdc, 0, 0, 500, 500);
	ReleaseDC(hWnd, hdc);*/
	drawbgimg(hInst, hWnd);

}
void GameShow(HWND hWnd)
{
	

	//if (userscore > 10 && userscore < 30) { speed += 0.5; }
	if ((userscore - oldscore) == 10)
	{
		speed += 1;
		oldscore = userscore;
	}
	HDC hdc = GetDC(hWnd);
	
	/*Rectangle(hdc, 0, 0, 500, 500);*/
	drawbgimg(hInst, hWnd);
	ReleaseDC(hWnd, hdc);
}
void GameWithPlayer(HWND hWnd)
{
	
}
void GameWithOutPlayer(HWND hWnd)
{
	
	HDC hdc = GetDC(hWnd);
	
	i = i+10*speed;
	if (i > 450) 
	{ 
		i = 0;
		userscore = -2;
	}
	wsprintf(szbuffer, L"%c", cahrnum);
	TextOut(hdc, j, i, szbuffer, lstrlen(szbuffer));
	wsprintf(scorebuffer, L"得分:%d", userscore);
	TextOut(hdc, 350, 10, scorebuffer, lstrlen(scorebuffer));
	if (userscore > 10)
	{
		if (userscore > 50)
		{
			TextOut(hdc, 320, 30, L"你已经超神了!", lstrlen(L"你已经超神了!"));
			return;
		}
		TextOut(hdc, 320,30, L"你真棒!加油", lstrlen(L"你真棒!加油"));
		
	}
	
	ReleaseDC(hWnd, hdc);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。
	srand((int)time);
	


    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CODEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CODEGAME));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CODEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      500, 150,450,450, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	
    switch (message)
    {
    case WM_COMMAND:
        
        break;
	case WM_CREATE:
		SetTimer(hWnd, 5000, 500, NULL);
		GameInit(hWnd);
		PlaySound(L"bgm.wav", NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			//Rectangle(hdc, 10, 10, 50, 50);
			
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
	{
		if (userscore < 0)
		{
			KillTimer(hWnd, 5000);
			if (IDOK == MessageBox(hWnd, L"游戏失败!是否继续", L"温馨提示", 1))
			{
				userscore = 0;
				SetTimer(hWnd, 5000, 500, NULL);
			}
			else
			{
				PostQuitMessage(1);
			}
			//游戏失败
		}
		GameShow(hWnd);
		GameWithOutPlayer(hWnd);
		
	}
		
		break;
	case WM_CHAR:
	{
		if (wParam == szbuffer[0])
		{
			GameInit(hWnd);
			userscore++;
		}
		break;
	}
		
		
		
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

