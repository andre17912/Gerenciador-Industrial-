#include <iostream>
#include <windows.h>

#include "Janelas.h"
#include "Apontamento.h" 
#include "Ordens.h"
#include "Material.h"

#define IDC_PTB1_BUTTON 1001
#define IDC_PTB2_BUTTON 1002
#define IDC_PTB3_BUTTON 1020
#define IDC_PTB4_BUTTON 1004
#define IDC_PTB5_BUTTON 1005
#define APOINTMENT_CLASS L"APONTAMENTOCLASS"
#define ORDENS_CLASS L"ORDENS_CLASS"
#define MATERIAL_CLASS L"MATERIAL_CLASS"

const wchar_t PRODUCTION_CLASS[] = L"Janela da produção";


LRESULT CALLBACK ProdProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

LRESULT CALLBACK ApontamentoProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

bool RegistrarApontamento(HINSTANCE hInstance)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc   = ApontamentoProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"APONTAMENTOCLASS";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (RegisterClass(&wc) == 0)
    {
        DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass da janela Apontamento falhou!",
            L"Erro",
            MB_OK | MB_ICONERROR
        );

        return false;
    }

    return true;
}

LRESULT CALLBACK MaterialProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK ApontamentoProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK OrdensProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


bool RegistraMaterial(HINSTANCE hInstance)
{
    WNDCLASS wMaterial = {};

    wMaterial.lpfnWndProc   = MaterialProc;
    wMaterial.hInstance     = hInstance;
    wMaterial.lpszClassName = MATERIAL_CLASS;
    wMaterial.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClass(&wMaterial) == 0)
    {
        DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass dos Materiais falhou!",
            L"Erro",
            MB_OK
        );

        return false;
    }

    return true;
}


bool RegistraOrdens(HINSTANCE hInstance)
{
    WNDCLASS wOrdens = {};

    wOrdens.lpfnWndProc = OrdensProc;
    wOrdens.hInstance = hInstance;
    wOrdens.lpszClassName = ORDENS_CLASS;
    wOrdens.hCursor = LoadCursor(NULL, IDC_ARROW);

if (RegisterClass(&wOrdens) == 0)
    {
        DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass da janela Ordens falhou!",
            L"Erro",
            MB_OK
        );

        return false;
    }

    return true;
}

// REGISTRA A CLASSE
bool RegistrarProducao(HINSTANCE hInstance)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc   = ProdProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = PRODUCTION_CLASS;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClass(&wc) == 0)
    {
        DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass da Produção falhou!",
            L"Erro",
            MB_OK
        );

        return false;
    }

    return true;
}

// ABRE A JANELA
void AbrirProducao(HINSTANCE hInstance)
{
    HWND hwnd = CreateWindowEx(
        0,
        PRODUCTION_CLASS,
        L"Gerenciador Industrial - Produção",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT,
        CW_USEDEFAULT,

        860,
        600,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        DWORD erro = GetLastError();

        wchar_t mensagem[256];

        wsprintf(
            mensagem,
            L"CreateWindowEx falhou!\n\nCódigo do erro: %lu",
            erro
        );

        MessageBox(
            NULL,
            mensagem,
            L"Erro",
            MB_OK
        );

        return;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}


// PROCEDIMENTO DA JANELA
LRESULT CALLBACK ProdProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)	

{
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetClientRect(hwnd, &rect);

            // Futuramente você desenha a interface aqui.

            EndPaint(hwnd, &ps);

            return 0;
        }

        case WM_DESTROY:
		{
            return 0;
		}
		
		case WM_CREATE: {
	      CreateWindowEx(
                0,
                L"BUTTON",
                L"Apontamento",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                45,
                200,
                30,
                hwnd,
                (HMENU)IDC_PTB1_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
			
			CreateWindowEx(
                0,
                L"BUTTON",
                L"Ordens de Produção",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                100,
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
                L"Empenho De Materia Prima",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                150,
                200,
                30,
                hwnd,
                (HMENU)IDC_PTB3_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
			
			CreateWindowEx(
                0,
                L"BUTTON",
                L"Remover Material",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                200,
                200,
                30,
                hwnd,
                (HMENU)IDC_PTB4_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
			
			CreateWindowEx(
                0,
                L"BUTTON",
                L"Consultar Sistema",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,
                250,
                200,
                30,
                hwnd,
                (HMENU)IDC_PTB5_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
			
			 return 0;
	}
             case WM_COMMAND :{
				 
				 switch(LOWORD(wParam)){
					 
					case IDC_PTB1_BUTTON:
                {
                    HINSTANCE hInstance =
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

                    HWND hwndApontamento = CreateWindowEx(
                        0,
                        APOINTMENT_CLASS,
                        L"APONTAMENTO - Produção",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        860,
                        600,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
						
                    );

                    if (hwndApontamento == NULL)
                    {
                        DWORD erro = GetLastError();

                        wchar_t mensagem[256];

                        wsprintf(
                            mensagem,
                            L"CreateWindowEx falhou!\n\n"
                            L"Código do erro: %lu",
                            erro
                        );

                        MessageBox(
                            NULL,
                            mensagem,
                            L"Erro",
                            MB_OK | MB_ICONERROR
                        );

                        return 0;
                    }

                    ShowWindow(hwndApontamento, SW_SHOW);
                    UpdateWindow(hwndApontamento);

                    break;
                }
				 
				 
				 case IDC_PTB2_BUTTON:
				 {
				        HINSTANCE hInstance =
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

                    HWND hwndOrdens = CreateWindowEx(
                        0,
                        ORDENS_CLASS,
                        L"ORDENS_CLASS",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        860,
                        600,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
						
                    );

                    if (hwndOrdens == NULL)
                    {
                        DWORD erro = GetLastError();

                        wchar_t mensagem[256];

                        wsprintf(
                            mensagem,
                            L"CreateWindowEx falhou!\n\n"
                            L"Código do erro: %lu",
                            erro
                        );

                        MessageBox(
                            NULL,
                            mensagem,
                            L"Erro",
                            MB_OK | MB_ICONERROR
                        );
					    
						ShowWindow(hwndOrdens, SW_SHOW);
                         UpdateWindow(hwndOrdens);
				

						
						
					}
					     ShowWindow(hwndOrdens, SW_SHOW);
                         UpdateWindow(hwndOrdens);
					break;
				 }
				 case IDC_PTB3_BUTTON:
				 { 
						HINSTANCE hInstance =
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

                    HWND hwndMaterial = CreateWindowEx(
                        0,
                        MATERIAL_CLASS,
                        L"MATERIAL_CLASS",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        860,
                        600,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
						
                    );

                    if (hwndMaterial == NULL)
                    {
                        DWORD erro = GetLastError();

                        wchar_t mensagem[256];

                        wsprintf(
                            mensagem,
                            L"CreateWindowEx falhou!\n\n"
                            L"Código do erro: %lu",
                            erro
                        );

                        MessageBox(
                            NULL,
                            mensagem,
                            L"Erro",
                            MB_OK | MB_ICONERROR
                        );			
						
					}
					 
					 	 ShowWindow(hwndMaterial, SW_SHOW);
                         UpdateWindow(hwndMaterial);
					 
					 break;
				 }
				 /*
				 case IDC_PTB4_BUTTON:
					    Removedor((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE));
						break;
						
						case IDC_PTB5_BUTTON:
					    Consultas((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE));
						break; 
						
						return 0;
						*/   
				
			 }
			     
			     return 0;
			 }	
    }
	
	
	
	  

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
