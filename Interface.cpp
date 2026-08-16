#ifndef UNICODE
#define UNICODE
#endif 
#define IDC_PTB2_BUTTON 1001
#define IDC_BTN_Logistica 1000

#include <windows.h>
#include<iostream>
#include "Producao.h"

HBITMAP hBackground = NULL;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Sidebarproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetClientRect(hwnd, &rect);

            HBRUSH brush = CreateSolidBrush(RGB(30, 40, 50));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);

            EndPaint(hwnd, &ps);
		
        }
        return 0;

        case WM_CREATE:
        {
            CreateWindowEx(
                0,
                L"BUTTON",
                L"Produção",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                50,
                200,
                30,
                hwnd,
                (HMENU)IDC_PTB2_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
			
			CreateWindowEx(
			 0,
			 L"BUTTON",
			 L"Logistica",
			 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			 20,
			 95,
			 200,
			 30,
			 hwnd,
			 (HMENU)IDC_BTN_Logistica,
			 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
			 NULL
			 );
			 
			 return 0;
			 
		}
		
			 case WM_COMMAND:
			    switch(LOWORD(wParam)){
				   
				   case IDC_PTB2_BUTTON:

                 MessageBox(
                  NULL,
                 L".......Entrando.......",
                 L"DEBUG",
                 MB_OK
               );

                  AbrirProducao(
                  (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE)
               );

             break;
					
					case IDC_BTN_Logistica:
					 MessageBox(
                     hwnd,
                    L"Entrando na Logistica :) !",
                    L"Logística",
                    MB_OK
                    );
					 break;
				}

            return 0;	
        }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	
	

	RegistrarProducao(hInstance);
	
  hBackground = (HBITMAP)LoadImage(
    NULL,
    L"Imagem.bmp",
    IMAGE_BITMAP,
    0,
    0,
    LR_LOADFROMFILE
);

	
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);
	
	 const wchar_t SIDEBAR_CLASS[] = L"Side Bar";
	
	 WNDCLASS sidebarclass ={};
	 sidebarclass.lpfnWndProc = Sidebarproc;
	 sidebarclass.hInstance = hInstance;
	 sidebarclass.lpszClassName = SIDEBAR_CLASS;
	 sidebarclass.hbrBackground = CreateSolidBrush(RGB(35, 35, 35));
     
	 
	 RegisterClass(&sidebarclass); 
	 
	
	
	

    // Create the window.

    HWND hwnd = CreateWindowEx(
    0,
    CLASS_NAME,
    L"Gerenciador Industrial",
    WS_OVERLAPPEDWINDOW,

    CW_USEDEFAULT, CW_USEDEFAULT,
    860, 600,

    NULL,
    NULL,
    hInstance,
    NULL
    );
		
		
		HWND sidebar = CreateWindowEx(
      0,
      SIDEBAR_CLASS,
      L"",
      WS_CHILD | WS_VISIBLE,
      0,          // X
      0,          // Y
      250,        // largura
      1000,        // altura
      hwnd,       // janela PAI
      NULL,
      hInstance,
      NULL
     );//

    if (hwnd == NULL)
    {
        return 0;
    }
	
	

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
 

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);

    HDC memDC = CreateCompatibleDC(hdc);

    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBackground);

    BITMAP bitmap;
    GetObject(hBackground, sizeof(BITMAP), &bitmap);

    StretchBlt(
        hdc,
        0,
        0,
        rect.right,
        rect.bottom,
        memDC,
        0,
        0,
        bitmap.bmWidth,
        bitmap.bmHeight,
        SRCCOPY
    );

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);

    EndPaint(hwnd, &ps);
}
break;
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
