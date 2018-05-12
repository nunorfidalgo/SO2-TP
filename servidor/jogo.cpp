#include "../dados.h"
#include "jogo.h"
#include "utils.h"

void inicia_jogo(Jogo *jogo) {
	_tprintf(TEXT("* Novo Jogo:\n"));
	inicia_naves_invasoras(jogo->naves_invasoras);
	inicia_naves_defensoras(jogo->naves_defensoras);
	inicia_bombas(jogo->bombas);
	inicia_tiros(jogo->tiros);
	inicia_powerups(jogo->powerups);
	inicia_pontuacoes(jogo->pontuacoes);
	inicia_obstaculos(jogo->obstaculos);
}

void inicia_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("* Inicia Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].resistencia = random_l_h(1, 9);
		naves_invasoras[i].velocidade = random_l_h(1, 9);
		naves_invasoras[i].coord.x = random_l_h(1, COLUNAS);
		naves_invasoras[i].coord.y = random_l_h(1, LINHAS);
		naves_invasoras[i].dimensao.altura = random_l_h(1, 4);
		naves_invasoras[i].dimensao.largura = random_l_h(1, 4);
	}
}

void inicia_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i, j;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].vidas = random_l_h(1, 3);
		naves_defensoras[i].velocidade = random_l_h(1, 9);
		naves_defensoras[i].coord.x = random_l_h(1, COLUNAS);
		naves_defensoras[i].coord.y = random_l_h(1, LINHAS);
		naves_defensoras[i].dimensao.altura = random_l_h(1, 4);
		naves_defensoras[i].dimensao.largura = random_l_h(1, 4);
		for (j = 0; j < NUM_POWERUPS_NAVE; j++) {
			naves_defensoras[i].powerup[j].duracao = random_l_h(1, 30); // entre 0 a 30s
			//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
			naves_defensoras[i].powerup[j].velocidade = random_l_h(1, 10);
			naves_defensoras[i].powerup[j].ocorrencia = random_l_h(1, 3);
			naves_defensoras[i].powerup[j].tipo = 'a';
			naves_defensoras[i].powerup[j].dimensao.altura = random_l_h(1, 6);
			naves_defensoras[i].powerup[j].dimensao.largura = random_l_h(1, 4);
			naves_defensoras[i].powerup[j].coord.x = random_l_h(1, COLUNAS);
			naves_defensoras[i].powerup[j].coord.y = random_l_h(1, LINHAS);
		}
	}
}

void inicia_bombas(Bomba *bombas) {
	_tprintf(TEXT("* Inicia Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++) {
		bombas[i].coord.x = random_l_h(1, COLUNAS);
		bombas[i].coord.y = random_l_h(1, LINHAS);
		bombas[i].velocidade = random_l_h(1, 10);
	}
}

void inicia_tiros(Tiro *tiros) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = random_l_h(1, COLUNAS);
		tiros[i].coord.y = random_l_h(1, LINHAS);
		tiros[i].velocidade = random_l_h(1, 10);
	}
}

void inicia_powerups(PowerUp *powerups) {
	_tprintf(TEXT("* Inicia Naves Defensoras: \n"));
	int i;
	for (i = 0; i < NUM_POWERUP; i++) {
		powerups[i].duracao = random_l_h(1, 30); // entre 0 a 30s
		//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
		powerups[i].velocidade = random_l_h(1, 10);
		powerups[i].ocorrencia = random_l_h(1, 3);
		powerups[i].tipo = 'a';
		powerups[i].dimensao.altura = random_l_h(1, 6);
		powerups[i].dimensao.largura = random_l_h(1, 4);
		powerups[i].coord.x = random_l_h(1, COLUNAS);
		powerups[i].coord.y = random_l_h(1, LINHAS);
	}
}

void inicia_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT("* Inicia Pontuações: \n"));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		pontuacoes[i].pontos = 0;
		pontuacoes[i].disparos = 0;
		pontuacoes[i].invasoras = 0;
		pontuacoes[i].vidas = 0;
		pontuacoes[i].powerups = 0;
		pontuacoes[i].colisoes = 0;
	}
}

