#include "servidor.h"
#include "../dados.h"
#include "jogo.h"
#include "../utils.h"

// gotoxy( x     , y     );
// gotoxy(COLUNAS, LINHAS);

/**** Função de inicialização dos dados do jogo ****/
void inicia_jogo(Jogo *jogo, BOOL debug) {
	Posicao	posicoes_iniciais[TMP_POS] = { 0 };
	int pos = 0;
	_tprintf(TEXT("* Novo Jogo:\n"));
	if (debug == TRUE) _tprintf(TEXT("Número obectos em batalha: %d\n"), TMP_POS);

	pos = inicia_naves_invasoras(jogo->naves_invasoras, posicoes_iniciais, pos);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	pos = inicia_naves_defensoras(jogo->naves_defensoras, posicoes_iniciais, pos);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	//pos = inicia_bombas(jogo->bombas, posicoes_iniciais, pos);
	//if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	pos = inicia_tiros(jogo->tiros, posicoes_iniciais, pos);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	//pos = inicia_powerups(jogo->powerups, posicoes_iniciais, pos);
	//if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	pos = inicia_obstaculos(jogo->obstaculos, posicoes_iniciais, pos);
	if (debug == TRUE) _tprintf(TEXT("pos: %d\n"), pos);

	//inicia_pontuacoes(jogo->pontuacoes);
	if (debug == TRUE) mostra_posições_iniciais(posicoes_iniciais);
}

/**** Funções de mostrar os dados ****/
int inicia_naves_invasoras(NaveInvasora *naves_invasoras, Posicao *posicoes_iniciais, int pos) {
	_tprintf(TEXT(" - Inicia %d Naves Invasoras.\n"), NUM_NAV_INVASORAS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].resistencia = random_l_h(1, 9);
		naves_invasoras[i].velocidade = random_l_h(1, 9);
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_ZERO, COLUNAS);
				y = random_l_h(POS_ZERO, POS_Y_INICIAL);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
			}
		} while (pos_control == 0);
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

int inicia_naves_defensoras(NaveDefensora *naves_defensoras, Posicao *posicoes_iniciais, int pos) {
	_tprintf(TEXT(" - Inicia %d Naves Defensoras. \n"), NUM_NAV_DEFENSORAS);
	int i, j, u, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].vidas = random_l_h(1, 3);
		naves_defensoras[i].velocidade = random_l_h(1, 9);
		do {
			for (u = 0; u < TMP_POS; u++) {
				x = random_l_h(POS_ZERO, COLUNAS);
				y = random_l_h(POS_Y_LIMITE_NAV_DEF_MOV, POS_FIM_TAB_Y - 1);
				if (x != posicoes_iniciais[u].x && y != posicoes_iniciais[u].y)
					pos_control++;
			}
		} while (pos_control == 0);
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
			naves_defensoras[i].powerup[j].coord.x = random_l_h(POS_ZERO, COLUNAS);
			//naves_defensoras[i].powerup[j].coord.y = random_l_h(POS_ZERO, POS_Y_INICIAL);
			naves_defensoras[i].powerup[j].coord.y = POS_Y_INICIAL;
		}
	}
	return pos;
}
//
//int inicia_bombas(Bomba *bombas, Posicao *posicoes_iniciais, int pos) {
//	_tprintf(TEXT(" - Inicia %d Bombas.\n"), NUM_BOMBAS);
//	int i, j, x, y = POS_Y_INICIAL, pos_control = 0, conta = 0;
//	for (i = 0; i < NUM_BOMBAS; i++) {
//		do {
//			for (j = 0; j < TMP_POS; j++) {
//				x = random_l_h(POS_ZERO, COLUNAS);
//				//y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
//				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
//					pos_control++;
//			}
//		} while (pos_control == 0);
//		(posicoes_iniciais + pos)->x = x;
//		(posicoes_iniciais + pos)->y = y;
//		pos++;
//		bombas[i].coord.x = x;
//		bombas[i].coord.y = y;
//		bombas[i].velocidade = random_l_h(1, 10);
//	}
//	return pos;
//}

