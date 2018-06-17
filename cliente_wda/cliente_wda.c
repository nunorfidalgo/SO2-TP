#include "resource.h"
#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <locale.h>

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

#define TITULO "Cliente Phoenix"
#define JANELA_LARGURA 800
#define JANELA_ALTURA 600
#define JANELA_POS_INICIAL_X 850
#define JANELA_POS_INICIAL_Y 50

HINSTANCE hInstance;

LRESULT CALLBACK Cliente(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szProgName[] = TEXT(TITULO);

HDC hdc = NULL;
HDC auxDC = NULL;
HBRUSH bg = NULL;
HBITMAP auxBM = NULL;
int nX = 0, nY = 0;

HBITMAP hNave = NULL;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {

	setlocale(LC_ALL, "pt-PT");

	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcApp;
	wcApp.cbSize = sizeof(WNDCLASSEX);
	wcApp.hInstance = hInst;
	wcApp.lpszClassName = szProgName;
	wcApp.lpfnWndProc = Cliente;
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcApp.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU);
	wcApp.cbClsExtra = 0;
	wcApp.cbWndExtra = 0;

	if (!RegisterClassEx(&wcApp))
		return(0);

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
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return((int)lpMsg.wParam);
}

LRESULT CALLBACK Cliente(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	static int sair, x = 0, y = 0;
	static TCHAR letras[10] = TEXT("\0");

	HDC hdc;
	PAINTSTRUCT ps;

	static BITMAP bmNave;
	static HDC hdcNave;
	
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
		case IDM_JOGO_NOVO:
			//MessageBox(NULL, "Menu Configs", "confirmar", MB_ICONEXCLAMATION | MB_OK);
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_JOGO_NOVO), hWnd, NovoJogo);
			break;
		case IDM_JOGO_SAIR:
			sair = MessageBox(hWnd, TEXT("Terminar servidor?"), TEXT("Confirme:"), MB_YESNO);
			if (sair == IDYES)
				DestroyWindow(hWnd);
		default:
			return DefWindowProc(hWnd, messg, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
		// CARREGA 'BITMAP' E ASSOCIA A UM 'DC' EM MEMORIA PARA A NAVE...
		hNave = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		hdc = GetDC(hWnd);
		GetObject(hNave, sizeof(bmNave), &bmNave);
		hdcNave = CreateCompatibleDC(hdc);
		SelectObject(hdcNave, hNave);
		ReleaseDC(hWnd, hdc);

		// EX1...
		// OBTEM AS DIMENSOES DO DISPLAY... 
		bg = CreateSolidBrush(RGB(0, 0, 0)); // RGB(255, 128, 128)
		nX = GetSystemMetrics(SM_CXSCREEN);
		nY = GetSystemMetrics(SM_CYSCREEN);

		// PREPARA 'BITMAP' E ASSOCIA A UM 'DC' EM MEMORIA... 
		hdc = GetDC(hWnd);
		auxDC = CreateCompatibleDC(hdc);
		auxBM = CreateCompatibleBitmap(hdc, nX, nY);
		SelectObject(auxDC, auxBM);
		SelectObject(auxDC, bg);
		PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);
		ReleaseDC(hWnd, hdc);

		break;
	case WM_CHAR:
	{
		letras[0] = wParam;
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_UP:
			y-=5;
			break;
		case VK_DOWN:
			y+=5;
			break;
		case VK_LEFT:
			x-=5;
			break;
		case VK_RIGHT:
			x+=5;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

	case WM_PAINT:
	{
		/*PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		Rectangle(hdc, x, y, x + 50, y + 30);
		TextOut(hdc, x, y, letras, 1);
		EndPaint(hWnd, &ps);*/

		// DESENHA NO 'DC' EM MEMORIA... 		
		PatBlt(auxDC, 0, 0, nX, nY, PATCOPY);
		BitBlt(auxDC, x, y, bmNave.bmWidth, bmNave.bmHeight, hdcNave, 0, 0, SRCCOPY);

		// SetStretchBltMode(auxDC, BLACKONWHITE);
		// StretchBlt(auxDC, x, y, 100, 60, hdcNave, 0, 0, bmNave.bmWidth, bmNave.bmHeight, SRCCOPY);

		// EX1...
		// DESENHA NO 'DC' EM MEMORIA... 
		//PatBlt(auxDC, 0, 0, nX, nY, PATCOPY); // comentado
		//Rectangle(auxDC, x, y, x + 50, y + 30);
		//TextOut(auxDC, x + 5, y + 5, letras, 1);

		// COPIA INFORMACAO DO 'DC' EM MEMORIA PARA O DISPLAY... 
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, nX, nY, auxDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CLOSE:
		sair = MessageBox(hWnd, TEXT("Fechar app?"), TEXT("confirmar:"), MB_YESNO);
		if (sair == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		// LIBERTA RECURSOS RELATIVOS AO 'BITMAP' E AO 'DC' DA NAVE... 
		DeleteObject(hNave);
		DeleteDC(hdcNave);

		// EX1...
		DeleteObject(bg);
		DeleteObject(auxBM);
		DeleteDC(auxDC);
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
		break;
	}
	return(0);
}

INT_PTR CALLBACK NovoJogo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDLIGAR:
			//GetDlgItemText(hDlg, IDC_EDIT1, login, 30);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		case IDCANCELAR:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		case IDCANCEL:
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

INT_PTR CALLBACK Sobre(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
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
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}