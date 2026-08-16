#include <iostream>
#include <windows.h>

#define IDC_PTB1_BUTTON 1001
#define IDC_PTB2_BUTTON 1002
#define IDC_PTB3_BUTTON 1003
#define IDC_PTB4_BUTTON 1004
#define IDC_PTB5_BUTTON 1005

const wchar_t PRODUCTION_CLASS[] = L"Janela da produção";


LRESULT CALLBACK ProdProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);


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

        // Se já estiver registrada, não é necessariamente um problema.
        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass falhou!",
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
		
		case WM_CREATE:
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
	
             case WM_COMMAND:{
				 
			 }
			      
	
			return 0;
    }
	
	  

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
