#include "bridge.h"

int BRIDGE_API Teste(void) {
	_tprintf(TEXT("\ntexto de teste..."));
	return 0;
}
int BRIDGE_API UmValor(int v) {
	return v;
}

// Mostrar a informação dos dados de jogo
void BRIDGE_API mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n# Mostra Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT(" - Nave[%d]: posição=(%02d,%02d), dimensão=(%02d,%02d), resistencia=%d, velocidade=%d, tipo=%c;\n"), i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].dimensao.altura, naves_invasoras[i].dimensao.largura, naves_invasoras[i].resistencia, naves_invasoras[i].velocidade, naves_invasoras[i].tipo);
}

void BRIDGE_API mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n# Mostra Naves Defensoras:\n"));
	int i, j;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT(" - Nave[%d]: posição=(%02d,%02d), dimensão=(%02d,%02d), vidas=%d, velocidade=%d\n"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].dimensao.altura, naves_defensoras[i].dimensao.largura, naves_defensoras[i].vidas, naves_defensoras[i].velocidade);
		for (j = 0; j < NUM_POWERUPS_NAV_DEF; j++) {
			_tprintf(TEXT(" - Nave[%d]->PowerUps[%d]: posição=(%02d,%02d), dimensão=(%02d,%02d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, j, naves_defensoras[i].powerup[j].coord.x, naves_defensoras[i].powerup[j].coord.y, naves_defensoras[i].powerup[j].dimensao.altura, naves_defensoras[i].powerup[j].dimensao.largura, naves_defensoras[i].powerup[j].duracao, naves_defensoras[i].powerup[j].velocidade, naves_defensoras[i].powerup[j].ocorrencia, naves_defensoras[i].powerup[j].tipo);
		}
	}
}

void BRIDGE_API mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n# Mostra Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT(" - Bomba[%d]: posição=(%02d,%02d), velocidade=%d;\n"), i, bombas[i].coord.x, bombas[i].coord.y, bombas[i].velocidade);
}

void BRIDGE_API mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n# Mostra Tiros:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT(" - Tiro[%d]: posição=(%02d,%02d), velocidade=%d;\n"), i, tiros[i].coord.x, tiros[i].coord.y, tiros[i].velocidade);
}

void BRIDGE_API mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n# Mostra PowerUps:\n"));
	int i;
	for (i = 0; i < NUM_POWERUPS; i++)
		_tprintf(TEXT(" - PowerUps[%d]: posição=(%02d,%02d), dimensão=(%02d,%02d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].dimensao.altura, powerups[i].dimensao.largura, powerups[i].duracao, powerups[i].velocidade, powerups[i].ocorrencia, powerups[i].tipo);
}

void BRIDGE_API mostra_obstaculos(Obstaculo *obstaculos) {
	_tprintf(TEXT("\n# Mostra Obstáculos:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT(" - Obstáculo[%d]: posição=(%02d,%02d), dimensão=(%02d,%02d), resistência=%d;\n"), i, obstaculos[i].coord.x, obstaculos[i].coord.y, obstaculos[i].dimensao.altura, obstaculos[i].dimensao.largura, obstaculos[i].resistencia);
}

void BRIDGE_API mostra_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT("\n# Mostra Pontuações:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT(" - Pontuação[%d]: pontos=%d, disparos=%d, invasoras=%d, vidas=%d, powerups=%d, colisões=%d;\n"), i, pontuacoes[i].pontos, pontuacoes[i].disparos, pontuacoes[i].invasoras, pontuacoes[i].vidas, pontuacoes[i].powerups, pontuacoes[i].powerups);
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
	}
	//// Bombas
	//for (i = 0; i < NUM_BOMBAS; i++) {
	//	gotoxy(jogo->bombas[i].coord.x, jogo->bombas[i].coord.y);
	//	_tprintf(TEXT("8"));
	//}
	// Tiros
	for (i = 0; i < NUM_TIROS; i++) {
		if (jogo->tiros[i].tipo != '0') {
			gotoxy(jogo->tiros[i].coord.x, jogo->tiros[i].coord.y);
			_tprintf(TEXT("."));
		}
	}
	//// PowerUps
	//for (i = 0; i < NUM_POWERUPS; i++) {
	//	gotoxy(jogo->powerups[i].coord.x, jogo->powerups[i].coord.y);
	//	_tprintf(TEXT("*"));
	//}
	//// Obstáculos
	//for (i = 0; i < NUM_OBSTACULOS; i++) {
	//	gotoxy(jogo->obstaculos[i].coord.x, jogo->obstaculos[i].coord.y);
	//	_tprintf(TEXT("#"));
	//}
}

void BRIDGE_API mostra_tabuleiro_jogo() {
	int i;

	//gotoxy(0, 0); _tprintf(TEXT("."));
	//gotoxy(1, 0); _tprintf(TEXT("."));
	//gotoxy(2, 0); _tprintf(TEXT("."));
	//gotoxy(3, 0); _tprintf(TEXT("."));
	//gotoxy(4, 0); _tprintf(TEXT("."));

	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_Y_INICIAL);
		_tprintf(TEXT("-"));
	}

	//gotoxy(0, 5); _tprintf(TEXT("*"));
	//gotoxy(1, 5); _tprintf(TEXT("*"));
	//gotoxy(2, 5); _tprintf(TEXT("*"));
	//gotoxy(3, 5); _tprintf(TEXT("*"));
	//gotoxy(4, 5); _tprintf(TEXT("*"));

	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_Y_LIMITE_NAV_DEF_MOV);
		_tprintf(TEXT("-"));
	}

	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_FIM_TAB_Y);
		_tprintf(TEXT("-"));
	}

	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_FIM_Y);
		_tprintf(TEXT("-"));
	}

	for (i = 0; i < LINHAS + 2; i++) {
		gotoxy(COLUNAS, i);
		_tprintf(TEXT("|"));
	}

	gotoxy(POS_ZERO, POS_FIM_TAB_Y);
	_tprintf(TEXT("Mensagens:\n"));
	gotoxy(POS_ZERO, POS_ENVIAR_MSGS);
	_tprintf(TEXT("Enviar mensagem(m): \n"));

	gotoxy(82, 0);
	_tprintf(TEXT("* Phoenix (multiplayer)"));
	gotoxy(82, 2);
	_tprintf(TEXT("* Teclas:"));
	gotoxy(82, 3);
	_tprintf(TEXT("- Setas CIMA, BAIXO, DIR, ESQ:"));
	gotoxy(82, 4);
	_tprintf(TEXT("\t- movimento nave defensora"));
	gotoxy(82, 5);
	_tprintf(TEXT("- SPACE: dispara 'tiro(s)'"));
	gotoxy(82, 6);
	_tprintf(TEXT("- ENTER: dispara 'bomba'"));
	gotoxy(82, 7);
	_tprintf(TEXT("- M: escreve 'mensagem'"));
	gotoxy(82, 8);
	_tprintf(TEXT("- ESC: sair"));

	gotoxy(82, 10);
	_tprintf(TEXT("* Pontuações:"));

}

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