int inicia_tiros(Tiro *tiros, Posicao *posicoes_iniciais, int pos) {
	//_tprintf(TEXT(" - Inicia %d Tiros.\n"), NUM_TIROS);
	//int i, j, x = 0, y = POS_Y_INICIAL, pos_control = 0, conta = 0;
	//for (i = 0; i < NUM_TIROS; i++) {
	//	do {
	//		for (j = 0; j < TMP_POS; j++) {
	//			x = random_l_h(POS_ZERO, COLUNAS);
	//			//y = random_l_h(POS_INICIAL_TAB_X, POS_FINAL_TAB_Y);
	//			if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
	//				pos_control++;
	//		}
	//	} while (pos_control == 0);
	//	(posicoes_iniciais + pos)->x = x;
	//	(posicoes_iniciais + pos)->y = y;
	//	pos++;
	//	tiros[i].coord.x = x;
	//	tiros[i].coord.y = y;
	//	tiros[i].velocidade = random_l_h(1, 10);
	//}

	_tprintf(TEXT(" - Inicia %d Tiros.\n"), NUM_TIROS);
	int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = 0;
		tiros[i].coord.y = 0;
		tiros[i].tipo = '0';
		tiros[i].velocidade = 0;
	}
	return pos;
}
//
//int inicia_powerups(PowerUp *powerups, Posicao *posicoes_iniciais, int pos) {
//	_tprintf(TEXT(" - Inicia %d PowerUps.\n"), NUM_POWERUPS);
//	int i, j, x, y = POS_Y_INICIAL, pos_control = 0, conta = 0;
//	for (i = 0; i < NUM_POWERUPS; i++) {
//		powerups[i].duracao = random_l_h(1, 30); // entre 0 a 30s
//		//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
//		powerups[i].velocidade = random_l_h(1, 10);
//		powerups[i].ocorrencia = random_l_h(1, 3);
//		powerups[i].tipo = 'a';
//		powerups[i].dimensao.altura = random_l_h(1, 6);
//		powerups[i].dimensao.largura = random_l_h(1, 4);
//		do {
//			for (j = 0; j < TMP_POS; j++) {
//				x = random_l_h(POS_ZERO, COLUNAS);
//				//y = random_l_h(POS_ZERO, POS_FINAL_TAB_Y);
//				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
//					pos_control++;
//			}
//		} while (pos_control == 0);
//		(posicoes_iniciais + pos)->x = x;
//		(posicoes_iniciais + pos)->y = y;
//		pos++;
//		powerups[i].coord.x = x;
//		powerups[i].coord.y = y;
//	}
//	return pos;
//}

int inicia_obstaculos(Obstaculo *obstaculos, Posicao *posicoes_iniciais, int pos) {
	_tprintf(TEXT(" - Inicia %d Obstáculos.\n"), NUM_OBSTACULOS);
	int i, j, x, y, pos_control = 0, conta = 0;
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		obstaculos[i].resistencia = random_l_h(1, 10);
		obstaculos[i].dimensao.altura = random_l_h(1, 6);
		obstaculos[i].dimensao.largura = random_l_h(1, 4);
		do {
			for (j = 0; j < TMP_POS; j++) {
				x = random_l_h(POS_Y_INICIAL, COLUNAS);
				y = random_l_h(POS_Y_INICIAL, POS_Y_LIMITE_NAV_DEF_MOV - 1);
				if (x != posicoes_iniciais[j].x && y != posicoes_iniciais[j].y)
					pos_control++;
			}
		} while (pos_control == 0);
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
	_tprintf(TEXT(" - Mostra posições iniciais:\n"));
	int i;
	//#define TMP_POS (NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS)
	_tprintf(TEXT("NAV INV\n"));
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\nNAV DEF\n"));
	for (i = NUM_NAV_INVASORAS; i < NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\nBOMBAS\n"));
	for (i = NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS; i < NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\nTIROS\n"));
	for (i = NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS; i < NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\nPOWERUPS\n"));
	for (i = NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS; i < NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\nOBSTACULOS\n"));
	for (i = NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS; i < NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), posicoes_iniciais[i].x, posicoes_iniciais[i].y);
	}
	_tprintf(TEXT("\n"));
}



