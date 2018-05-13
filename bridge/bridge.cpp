#include "bridge.h"

int BRIDGE_API Teste(void) {
	_tprintf(TEXT("\ntexto de teste..."));
	return 0;
}
int BRIDGE_API UmValor(int v) {
	return v;
}


void BRIDGE_API mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n# Mostra Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("-Nave[%d]: posição=(%d,%d), dimensão=(%d,%d), resistencia=%d, velocidade=%d, tipo=%c;\n"), i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].dimensao.altura, naves_invasoras[i].dimensao.largura, naves_invasoras[i].resistencia, naves_invasoras[i].velocidade, naves_invasoras[i].tipo);
}

void BRIDGE_API mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n# Mostra Naves Defensoras:\n"));
	int i, j;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT("-Nave[%d]: posição=(%d,%d), dimensão=(%d,%d), vidas=%d, velocidade=%d\n"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].dimensao.altura, naves_defensoras[i].dimensao.largura, naves_defensoras[i].vidas, naves_defensoras[i].velocidade);
		for (j = 0; j < NUM_POWERUPS_NAV_DEF; j++) {
			_tprintf(TEXT("-Nave[%d]->PowerUps[%d]: posição=(%d,%d), dimensão=(%d,%d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, j, naves_defensoras[i].powerup[j].coord.x, naves_defensoras[i].powerup[j].coord.y, naves_defensoras[i].powerup[j].dimensao.altura, naves_defensoras[i].powerup[j].dimensao.largura, naves_defensoras[i].powerup[j].duracao, naves_defensoras[i].powerup[j].velocidade, naves_defensoras[i].powerup[j].ocorrencia, naves_defensoras[i].powerup[j].tipo);
		}
	}
}

void BRIDGE_API mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n# Mostra Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT("-Bomba[%d]: posição=(%d,%d), velocidade=%d;\n"), i, bombas[i].coord.x, bombas[i].coord.y, bombas[i].velocidade);
}

void BRIDGE_API mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n# Mostra Tiros:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("-Tiro[%d]: posição=(%d,%d), velocidade=%d;\n"), i, tiros[i].coord.x, tiros[i].coord.y, tiros[i].velocidade);
}

void BRIDGE_API mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n# Mostra PowerUps:\n"));
	int i;
	for (i = 0; i < NUM_POWERUPS; i++)
		_tprintf(TEXT("-PowerUps[%d]: posição=(%d,%d), dimensão=(%d,%d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].dimensao.altura, powerups[i].dimensao.largura, powerups[i].duracao, powerups[i].velocidade, powerups[i].ocorrencia, powerups[i].tipo);
}

void BRIDGE_API mostra_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT("\n# Mostra Pontuações:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("-Pontuação[%d]: pontos=%d, disparos=%d, invasoras=%d, vidas=%d, powerups=%d, colisões=%d;\n"), i, pontuacoes[i].pontos, pontuacoes[i].disparos, pontuacoes[i].invasoras, pontuacoes[i].vidas, pontuacoes[i].powerups, pontuacoes[i].powerups);
}

void BRIDGE_API mostra_obstaculos(Obstaculo *obstaculos) {
	_tprintf(TEXT("\n# Mostra Obstáculos:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("-Obstáculo[%d]: posição=(%d,%d), dimensão=(%d,%d), resistência=%d;\n"), i, obstaculos[i].coord.x, obstaculos[i].coord.y, obstaculos[i].dimensao.altura, obstaculos[i].dimensao.largura, obstaculos[i].resistencia);
}

void BRIDGE_API mostra_jogo_na_consola(Jogo *jogo) {
	int i; // j;
	// Naves Invasoras
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		gotoxy(jogo->naves_invasoras[i].coord.x, jogo->naves_invasoras[i].coord.y);
		_tprintf(TEXT("i"));
	}
	// Naves Defensoras
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		gotoxy(jogo->naves_defensoras[i].coord.x, jogo->naves_defensoras[i].coord.y);
		_tprintf(TEXT("d"));
		/*for (j = 0; j < NUM_POWERUPS_NAVE; j++) {
			gotoxy(jogo->naves_defensoras[i].powerup[j].coord.x, jogo->naves_defensoras[i].powerup[j].coord.y);
			_tprintf(TEXT("P"));
		}*/
	}
	// Naves Bombas
	for (i = 0; i < NUM_BOMBAS; i++) {
		gotoxy(jogo->bombas[i].coord.x, jogo->bombas[i].coord.y);
		_tprintf(TEXT("b"));
	}
	// Naves Tiros
	for (i = 0; i < NUM_TIROS; i++) {
		gotoxy(jogo->tiros[i].coord.x, jogo->tiros[i].coord.y);
		_tprintf(TEXT("t"));
	}
	// Naves PowerUp
	for (i = 0; i < NUM_POWERUPS; i++) {
		gotoxy(jogo->powerups[i].coord.x, jogo->powerups[i].coord.y);
		_tprintf(TEXT("p"));
	}
	// Naves Obstáculo
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		gotoxy(jogo->obstaculos[i].coord.x, jogo->obstaculos[i].coord.y);
		_tprintf(TEXT("o"));
	}
}

