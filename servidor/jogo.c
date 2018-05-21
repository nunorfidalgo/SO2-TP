#include "../dados.h"
#include "jogo.h"
#include "utils.h"

// gotoxy( x     , y     );
// gotoxy(COLUNAS, LINHAS);

/**** Função de inicialização dos dados do jogo ****/
void inicia_jogo(Jogo *jogo, BOOL debug) {
	Posicao	posicoes_iniciais[TMP_POS] = { 0 };
	int pos = 0;
	_tprintf(TEXT("* Novo Jogo:\n"));
	if (debug == TRUE) _tprintf(TEXT("Número obectos em batalha: %d\n"), TMP_POS);
	pos = inicia_naves_invasoras(jogo->naves_invasoras, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	pos = inicia_naves_defensoras(jogo->naves_defensoras, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	pos = inicia_bombas(jogo->bombas, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	pos = inicia_tiros(jogo->tiros, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	pos = inicia_powerups(jogo->powerups, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	pos = inicia_obstaculos(jogo->obstaculos, posicoes_iniciais, pos, debug);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);
	inicia_pontuacoes(jogo->pontuacoes);
	if (debug == TRUE) mostra_posições_iniciais(posicoes_iniciais);
}

/**** Funções de mostrar os dados ****/
int inicia_naves_invasoras(NaveInvasora *naves_invasoras, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d Naves Invasoras.\n"), NUM_NAV_INVASORAS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].resistencia = random_l_h(1, 9);
		naves_invasoras[i].velocidade = random_l_h(1, 9);
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_INICIAL_NAV_INV_X, COLUNAS);
				y = random_l_h(POS_INICIAL_NAV_INV_X, POS_FINAL_NAV_INV_Y);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		naves_invasoras[i].coord.x = x;
		naves_invasoras[i].coord.y = y;
		naves_invasoras[i].dimensao.altura = random_l_h(1, 4);
		naves_invasoras[i].dimensao.largura = random_l_h(1, 4);
	}
	return pos;
}

int inicia_naves_defensoras(NaveDefensora *naves_defensoras, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d Naves Defensoras. \n"), NUM_NAV_DEFENSORAS);
	int i, j, u, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].vidas = random_l_h(1, 3);
		naves_defensoras[i].velocidade = random_l_h(1, 9);
		do {
			for (u = 0; u < TMP_POS; u++) {
				x = random_l_h(POS_INICIAL_NAV_DEF_X, COLUNAS);
				y = random_l_h(POS_INICIAL_NAV_DEF_X, POS_FINAL_NAV_DEF_Y);
				if (x != posicoes_iniciais[u].x && y != posicoes_iniciais[u].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		naves_defensoras[i].coord.x = x;
		naves_defensoras[i].coord.y = y;
		naves_defensoras[i].dimensao.altura = random_l_h(1, 4);
		naves_defensoras[i].dimensao.largura = random_l_h(1, 4);
		for (j = 0; j < NUM_POWERUPS_NAV_DEF; j++) {
			naves_defensoras[i].powerup[j].duracao = random_l_h(1, 30); // entre 0 a 30s
			//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
			naves_defensoras[i].powerup[j].velocidade = random_l_h(1, 10);
			naves_defensoras[i].powerup[j].ocorrencia = random_l_h(1, 3);
			naves_defensoras[i].powerup[j].tipo = 'a';
			naves_defensoras[i].powerup[j].dimensao.altura = random_l_h(1, 6);
			naves_defensoras[i].powerup[j].dimensao.largura = random_l_h(1, 4);
			naves_defensoras[i].powerup[j].coord.x = random_l_h(POS_INICIAL_TAB_X, COLUNAS);
			naves_defensoras[i].powerup[j].coord.y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
		}
	}
	return pos;
}

int inicia_bombas(Bomba *bombas, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d Bombas.\n"), NUM_BOMBAS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_BOMBAS; i++) {
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_INICIAL_TAB_X, COLUNAS);
				y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		bombas[i].coord.x = x;
		bombas[i].coord.y = y;
		bombas[i].velocidade = random_l_h(1, 10);
	}
	return pos;
}

int inicia_tiros(Tiro *tiros, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d Tiros.\n"), NUM_TIROS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_TIROS; i++) {
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_INICIAL_TAB_X, COLUNAS);
				y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		tiros[i].coord.x = x;
		tiros[i].coord.y = y;
		tiros[i].velocidade = random_l_h(1, 10);
	}
	return pos;
}

