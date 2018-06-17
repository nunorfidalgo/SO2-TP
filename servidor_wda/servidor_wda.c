#include "resource.h"
#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <locale.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define TITULO "Servidor Phoenix"
#define JANELA_LARGURA 960
#define JANELA_ALTURA 600
#define JANELA_POS_INICIAL_X 50
#define JANELA_POS_INICIAL_Y 50

HINSTANCE hInstance;

LRESULT CALLBACK Servidor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Consola(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Configuracoes(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szProgName[] = TEXT(TITULO);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {

	setlocale(LC_ALL, "pt-PT");

	HWND hWnd; //hWndCmd;
	HWND hwndBtn1;
	MSG lpMsg; 
	WNDCLASSEX wcApp; // wcCmd;

	wcApp.cbSize = sizeof(WNDCLASSEX); 
	wcApp.hInstance = hInst; 
	wcApp.lpszClassName = szProgName;
	wcApp.lpfnWndProc = Servidor;
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcApp.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wcApp.cbClsExtra = 0; 
	wcApp.cbWndExtra = 0;

	if (!RegisterClassEx(&wcApp))
		return(0);

	hInstance = hInst; // guarda a instância numa var handle global

	hWnd = CreateWindow(
		szProgName,
		TEXT(TITULO),
		WS_OVERLAPPEDWINDOW, 
		JANELA_POS_INICIAL_X, 
		JANELA_POS_INICIAL_Y,
		JANELA_LARGURA,
		JANELA_ALTURA,

		(HWND)HWND_DESKTOP,
		(HMENU)NULL,
		(HINSTANCE)hInst,
		0); 

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 

	hwndBtn1 = CreateWindow(
		TEXT("BUTTON"),  // Predefined class; Unicode assumed 
		L"button1",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
		10,         // x position 
		100,         // y position 
		100,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)hInst,
		NULL);

	hwndBtn1 = CreateWindow(
		TEXT("COMBOBOX"),  // Predefined class; Unicode assumed 
		L"Combobox1",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
		10,         // x position 
		160,         // y position 
		100,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)hInst,
		NULL);

	hwndBtn1 = CreateWindow(
		TEXT("edit"), 
		TEXT("edit1"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL |
		ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		10, 
		240, 
		100, 
		200, 
		hWnd, 
		NULL, 
		(HINSTANCE)hInst, 
		NULL);

	//hwndBtn1 = CreateWindow(
	//	TEXT("EDIT"),  // Predefined class; Unicode assumed 
	//	L"edit1",      // Button text 
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
	//	10,         // x position 
	//	240,         // y position 
	//	100,        // Button width
	//	50,        // Button height
	//	hWnd,     // Parent window
	//	MAKEINTRESOURCE(IDR_MENU),       // No menu.
	//	(HINSTANCE)hInst,
	//	NULL);

	hwndBtn1 = CreateWindow(
		TEXT("LISTBOX"),  // Predefined class; Unicode assumed 
		L"listbox1",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
		10,         // x position 
		300,         // y position 
		100,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)hInst,
		NULL);

	hwndBtn1 = CreateWindow(
		TEXT("STATIC"),  // Predefined class; Unicode assumed 
		L"just text",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
		10,         // x position 
		360,         // y position 
		100,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)hInst,
		NULL);

	//*** Consola ************************************************************************/

	//wcCmd.cbSize = sizeof(WNDCLASSEX);
	//wcCmd.hInstance = hInst;
	//wcCmd.lpszClassName = szProgName;
	//wcCmd.lpfnWndProc = Consola;
	//wcCmd.style = CS_HREDRAW | CS_VREDRAW;
	//wcCmd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wcCmd.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	//wcCmd.hCursor = LoadCursor(NULL, IDC_ARROW);
	////wcCmd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcCmd.lpszMenuName = NULL;
	//wcCmd.cbClsExtra = 0;
	//wcCmd.cbWndExtra = 0;

	//if (!RegisterClassEx(&wcApp))
	//	return(0);

	//hInstance = hInst; // guarda a instância numa var handle global

	//hWnd = CreateWindow(
	//	szProgName,
	//	TEXT(TITULO),
	//	WS_OVERLAPPEDWINDOW,
	//	JANELA_POS_INICIAL_X,
	//	JANELA_POS_INICIAL_Y,
	//	JANELA_LARGURA,
	//	JANELA_ALTURA,

	//	(HWND)HWND_DESKTOP,
	//	(HMENU)NULL,
	//	(HINSTANCE)hInst,
	//	0);

	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);


	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg); 
		DispatchMessage(&lpMsg); 
	}

	return((int)lpMsg.wParam); 
}

LRESULT CALLBACK Servidor(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	static int sair;
	HDC hdc;						// Declaração de um handler para um Device Context

	switch (messg) {
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_AJUDA_SOBRE:
			//MessageBox(NULL, "Menu sobre", "confirmar", MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_SOBRE), hWnd, Sobre);
			break;
		case IDM_SERVIDOR_CONFIGURACOES:
			//MessageBox(NULL, "Menu Configs", "confirmar", MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_CONFIGURACOES), hWnd, Configuracoes);
			break;
		case IDM_SERVIDOR_SAIR:
			sair = MessageBox(hWnd, TEXT("Terminar servidor?"), TEXT("Confirme:"), MB_YESNO);
			if (sair == IDYES)
				DestroyWindow(hWnd);
		default:
			return DefWindowProc(hWnd, messg, wParam, lParam);
		}
	}
	break;
		/*case WM_PAINT:
		{*/
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);

		//Rectangle(hdc, x, y, x + 50, y + 30);
		//TextOut(hdc, x, y, letras, 1);
		//EndPaint(hWnd, &ps);
		//}
	case WM_PAINT:{
		RECT r = { 0, 0, 200, 75 };

		
		PAINTSTRUCT PtStc;
		hdc = BeginPaint(hWnd, &PtStc);
		DrawText(hdc, TEXT("Titulo"), _tcslen(TEXT("Titulo")), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &PtStc);
		}
		break;

	case WM_CLOSE:
		sair = MessageBox(hWnd, TEXT("Terminar servidor?"), TEXT("Confirme:"), MB_YESNO);
		if (sair == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
		break;
	}
	return(0);
}

INT_PTR CALLBACK Consola(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	AllocConsole();
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;


	//switch (message) {
	//case WM_INITDIALOG:
	//	break;

	//case WM_COMMAND:
	//	switch (LOWORD(wParam)) {
	//	case IDOK:
	//		//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
	//		EndDialog(hDlg, 0);
	//		return (INT_PTR)TRUE;
	//		break;

	//	case IDCANCEL:
	//		//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
	//		EndDialog(hDlg, 0);
	//		return (INT_PTR)TRUE;
	//		break;
	//	}
	//	break;
	//}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Configuracoes(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;

		case IDCANCEL:
			//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		//case IDLINK:
		//	MessageBox(NULL, TEXT("Dialog Link"), TEXT("link"), MB_ICONEXCLAMATION | MB_OK);
		//	//ShellExecute(hDlg, TEXT("open"), TEXT("https://github.com/nunorfidalgo/SO2-TP"), NULL, NULL, SW_SHOWDEFAULT);
		//	EndDialog(hDlg, 0);
		//	return (INT_PTR)TRUE;
		//	break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);

	switch (message){
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDOK:
			//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;

		case IDCANCEL:
			//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;               
}