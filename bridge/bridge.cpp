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


DWORD __stdcall inicia_naves_invasoras(void *ptr) {
	NaveInvasora * naves_invasoras = (NaveInvasora *)ptr;
	_tprintf(TEXT("\n* Inicia Naves Invasoras: "));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].tamanho = 4 + (2 * i);
		naves_invasoras[i].coord.x = 3;
		naves_invasoras[i].coord.y = 3 * i;
	}
	return 0;
}

DWORD __stdcall inicia_naves_defensoras(void *ptr) {
	NaveDefensora *naves_defensoras = (NaveDefensora *)ptr;
	_tprintf(TEXT("\n* Inicia Naves Defensoras: "));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].tamanho = 2 * i;
		naves_defensoras[i].coord.x = 23;
		naves_defensoras[i].coord.y = (COLUNAS / 2) + i + 4;
	}
	return 0;
}

DWORD __stdcall inicia_bombas(void *ptr) {
	Bomba *bombas = (Bomba *)ptr;
	_tprintf(TEXT("\n* Inicia Bombas: "));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++) {
		bombas[i].coord.x = 4;
		bombas[i].coord.y = i * 2;
	}
	return 0;
}

DWORD __stdcall inicia_tiros(void *ptr) {
	Tiro *tiros = (Tiro *)ptr;
	_tprintf(TEXT("\n* Inicia Naves Defensoras: "));
	int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = 22;
		tiros[i].coord.y = (COLUNAS / 2) + i + 4;
	}
	return 0;
}

DWORD __stdcall inicia_powerups(void *ptr) {
	PowerUp *powerups = (PowerUp *)ptr;
	_tprintf(TEXT("\n* Inicia Naves Defensoras: "));
	int i;
	for (i = 0; i < NUM_POWERUP; i++) {
		powerups[i].tamanho = 2 * i;
		powerups[i].coord.x = 6;
		powerups[i].coord.y = i * 4;
	}
	return 0;
}

void mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n* Mostra Naves Invasoras: "));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("\n[Nave]: id=%d, x=%d, y=%d, tamanho=%d;"), i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].tamanho);
}

void mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n* Mostra Naves Defensoras: "));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
		_tprintf(TEXT("\n[Nave]: id=%d, x=%d, y=%d, tamanho=%d;"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].tamanho);
}

void mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n* Mostra Bombas: "));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT("\n[Bomba]: id=%d, x=%d, y=%d;"), i, bombas[i].coord.x, bombas[i].coord.y);
}

void mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n* Mostra Tiros: "));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("\n[Tiro]: id=%d, x=%d, y=%d;"), i, tiros[i].coord.x, tiros[i].coord.y);
}

void mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n* Mostra PowerUps: "));
	int i;
	for (i = 0; i < NUM_POWERUP; i++)
		_tprintf(TEXT("\n[PowerUp]: id=%d, x=%d, y=%d, tamanho=%d, tipo=%c;"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].tipo, powerups[i].tamanho);
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