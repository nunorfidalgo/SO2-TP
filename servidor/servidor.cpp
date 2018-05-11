#include "servidor.h"

// Variaveis globais
Jogo			*jogo;
//HANDLE		hEvJogo;

HANDLE			hMapMemParJogo;
LARGE_INTEGER	tam_jogo;

HANDLE			muNavInvs, muNavDefs, muTiros, muBombas, muPowerUps;
HANDLE			htNavInvs, htNavDefs, htTiros, htBombas, htPowerUps;
DWORD			idNavInvs, idNavDefs, idTiros, idBombas, idPowerUps;

//Mensagem		mensagens;

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	system("cls");

	tam_jogo.QuadPart = sizeof(Jogo);
	hMapMemParJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_jogo.HighPart, tam_jogo.LowPart, TEXT("Jogo"));
	if (hMapMemParJogo == NULL) {
		_tprintf(TEXT("\nERRO memoria partilhada: %d"), GetLastError());
		exit(1);
	}
	jogo = (Jogo *)MapViewOfFile(hMapMemParJogo, FILE_MAP_WRITE, 0, 0, (SIZE_T)tam_jogo.QuadPart);

	//// Event
	//hEvJogo = CreateEvent(NULL, true, false, TEXT("Evento"));
	//if (hEvJogo == NULL) {
	//	_tprintf(TEXT("ERRO ao criar evento para o jogo: %d\n"), GetLastError());
	//	exit(1);
	//}

	// Mutex para Naves Invasoras
	muNavInvs = CreateMutex(NULL, FALSE, NULL);
	if (muNavInvs == NULL) {
		_tprintf(TEXT("ERRO ao criar mutex para Naves Invasoras: %d\n"), GetLastError());
		exit(1);
	}
	// Threat Naves Invasoras
	htNavInvs = CreateThread(NULL, 0, inicia_naves_invasoras, (LPVOID)jogo->naves_invasoras, 0, &idNavInvs);
	if (htNavInvs != NULL) {
		_tprintf(TEXT("[Thread Naves Invasoras] id=%d;\n"), idNavInvs);
	}
	else {
		_tprintf(TEXT("ERRO ao criar Thread de Naves Invasoras: %d\n"), GetLastError());
		exit(1);
	}

	// Mutex para Naves Defensoras
	muNavDefs = CreateMutex(NULL, FALSE, NULL);
	if (muNavDefs == NULL) {
		_tprintf(TEXT("ERRO ao criar mutex para Naves Defensoras: %d\n"), GetLastError());
		exit(1);
	}
	// Threat Naves Defensoras
	htNavDefs = CreateThread(NULL, 0, inicia_naves_defensoras, (LPVOID)jogo->naves_defensoras, 0, &idNavDefs);
	if (htNavDefs != NULL) {
		_tprintf(TEXT("[Thread Naves Defensoras] id=%d;\n"), idNavDefs);
	}
	else {
		_tprintf(TEXT("ERRO ao criar Thread de Naves Defensoras: %d\n"), GetLastError());
		exit(1);
	}

	// Mutex para Bombas
	muBombas = CreateMutex(NULL, FALSE, NULL);
	if (muBombas == NULL) {
		_tprintf(TEXT("ERRO ao criar mutex para Bombas: %d\n"), GetLastError());
		exit(1);
	}
	// Threat Bombas
	htBombas = CreateThread(NULL, 0, inicia_bombas, (LPVOID)jogo->bombas, 0, &idBombas);
	if (htBombas != NULL) {
		_tprintf(TEXT("[Thread Bombas] id=%d;\n"), idBombas);
	}
	else {
		_tprintf(TEXT("ERRO ao criar Thread de Bombas: %d\n"), GetLastError());
		exit(1);
	}

	// Mutex para Tiros
	muTiros = CreateMutex(NULL, FALSE, NULL);
	if (muTiros == NULL) {
		_tprintf(TEXT("ERRO ao criar mutex para Tiros: %d\n"), GetLastError());
		exit(1);
	}
	// Threat Tiros
	htTiros = CreateThread(NULL, 0, inicia_tiros, (LPVOID)jogo->tiros, 0, &idTiros);
	if (htTiros != NULL) {
		_tprintf(TEXT("[Thread Tiros] id=%d;\n"), idTiros);
	}
	else {
		_tprintf(TEXT("ERRO ao criar Thread de Tiros: %d\n"), GetLastError());
		exit(1);
	}

	// Mutex para PowerUps
	muPowerUps = CreateMutex(NULL, FALSE, NULL);
	if (muPowerUps == NULL) {
		_tprintf(TEXT("ERRO ao criar mutex para PowerUps: %d\n"), GetLastError());
		exit(1);
	}
	// Threat PowerUps
	htPowerUps = CreateThread(NULL, 0, inicia_powerups, (LPVOID)jogo->powerups, 0, &idPowerUps);
	if (htPowerUps != NULL) {
		_tprintf(TEXT("[Thread PowerUps] id=%d;\n"), idPowerUps);
	}
	else {
		_tprintf(TEXT("ERRO ao criar Thread de PowerUps: %d\n"), GetLastError());
		exit(1);
	}

	mostra_naves_invasoras(jogo->naves_invasoras);
	mostra_naves_defensoras(jogo->naves_defensoras);
	mostra_bombas(jogo->bombas);
	mostra_tiros(jogo->tiros);
	mostra_powerups(jogo->powerups);

	WaitForSingleObject(htNavInvs, INFINITE);
	WaitForSingleObject(htNavDefs, INFINITE);
	WaitForSingleObject(htBombas, INFINITE);
	WaitForSingleObject(htTiros, INFINITE);
	WaitForSingleObject(htPowerUps, INFINITE);

	CloseHandle(muNavInvs);
	CloseHandle(muNavDefs);
	CloseHandle(muBombas);
	CloseHandle(muTiros);
	CloseHandle(muPowerUps);

	//CloseHandle(hEvJogo);
	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\n\nTerminou!!\n"));
	return 0;
}