Jogo BRIDGE_API * MemoriaPartilhadaJogo(HANDLE	&hMapMemParJogo, LARGE_INTEGER &tam_jogo) {
	tam_jogo.QuadPart = sizeof(Jogo);
	hMapMemParJogo = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, tam_jogo.HighPart, tam_jogo.LowPart, TEXT("Jogo"));
	if (hMapMemParJogo == NULL) {
		_tprintf(TEXT("ERRO ao criar memoria partilhada para o Jogo: %d\n"), GetLastError());
		exit(1);
	}
	return (Jogo *)MapViewOfFile(hMapMemParJogo, FILE_MAP_ALL_ACCESS, 0, 0, (SIZE_T)tam_jogo.QuadPart);
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
		_tprintf(TEXT("enviar mensagem (?): "));
		_fgetts(msgs->texto, TEXTO, stdin);
		msgs->idJogador = id;
		msgs->texto[_tcslen(msgs->texto) - 1] = TEXT('\0');
		if (_tcsncmp(msgs->texto, TEXT("?"), 1) == 0) {
			_tprintf(TEXT("comandos:\n"));
			_tprintf(TEXT("* '?': mostra comandos de ajuda\n"));
			_tprintf(TEXT("* 'sair': termina\n"));
		}
		SetEvent(hEvent);
		ResetEvent(hEvent);
	} while (_tcsncmp(msgs->texto, TEXT("sair"), 3) != 0);
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
		_tprintf(TEXT("Confirme se a aplicação 'gateway' está em execução?\n"));
		exit(1);
	}
	do {
		WaitForSingleObject(hEvent, INFINITE);
		if (_tcsncmp(msgs->texto, TEXT("?"), 1) != 0) {
			_tprintf(TEXT("mensagem[%d]: %s\n"), msgs->idJogador, msgs->texto);
		}
	} while (_tcsncmp(msgs->texto, TEXT("sair"), 4) != 0);
	CloseHandle(hEvent);
	UnmapViewOfFile(msgs);
	CloseHandle(hMap);
}

void BRIDGE_API EscreveMensagens(int idJogador, Mensagem *mensagens, HANDLE hEvMsg) {
	do {
		_tprintf(TEXT("enviar mensagem (?): "));
		_fgetts(mensagens->texto, TEXTO, stdin);
		mensagens->idJogador = idJogador;
		mensagens->texto[_tcslen(mensagens->texto) - 1] = TEXT('\0');
		if (_tcsncmp(mensagens->texto, TEXT("?"), 1) == 0) {
			_tprintf(TEXT("comandos:\n"));
			_tprintf(TEXT("* '?': mostra comandos de ajuda\n"));
			_tprintf(TEXT("* 'sair': termina\n"));
		}
		SetEvent(hEvMsg);
		ResetEvent(hEvMsg);
	} while (_tcsncmp(mensagens->texto, TEXT("sair"), 3) != 0);
}

void BRIDGE_API LeMensagens(Mensagem *mensagens, HANDLE hEvMsg) {
	do {
		WaitForSingleObject(hEvMsg, INFINITE);
		if (_tcsncmp(mensagens->texto, TEXT("?"), 1) != 0) {
			_tprintf(TEXT("mensagem[%d]: %s\n"), mensagens->idJogador, mensagens->texto);
		}
	} while (_tcsncmp(mensagens->texto, TEXT("sair"), 4) != 0);
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