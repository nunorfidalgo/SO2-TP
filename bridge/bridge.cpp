#include "bridge.h" //DLL.h"

#define TAM 80

// Estrutura de dados
//typedef struct {
//	int tamanho;
//	int x;
//	int y;
//} NAVES;
//
//typedef struct {
//	int tamanho;
//	int x;
//	int y;
//} TIROS;
//
//typedef struct {
//	int tamanho;
//	int x;
//	int y;
//} POWERUPS;

	int Teste(void) {
		_tprintf(TEXT("\nbridge: texto de teste..."));
		return 0;
	}

	int UmValor(int v) {
		return v;
	}
	
	int patrao() {
		_tprintf(TEXT("\nPatrao:"));
		HANDLE	hEvent;
		TCHAR *cmd;
	
		HANDLE hMap; // hFile
	
		// Abrir ficheiro... (RW)
		//hFile = CreateFile(TEXT("memdados.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
		//hMap = CreateFileMapping(INVALID_HANDLE_VALUE, ..., TAM * sizeof(TCHAT));
		//hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, TAM * sizeof(TCHAR), NULL);
		LARGE_INTEGER t;
		t.QuadPart = TAM * sizeof(TCHAR);
		//hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, t.HighPart, t.LowPart, TEXT("shm"));
		hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, t.HighPart, t.LowPart, TEXT("shm"));
		//cmd = (TCHAR *) MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, TAM * sizeof(TCHAR));
		cmd = (TCHAR *)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, (SIZE_T)t.QuadPart);
	
		// Event
		hEvent = CreateEvent(NULL, true, false, TEXT("evento"));
		if (hEvent == NULL) {
			_tprintf(TEXT("CreateEvent error: %d\n"), GetLastError());
			return 1;
		}
		do {
			_tprintf(TEXT("CMD: "));
			_fgetts(cmd, TAM, stdin);
			cmd[_tcslen(cmd) - 1] = TEXT('\0');
			_tprintf(TEXT("Escrevi %d bytes: '%s'\n"), (_tcslen(cmd) + 1), cmd);
			SetEvent(hEvent);
			ResetEvent(hEvent);
		} while (_tcsncmp(cmd, TEXT("fim"), 3) != 0);
	
		CloseHandle(hEvent);
		// Fechar ficheiro
		//CloseHandle(hFile);
		UnmapViewOfFile(cmd);
		CloseHandle(hMap);
	
		_tprintf(TEXT("\nPatrao: fim"));
		return 0;
	}
	
	int empregado() {
		_tprintf(TEXT("\nEmpregado: "));
		HANDLE	hEvent;
		TCHAR *cmd;
	
		HANDLE hMap;
	
		LARGE_INTEGER t;
		t.QuadPart = TAM * sizeof(TCHAR);
	
		//hFile = CreateFile(TEXT("dados.txt"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, t.HighPart, t.LowPart, TEXT("shm"));
		cmd = (TCHAR *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, (SIZE_T)t.QuadPart);
	
		// Event
		hEvent = OpenEvent(SYNCHRONIZE, true, TEXT("evento"));
		if (hEvent == NULL) {
			_tprintf(TEXT("CreateSemaphore error: %d\n"), GetLastError());
			return 1;
		}
		do {
			WaitForSingleObject(hEvent, INFINITE);
			_tprintf(TEXT("Li '%s' (%d bytes)\n"), cmd, _tcslen(cmd) + 1);
	
		} while (_tcsncmp(cmd, TEXT("fim"), 3) != 0);
	
		CloseHandle(hEvent);
		// Fechar ficheiro
		//CloseHandle(hFile);
		UnmapViewOfFile(cmd);
		CloseHandle(hMap);
		_tprintf(TEXT("\nEmpregado: fim"));
		return 0;
	}

extern "C" BRIDGE_API BOOL APIENTRY WINAPI DllMain(HANDLE hInstance, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro ao iniciar a DLL!"));
		else
			_tprintf(TEXT("Bridge: pronta..."));
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro a terminar a DLL!"));
		else
			_tprintf(TEXT("Brige: terminou..."));
		break;
	}
	return 1;
}