void inicia_obstaculos(Obstaculo *obstaculos) {
	_tprintf(TEXT("* Inicia Obstáculos: \n"));
	int i;
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		obstaculos[i].resistencia = 0;
		obstaculos[i].dimensao.altura = random_l_h(1, 6);
		obstaculos[i].dimensao.largura = random_l_h(1, 4);
		obstaculos[i].coord.x = random_l_h(1, COLUNAS);
		obstaculos[i].coord.y = random_l_h(1, LINHAS);
	}
}

void mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n# Mostra Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("[Nave]: id=%d, posição=(%d,%d), dimensao=(%d,%d), resistencia=%d, velocidade=%d, tipo=%c;\n"), i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].dimensao.altura, naves_invasoras[i].dimensao.largura, naves_invasoras[i].resistencia, naves_invasoras[i].velocidade, naves_invasoras[i].tipo);
}

void mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n# Mostra Naves Defensoras:\n"));
	int i, j;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
		_tprintf(TEXT("[Nave]: id=%d, posição=(%d,%d), dimensao=(%d,%d), vidas=%d, velocidade=%d\n"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].dimensao.altura, naves_defensoras[i].dimensao.largura, naves_defensoras[i].vidas, naves_defensoras[i].velocidade);
		for (j = 0; j < NUM_POWERUPS_NAVE; j++)
			_tprintf(TEXT("[Nave->PowerUps]: id=%d, posição=(%d,%d), dimensao=(%d,%d), duracao=%d, adquirido=?, velocidade=%d, ocorrencia=%d, tipo=%c;\n"), i, naves_defensoras[i].powerup[j].coord.x, naves_defensoras[i].powerup[j].coord.y, naves_defensoras[i].powerup[j].dimensao.altura, naves_defensoras[i].powerup[j].dimensao.largura, naves_defensoras[i].powerup[j].duracao, naves_defensoras[i].powerup[j].velocidade, naves_defensoras[i].powerup[j].ocorrencia, naves_defensoras[i].powerup[j].tipo);
}

void mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n# Mostra Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT("[Bomba]: id=%d, posição=(%d,%d), velocidade=%d;\n"), i, bombas[i].coord.x, bombas[i].coord.y, bombas[i].velocidade);
}

void mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n# Mostra Tiros:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("[Tiro]: id=%d, posição=(%d,%d), velocidade=%d;\n"), i, tiros[i].coord.x, tiros[i].coord.y, tiros[i].velocidade);
}

void mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n# Mostra PowerUps:\n"));
	int i;
	for (i = 0; i < NUM_POWERUP; i++)
		_tprintf(TEXT("[Nave->PowerUps]: id=%d, posição=(%d,%d), dimensao=(%d,%d), duracao=%d, adquirido=?, velocidade=%d, ocorrencia=%d, tipo=%c;\n"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].dimensao.altura, powerups[i].dimensao.largura, powerups[i].duracao, powerups[i].velocidade, powerups[i].ocorrencia, powerups[i].tipo);
}

void mostra_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT("\n# Mostra Pontuações:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT("[Tiro]: id=%d, pontos=%d, disparos=%d, invasoras=%d, vidas=%d, powerups=%d, colisões=%d;\n"), i, pontuacoes[i].pontos, pontuacoes[i].disparos, pontuacoes[i].invasoras, pontuacoes[i].vidas, pontuacoes[i].powerups, pontuacoes[i].powerups);
}

void mostra_obstaculos(Obstaculo *obstaculos) {
	_tprintf(TEXT("\n# Mostra Obstáculos:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT("[Nave]: id=%d, posição=(%d,%d), dimensao=(%d,%d), resistencia=%d;\n"), i, obstaculos[i].coord.x, obstaculos[i].coord.y, obstaculos[i].dimensao.altura, obstaculos[i].dimensao.largura, obstaculos[i].resistencia);
}

/*********** Fuções das Threads ***********/
DWORD __stdcall naves_invasoras(void *ptr) {
	NaveInvasora *naves_invasoras = (NaveInvasora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	/*int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].tamanho = 4 + (2 * i);
		naves_invasoras[i].coord.x = 3;
		naves_invasoras[i].coord.y = 3 * i;
	}*/
	return 0;
}

DWORD __stdcall naves_defensoras(void *ptr) {
	NaveDefensora *naves_defensoras = (NaveDefensora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Defensoras:\n"));
	/*int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].tamanho = 2 * i;
		naves_defensoras[i].coord.x = 23;
		naves_defensoras[i].coord.y = (COLUNAS / 2) + i + 4;
	}*/
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