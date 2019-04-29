// CodeGame.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CodeGame.h"
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//�����û�����
int i, j, cahrnum, userscore=0;
int speed = 2;
int oldscore = 0;
RECT lprc;
HBRUSH hbr;
WCHAR szbuffer[100];
WCHAR scorebuffer[100];
HBITMAP hbitmap;


//�����û�����
void drawbgimg(HINSTANCE hInst, HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HDC mdc = CreateCompatibleDC(hdc); // �������ݵĻ���DC����
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
	wsprintf(scorebuffer, L"�÷�:%d", userscore);
	TextOut(hdc, 350, 10, scorebuffer, lstrlen(scorebuffer));
	if (userscore > 10)
	{
		if (userscore > 50)
		{
			TextOut(hdc, 320, 30, L"���Ѿ�������!", lstrlen(L"���Ѿ�������!"));
			return;
		}
		TextOut(hdc, 320,30, L"�����!����", lstrlen(L"�����!����"));
		
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

    // TODO: �ڴ˷��ô��롣
	srand((int)time);
	


    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CODEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CODEGAME));

    MSG msg;

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
			//Rectangle(hdc, 10, 10, 50, 50);
			
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
	{
		if (userscore < 0)
		{
			KillTimer(hWnd, 5000);
			if (IDOK == MessageBox(hWnd, L"��Ϸʧ��!�Ƿ����", L"��ܰ��ʾ", 1))
			{
				userscore = 0;
				SetTimer(hWnd, 5000, 500, NULL);
			}
			else
			{
				PostQuitMessage(1);
			}
			//��Ϸʧ��
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

