#include "bridge.h"

int BRIDGE_API Teste(void) {
	_tprintf(TEXT("\ntexto de teste..."));
	return 0;
}
int BRIDGE_API UmValor(int v) {
	return v;
}

void BRIDGE_API escreve_msgs(int id) {
	HANDLE		hEvent;
	Mensagem	*msgs;
	HANDLE		hMap;
	LARGE_INTEGER t;
	t.QuadPart = sizeof(Mensagem);
	hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, t.HighPart, t.LowPart, TEXT("Mensagens"));
	// falta if para testar 
	msgs = (Mensagem *)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, (SIZE_T)t.QuadPart);
	// Event
	hEvent = CreateEvent(NULL, true, false, TEXT("EvMensagens"));
	if (hEvent == NULL) {
		_tprintf(TEXT("ERRO ao criar evento de Mensagens: %d\n"), GetLastError());
		exit(1);
	}
	do {
		_tprintf(TEXT("enviar mensagem: "));
		_fgetts(msgs->texto, TEXTO, stdin);
		msgs->idJogador = id;
		msgs->texto[_tcslen(msgs->texto) - 1] = TEXT('\0');
		if (_tcsncmp(msgs->texto, TEXT("ajuda"), 5) == 0) {
			_tprintf(TEXT("fim: termina\n"));
		}
		SetEvent(hEvent);
		ResetEvent(hEvent);
	} while (_tcsncmp(msgs->texto, TEXT("fim"), 3) != 0);
	CloseHandle(hEvent);
	UnmapViewOfFile(msgs);
	CloseHandle(hMap);
}

void BRIDGE_API le_msgs() {
	HANDLE		hEvent;
	Mensagem	*msgs;
	HANDLE		hMap;
	LARGE_INTEGER t;
	t.QuadPart = sizeof(Mensagem);
	hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, t.HighPart, t.LowPart, TEXT("Mensagens"));
	msgs = (Mensagem *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, (SIZE_T)t.QuadPart);
	// Event
	hEvent = OpenEvent(SYNCHRONIZE, true, TEXT("EvMensagens"));
	if (hEvent == NULL) {
		_tprintf(TEXT("ERRO ao aceder ao evento de Mensagens: %d\n"), GetLastError());
		exit (1);
	}
	do {
		WaitForSingleObject(hEvent, INFINITE);
		if (_tcsncmp(msgs->texto, TEXT("ajuda"), 5) != 0) {
			_tprintf(TEXT("mensagem[%d]: %s\n"), msgs->idJogador, msgs->texto);
		}
	} while (_tcsncmp(msgs->texto, TEXT("fim"), 3) != 0);
	CloseHandle(hEvent);
	UnmapViewOfFile(msgs);
	CloseHandle(hMap);
}

Jogo BRIDGE_API * MemoriaPartilhadaJogo(HANDLE	&hMapMemParJogo, LARGE_INTEGER &tam_jogo) {
	tam_jogo.QuadPart = sizeof(Jogo);
	Jogo *tmp;
	hMapMemParJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_jogo.HighPart, tam_jogo.LowPart, TEXT("Jogo"));
	if (hMapMemParJogo == NULL) {
		_tprintf(TEXT("ERRO ao criar memoria partilhada para o Jogo: %d\n"), GetLastError());
		exit(1);
	}
	tmp = (Jogo *)MapViewOfFile(hMapMemParJogo, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_jogo.QuadPart);
	return tmp;
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

Mensagem BRIDGE_API * MemoriaPartilhadaMensagens(HANDLE	&hMapMemParMsg, LARGE_INTEGER &tam_mensagem) {
	tam_mensagem.QuadPart = sizeof(Mensagem);
	hMapMemParMsg = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_mensagem.HighPart, tam_mensagem.LowPart, TEXT("Mensagens"));
	if (hMapMemParMsg == NULL) {
		_tprintf(TEXT("ERRO ao criar memoria partilhada para Mensagens: %d\n"), GetLastError());
		exit(1);
	}
	return (Mensagem *)MapViewOfFile(hMapMemParMsg, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_mensagem.QuadPart);
}

void BRIDGE_API EscreveMensagens(int idJogador, Mensagem *mensagens, HANDLE hEvMsg) {
	_tprintf(TEXT("enviar: "));
	_fgetts(mensagens->texto, TEXTO, stdin);
	mensagens->idJogador = idJogador;
	mensagens->texto[_tcslen(mensagens->texto) - 1] = TEXT('\0');
	_tprintf(TEXT("mensagem[%d]: %s\n"), mensagens->idJogador, mensagens->texto);
	SetEvent(hEvMsg);
	ResetEvent(hEvMsg);
}

void BRIDGE_API LeMensagens(Mensagem *mensagens, HANDLE hEvMsg) {
	WaitForSingleObject(hEvMsg, INFINITE);
	_tprintf(TEXT("mensagem[%d]: %s\n"), mensagens->idJogador, mensagens->texto);
}

void gotoxy(int x, int y) {
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if (!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, coord);
}

extern "C" BRIDGE_API BOOL APIENTRY WINAPI DllMain(HANDLE hInstance, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("Bridge: Ocorreu um erro ao iniciar a DLL!\n"));
		else
			_tprintf(TEXT("Bridge: pronta...\n"));
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("Bridge: Ocorreu um erro a terminar a DLL!\n"));
		else
			_tprintf(TEXT("Brige: terminou..."));
		break;
	}
	return 1;
}