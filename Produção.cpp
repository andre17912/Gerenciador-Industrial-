#include <iostream>
#include <windows.h>

#include "Janelas.h"
#include "Apontamento.h" 
#include "Ordens.h"
#include "Material.h"
#define IDC_LABEL_EDIT 1010
#define IDC_LABEL_CODIGO 1006
#define IDC_EDIT_CODIGO  1005
#define IDC_PTB1_BUTTON 1001
#define IDC_PTB2_BUTTON 1002
#define IDC_PTB3_BUTTON 1020
#define IDC_PTB4_BUTTON 1004
#define IDC_PTB5_BUTTON 1005
#define APOINTMENT_CLASS L"APONTAMENTOCLASS"
#define ORDENS_CLASS L"ORDENS_CLASS"
#define MATERIAL_CLASS L"MATERIAL_CLASS"
#define REMOVECLASS    L"REMOVECLASS"
#define CONCLASS       L"CONCLASS"


const wchar_t PRODUCTION_CLASS[] = L"Janela da produção";


LRESULT CALLBACK ConsulProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

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


LRESULT CALLBACK RemoveProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);




bool Consul(HINSTANCE hInstance){
	
	WNDCLASS cs ={ };
	
	cs.lpfnWndProc = RemoveProc;
	cs.hInstance   = hInstance;
	cs.lpszClassName = L"CONCLASS";
	cs.hCursor       = LoadCursor(NULL, IDC_ARROW);
	cs.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	if(RegisterClass(&cs) == 0){
		DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass da janela Remover falhou!",
            L"Erro",
            MB_OK | MB_ICONERROR
        );

        return false;
    
	}
	
	return true;
}

bool RemoveMaterial(HINSTANCE hInstance){
	
	WNDCLASS rm ={ };
	
	rm.lpfnWndProc = RemoveProc;
	rm.hInstance   = hInstance;
	rm.lpszClassName = L"REMOVECLASS";
	rm.hCursor       = LoadCursor(NULL, IDC_ARROW);
	rm.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	if(RegisterClass(&rm) == 0){
		DWORD erro = GetLastError();

        if (erro == ERROR_CLASS_ALREADY_EXISTS)
        {
            return true;
        }

        MessageBox(
            NULL,
            L"RegisterClass da janela Remover falhou!",
            L"Erro",
            MB_OK | MB_ICONERROR
        );

        return false;
    
	}
	
	return true;
}


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

