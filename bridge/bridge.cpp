#include "bridge.h"

int BRIDGE_API Teste(void) {
	_tprintf(TEXT("\ntexto de teste..."));
	return 0;
}

int BRIDGE_API UmValor(int v) {
	return v;
}

int BRIDGE_API patrao() {
	_tprintf(TEXT("\nPatrao:"));
	HANDLE	hEvent;
	TCHAR *cmd;

	HANDLE hMap; // hFile

	LARGE_INTEGER t;
	t.QuadPart = TAM * sizeof(TCHAR);
	hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, t.HighPart, t.LowPart, TEXT("shm"));
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
		_tprintf(TEXT("Escrevi %d bytes: '%s'\n"), (int)(_tcslen(cmd) + 1), cmd);
		SetEvent(hEvent);
		ResetEvent(hEvent);
	} while (_tcsncmp(cmd, TEXT("fim"), 3) != 0);

	CloseHandle(hEvent);
	UnmapViewOfFile(cmd);
	CloseHandle(hMap);

	_tprintf(TEXT("\nPatrao: fim"));
	return 0;
}

int BRIDGE_API empregado() {
	_tprintf(TEXT("\nEmpregado: "));
	HANDLE	hEvent;
	TCHAR *cmd;

	HANDLE hMap;

	LARGE_INTEGER t;
	t.QuadPart = TAM * sizeof(TCHAR);
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
		_tprintf(TEXT("Li '%s' (%d bytes)\n"), cmd, (int)_tcslen(cmd) + 1);

	} while (_tcsncmp(cmd, TEXT("fim"), 3) != 0);

	CloseHandle(hEvent);
	UnmapViewOfFile(cmd);
	CloseHandle(hMap);
	_tprintf(TEXT("\nEmpregado: fim"));
	return 0;
}

extern "C" BRIDGE_API BOOL APIENTRY WINAPI DllMain(HANDLE hInstance, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro ao iniciar a DLL!\n"));
		else
			_tprintf(TEXT("Bridge: pronta..."));
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == NULL)
			_tprintf(TEXT("\nBridge: Ocorreu um erro a terminar a DLL!\n"));
		else
			_tprintf(TEXT("\nBrige: terminou..."));
		break;
	}
	return 1;
}