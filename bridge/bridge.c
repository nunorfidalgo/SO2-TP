#include "bridge.h"

Jogo BRIDGE_API *CriaMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo) {
	tam_jogo->QuadPart = sizeof(Jogo);
	hMapMemParJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_jogo->HighPart, tam_jogo->LowPart, TEXT("Jogo"));
	if (hMapMemParJogo == NULL) {
		_tprintf(TEXT("Erro ao criar memoria partilhada de forma a iniciar novo jogo. (código=%d)\n"), GetLastError());
		exit(1);
	}
	return (Jogo *)MapViewOfFile(hMapMemParJogo, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_jogo->QuadPart);
}

Jogo BRIDGE_API *AcedeMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo) {
	tam_jogo->QuadPart = sizeof(Jogo);
	hMapMemParJogo = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("Jogo"));
	if (hMapMemParJogo == NULL) {
		_tprintf(TEXT("Erro ao aceder à memoria partilhada do jogo! (código=%d)\n"), GetLastError());
		_tprintf(TEXT("Por favor inicie o servidor...\n"));
		exit(1);
	}
	return (Jogo *)MapViewOfFile(hMapMemParJogo, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_jogo->QuadPart);
}

//Mensagem BRIDGE_API * CriaMemoriaPartilhadaMensagens(HANDLE	&hMapMemParMsg, LARGE_INTEGER &tam_mensagem) {
//	tam_mensagem.QuadPart = sizeof(Mensagem);
//	hMapMemParMsg = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_mensagem.HighPart, tam_mensagem.LowPart, TEXT("Mensagens"));
//	if (hMapMemParMsg == NULL) {
//		_tprintf(TEXT("ERRO ao criar memoria partilhada para Mensagens: %d\n"), GetLastError());
//		exit(1);
//	}
//	return (Mensagem *)MapViewOfFile(hMapMemParMsg, FILE_MAP_WRITE, 0, 0, (SIZE_T)tam_mensagem.QuadPart);
//}

//Mensagem BRIDGE_API * MemoriaPartilhadaMensagens(HANDLE	&hMapMemParMsg, LARGE_INTEGER &tam_mensagem) {
//	tam_mensagem.QuadPart = sizeof(Mensagem);
//	hMapMemParMsg = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_mensagem.HighPart, tam_mensagem.LowPart, TEXT("Mensagens"));
//	if (hMapMemParMsg == NULL) {
//		_tprintf(TEXT("ERRO ao criar memoria partilhada para Mensagens: %d\n"), GetLastError());
//		exit(1);
//	}
//	return (Mensagem *)MapViewOfFile(hMapMemParMsg, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_mensagem.QuadPart);
//}

void gotoxy(int x, int y) {
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if (!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, coord);
}

BRIDGE_API BOOL APIENTRY WINAPI DllMain(HANDLE hInstance, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro ao iniciar a DLL!\n"));
		//else
			//_tprintf(TEXT("\nBridge: pronta...\n"));
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro a terminar a DLL!\n"));
		//else
			//_tprintf(TEXT("\nBrige: terminou..."));
		break;
	}
	return 1;
}