int inicia_powerups(PowerUp *powerups, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d PowerUps.\n"), NUM_POWERUPS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_POWERUPS; i++) {
		powerups[i].duracao = random_l_h(1, 30); // entre 0 a 30s
		//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
		powerups[i].velocidade = random_l_h(1, 10);
		powerups[i].ocorrencia = random_l_h(1, 3);
		powerups[i].tipo = 'a';
		powerups[i].dimensao.altura = random_l_h(1, 6);
		powerups[i].dimensao.largura = random_l_h(1, 4);
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_INICIAL_TAB_X, COLUNAS);
				y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		powerups[i].coord.x = x;
		powerups[i].coord.y = y;
	}
	return pos;
}

int inicia_obstaculos(Obstaculo *obstaculos, Posicao *posicoes_iniciais, int pos, BOOL debug) {
	_tprintf(TEXT(" - Inicia %d Obstáculos.\n"), NUM_OBSTACULOS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		obstaculos[i].resistencia = random_l_h(1, 10);
		obstaculos[i].dimensao.altura = random_l_h(1, 6);
		obstaculos[i].dimensao.largura = random_l_h(1, 4);
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_INICIAL_TAB_X, COLUNAS);
				y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
				else
					conta++;
			}
		} while (pos_control == 0);
		if (debug == TRUE) _tprintf(TEXT("conta=%d\n"), conta);
		(posicoes_iniciais + pos)->x = x;
		(posicoes_iniciais + pos)->y = y;
		pos++;
		obstaculos[i].coord.x = x;
		obstaculos[i].coord.y = y;
	}
	return pos;
}

void inicia_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT(" - Inicia Pontuações.\n"));
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

void mostra_posições_iniciais(Posicao *posicoes_iniciais) {
	_tprintf(TEXT(" - Mostra posições iniciais: \n"));
	int i;
	_tprintf(TEXT("pos ininicias:\n"));
	for (i = 0; i < TMP_POS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\n"));
}

/**** Fuções das Threads ****/
DWORD __stdcall naves_invasoras(void *ptr) {
	NaveInvasora *naves_invasoras = (NaveInvasora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	/*Sleep(10000);
	_tprintf(TEXT("Dormi 10 sec... fazer as naves inv mexer!!\n"));*/

	// gotoxy( x     , y     );
	// gotoxy(COLUNAS, LINHAS);

	int i;
	float xrand, yrand;
	while (1) {

		for (i = 0; i < NUM_NAV_INVASORAS; i++) {
			xrand = rand_01();
			yrand = rand_01();
			if (xrand < 0.5 && (naves_invasoras[i].coord.x > 0 || naves_invasoras[i].coord.x < COLUNAS))
				naves_invasoras[i].coord.x++;
			if (yrand < 0.5 && (naves_invasoras[i].coord.y > 0 || naves_invasoras[i].coord.y < POS_FINAL_NAV_DEF_Y))
				naves_invasoras[i].coord.y++;
		}

		Sleep(UM_SEC);
	}
	return 0;
}

DWORD __stdcall naves_defensoras(void *ptr) {
	NaveDefensora *naves_defensoras = (NaveDefensora *)ptr;
	_tprintf(TEXT("- Funcao da Thread Naves Defensoras:\n"));
	return 0;
}

DWORD __stdcall batalha(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Batalha:\n"));
	return 0;
}

DWORD __stdcall efeitos(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Efeitos:\n"));
	return 0;
}