LRESULT CALLBACK ConsulProc(
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



LRESULT CALLBACK RemoveProc(
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
        case WM_CREATE:
        {
            // ==================== LABELS (TEXTOS ESTÁTICOS) ====================
            
            // Labels para exibição de informações (não editáveis)
            struct LabelInfo {
                int x, y;
                int width;      // Adicionando largura personalizada
                const wchar_t* text;
            };
            
            LabelInfo labels[] = {
                {20, 75, 180, L"Código do Produto:"},
                {20, 105, 180, L"Ordem de Produção:"},
                {20, 135, 180, L"Máquina:"},
                {20, 175, 180, L"Quantidade:"},           // Aumentei a largura
                {20, 205, 180, L"Quantidade Produzida:"}  // Aumentei a largura
            };
            
            // Criar todos os labels estáticos
            for (int i = 0; i < 5; i++) {
                HWND hLabel = CreateWindowEx(
                    0,
                    L"STATIC",
                    labels[i].text,
                    WS_VISIBLE | WS_CHILD | SS_RIGHT,
                    labels[i].x,
                    labels[i].y,
                    labels[i].width,  // Usando largura personalizada
                    25,
                    hwnd,
                    (HMENU)IDC_LABEL_EDIT,
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL
                );
                
                if (!hLabel) return -1;
            }
            
            // ==================== VALORES EXIBIDOS (NÃO EDITÁVEIS) ====================
            
            // Exibir valores (como se fossem "readonly") - sem borda, apenas texto
            struct ValueInfo {
                int x, y;
                int width;
                const wchar_t* text;
            };
            
            ValueInfo values[] = {
                {210, 75, 300, L".........."},        // Código do Produto
                {210, 105, 300, L"....."},            // Ordem de Produção
                {210, 135, 300, L"Máquina 03"},       // Máquina
                {210, 175, 300, L"0"},                // Quantidade
                {210, 205, 300, L"0"}                 // Quantidade Produzida
            };
            
            // Criar labels para exibir os valores (estilo mais clean, sem borda)
            for (int i = 0; i < 5; i++) {
                HWND hValue = CreateWindowEx(
                    0,
                    L"STATIC",
                    values[i].text,
                    WS_VISIBLE | WS_CHILD | SS_LEFT,
                    values[i].x,
                    values[i].y,
                    values[i].width,  // Usando largura personalizada
                    25,
                    hwnd,
                    (HMENU)IDC_LABEL_EDIT,
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL
                );
                
                if (!hValue) return -1;
            }
            
            // ==================== BARRA DE CÓDIGO DE BARRAS (EDIT) ====================
            
            // Criar campo EDIT para código de barras (bem acima do botão)
            HWND hEditCodigoBarras = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                L"EDIT",
                L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                300,
                350,
                300,  // Aumentei a largura
                35,
                hwnd,
                (HMENU)IDC_LABEL_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            
            if (!hEditCodigoBarras) return -1;
            
            // Adicionar um label indicando o campo de código de barras
            HWND hLabelCodigoBarras = CreateWindowEx(
                0,
                L"STATIC",
                L"Código de Barras:",
                WS_VISIBLE | WS_CHILD | SS_RIGHT,
                150,
                355,
                140,
                25,
                hwnd,
                (HMENU)IDC_LABEL_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            
            if (!hLabelCodigoBarras) return -1;
            
            // ==================== BOTÃO APONTAR ====================
            
            // Criar botão "Apontar" com estilo moderno
            HWND hButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"Apontar Produção",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_FLAT,
                300,
                420,
                300,  // Aumentei a largura
                45,
                hwnd,
                (HMENU)IDC_LABEL_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            
            if (!hButton) return -1;
            
            // ==================== COMBOBOX MÁQUINA ====================
            
            HWND hCombo = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                L"COMBOBOX",
                L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                210,  // Ajustei para alinhar com os valores
                130,
                300,  // Aumentei a largura
                100,
                hwnd,
                (HMENU)IDC_LABEL_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            
            if (hCombo) {
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Máquina 01");
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Máquina 02");
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Máquina 03");
                SendMessage(hCombo, CB_SETCURSEL, 2, 0);
            }
            
            return 0;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        
        case WM_CTLCOLORSTATIC:
        {
            // Customizar cores para um visual mais moderno
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
        }
        
        case WM_COMMAND:
        {
            WORD wmId = LOWORD(wParam);
            WORD wmEvent = HIWORD(wParam);
            
            if (wmId == IDC_LABEL_EDIT && wmEvent == BN_CLICKED)
            {
                // Verificar se é o botão
                HWND hCtrl = (HWND)lParam;
                wchar_t className[256];
                GetClassName(hCtrl, className, 256);
                
                if (wcscmp(className, L"BUTTON") == 0)
                {
                    // Botão "Apontar" foi clicado
                    
                    // Obter o código de barras digitado
                    HWND hEditBarras = GetDlgItem(hwnd, IDC_LABEL_EDIT);
                    
                    if (hEditBarras) {
                        wchar_t buffer[256];
                        GetWindowText(hEditBarras, buffer, 256);
                        
                        // Validar se o código de barras foi digitado
                        if (wcslen(buffer) == 0) {
                            MessageBox(hwnd, 
                                L"Por favor, digite ou leia o código de barras.",
                                L"Campo Obrigatório",
                                MB_OK | MB_ICONINFORMATION);
                            SetFocus(hEditBarras);
                            return 0;
                        }
                        
                        // Processar o apontamento
                        wchar_t mensagem[512];
                        wsprintf(mensagem, 
                            L"Produção apontada com sucesso!\nCódigo: %s", 
                            buffer);
                            
                        MessageBox(hwnd, 
                            mensagem,
                            L"Sucesso",
                            MB_OK | MB_ICONINFORMATION);
                    }
                }
            }
            break;
        }
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
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,

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
                        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
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
                       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
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
				 
				 case IDC_PTB4_BUTTON:
				 {
					    HINSTANCE hInstance =
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

                    HWND hwndRemover = CreateWindowEx(
                        0,
                        ORDENS_CLASS,
                        L"REMOVECLASS",
                      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        860,
                        600,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
						
                    );

                    if (hwndRemover == NULL)
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
						ShowWindow(hwndRemover, SW_SHOW);
                         UpdateWindow(hwndRemover);
				
						break;
				 }
						case IDC_PTB5_BUTTON:{
							
							HINSTANCE hInstance =
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

                    HWND hwndCon = CreateWindowEx(
                        0,
                        ORDENS_CLASS,
                        L"CONCLASS",
                       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        860,
                        600,
                        NULL,
                        NULL,
                        hInstance,
                        NULL
						
                    );

                    if (hwndCon == NULL)
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
						   ShowWindow(hwndCon, SW_SHOW);
                           UpdateWindow(hwndCon);
						  break; 
						}
						return 0;
						  
				
			 
			 
			     
			     return 0;
			 }	
    }
	
	
	
	}  

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
