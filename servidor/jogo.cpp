#include "../dados.h"
#include "jogo.h"
#include "../bridge/bridge.h"

void inicia_jogo(Jogo *jogo) {
	_tprintf(TEXT("* Novo Jogo:\n"));
	inicia_naves_invasoras(jogo->naves_invasoras);
	//inicia_naves_defensoras(jogo->naves_defensoras);
	//inicia_bombas(jogo->bombas);
	//inicia_tiros(jogo->tiros);
	//inicia_powerups(jogo->powerups);
}

void inicia_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("* Inicia Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].tamanho = 4 + (2 * i);
		naves_invasoras[i].coord.x = 3;
		naves_invasoras[i].coord.y = 3 * i;
	}
}

void inicia_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].tamanho = 2 * i;
		naves_defensoras[i].coord.x = 23;
		naves_defensoras[i].coord.y = (COLUNAS / 2) + i + 4;
	}
}

void inicia_bombas(Bomba *bombas) {
	_tprintf(TEXT("* Inicia Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++) {
		bombas[i].coord.x = 4;
		bombas[i].coord.y = i * 2;
	}
}

void inicia_tiros(Tiro *tiros) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = 22;
		tiros[i].coord.y = (COLUNAS / 2) + i + 4;
	}
}

void inicia_powerups(PowerUp *powerups) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i;
	for (i = 0; i < NUM_POWERUP; i++) {
		powerups[i].tamanho = 2 * i;
		powerups[i].coord.x = 6;
		powerups[i].coord.y = i * 4;
	}
}


void mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n# Mostra Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("[Nave]: id=%d, x=%d, y=%d, tamanho=%d;\n"), i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].tamanho);
}

void mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n# Mostra Naves Defensoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
		_tprintf(TEXT("[Nave]: id=%d, x=%d, y=%d, tamanho=%d;\n"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].tamanho);
}

void mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n# Mostra Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT("[Bomba]: id=%d, x=%d, y=%d;\n"), i, bombas[i].coord.x, bombas[i].coord.y);
}

void mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n# Mostra Tiros:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("[Tiro]: id=%d, x=%d, y=%d;\n"), i, tiros[i].coord.x, tiros[i].coord.y);
}

void mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n# Mostra PowerUps:\n"));
	int i;
	for (i = 0; i < NUM_POWERUP; i++)
		_tprintf(TEXT("[PowerUp]: id=%d, x=%d, y=%d, tamanho=%d, tipo=%c;\n"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].tipo, powerups[i].tamanho);
}

DWORD __stdcall naves_invasoras(void *ptr) {
	NaveInvasora *naves_invasoras = (NaveInvasora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].tamanho = 4 + (2 * i);
		naves_invasoras[i].coord.x = 3;
		naves_invasoras[i].coord.y = 3 * i;
	}
	return 0;
}

DWORD __stdcall naves_defensoras(void *ptr) {
	NaveDefensora *naves_defensoras = (NaveDefensora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Defensoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].tamanho = 2 * i;
		naves_defensoras[i].coord.x = 23;
		naves_defensoras[i].coord.y = (COLUNAS / 2) + i + 4;
	}
	return 0;
}

DWORD __stdcall batalha(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Batalha:\n"));
	/*int i;
	for (i = 0; i < NUM_BOMBAS; i++) {
		bombas[i].coord.x = 4;
		bombas[i].coord.y = i * 2;
	}*/
	return 0;
}

DWORD __stdcall efeitos(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Efeitos:\n"));
	/*int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = 22;
		tiros[i].coord.y = (COLUNAS / 2) + i + 4;
	}*/
	return 0;
}

DWORD __stdcall jogadores(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Jogadores:\n"));
	/*int i;
	for (i = 0; i < NUM_POWERUP; i++) {
		powerups[i].tamanho = 2 * i;
		powerups[i].coord.x = 6;
		powerups[i].coord.y = i * 4;
	}*/
	return 0;
}