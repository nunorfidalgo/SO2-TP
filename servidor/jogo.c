#include "servidor.h"
#include "../dados.h"
#include "jogo.h"
#include "../utils.h"

// gotoxy( x     , y     );
// gotoxy(COLUNAS, LINHAS);

/**** Função de inicialização dos dados do jogo ****/
void inicia_jogo(Jogo *jogo, BOOL debug) {
	PosicoesIniciais pos_init;
	_tprintf(TEXT("* Novo Jogo:\n"));

	inicia_naves_invasoras(jogo->naves_invasoras, &pos_init);
	inicia_naves_defensoras(jogo->naves_defensoras, &pos_init);
	inicia_obstaculos(jogo->obstaculos, &pos_init);

	inicia_bombas(jogo->bombas);
	inicia_tiros(jogo->tiros);
	inicia_powerups(jogo->powerups);
	inicia_pontuacoes(jogo->pontuacoes);

	if (debug == TRUE) mostra_posições_iniciais(&pos_init);
}

/**** Funções de mostrar os dados ****/
void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init) {
	_tprintf(TEXT(" - Inicia %d Naves Invasoras.\n"), NUM_NAV_INVASORAS);
	int i, j, xrand, yrand, pos_control = 0, conta = 0, pos = 0;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		naves_invasoras[i].resistencia = random_l_h(1, 10);
		naves_invasoras[i].velocidade = random_l_h(1, 10) * 100; // em MS
		naves_invasoras[i].tipo = '0';
		do {
			for (j = 0; j < TMP_POS; j++) {
				xrand = random_l_h(POS_ZERO, COLUNAS);
				yrand = random_l_h(POS_ZERO, POS_Y_INICIAL);
				if (xrand != pos_init->nav_inv[j].x && yrand != pos_init->nav_inv[j].y)
					pos_control++;
			}
		} while (pos_control == 0);
		(pos_init->nav_inv + pos)->x = xrand;
		(pos_init->nav_inv + pos)->y = yrand;
		pos++;
		naves_invasoras[i].coord.x = xrand;
		naves_invasoras[i].coord.y = yrand;
		naves_invasoras[i].dimensao.altura = 4; //random_l_h(1, 4);
		naves_invasoras[i].dimensao.largura = 4; //random_l_h(1, 4);
	}
}

void inicia_naves_defensoras(NaveDefensora *naves_defensoras, PosicoesIniciais *pos_init) {
	_tprintf(TEXT(" - Inicia %d Naves Defensoras. \n"), NUM_NAV_DEFENSORAS);
	int i, j, u, xrand, yrand, pos_control = 0, conta = 0, pos = 0;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		naves_defensoras[i].vidas = random_l_h(1, 3);
		naves_defensoras[i].velocidade = random_l_h(1, 9);
		do {
			for (u = 0; u < TMP_POS; u++) {
				xrand = random_l_h(POS_ZERO, COLUNAS);
				yrand = random_l_h(POS_Y_LIMITE_NAV_DEF_MOV, POS_FIM_TAB_Y - 1);
				if (xrand != pos_init->nav_def[u].x && yrand != pos_init->nav_def[u].y)
					pos_control++;
			}
		} while (pos_control == 0);
		(pos_init->nav_inv + pos)->x = xrand;
		(pos_init->nav_inv + pos)->y = yrand;
		pos++;
		naves_defensoras[i].coord.x = xrand;
		naves_defensoras[i].coord.y = yrand;
		naves_defensoras[i].dimensao.altura = random_l_h(1, 4);
		naves_defensoras[i].dimensao.largura = random_l_h(1, 4);
		for (j = 0; j < NUM_POWERUPS_NAV_DEF; j++) {
			naves_defensoras[i].powerup[j].duracao = 0; // random_l_h(1, 30); // entre 0 a 30s
			//naves_defensoras[i].powerup[j].adquirido = SYSTEMTIME??
			naves_defensoras[i].powerup[j].velocidade = 0; // random_l_h(1, 10);
			naves_defensoras[i].powerup[j].ocorrencia = 0; // random_l_h(1, 3);
			naves_defensoras[i].powerup[j].tipo = '0';
			naves_defensoras[i].powerup[j].dimensao.altura = 0; // random_l_h(1, 6);
			naves_defensoras[i].powerup[j].dimensao.largura = 0; // random_l_h(1, 4);
			naves_defensoras[i].powerup[j].coord.x = 0; // random_l_h(POS_ZERO, COLUNAS);
			//naves_defensoras[i].powerup[j].coord.y = random_l_h(POS_ZERO, POS_Y_INICIAL);
			naves_defensoras[i].powerup[j].coord.y = 0;  random_l_h(POS_ZERO, POS_Y_INICIAL);
			naves_defensoras[i].powerup[j].coord.y = 0; // POS_Y_INICIAL;
		}
	}
}

void inicia_bombas(Bomba *bombas) {
	_tprintf(TEXT(" - Inicia %d Bombas.\n"), NUM_BOMBAS);
	int i;
	for (i = 0; i < NUM_BOMBAS; i++) {
		bombas[i].coord.x = 0;
		bombas[i].coord.y = 0;
		bombas[i].velocidade = 0;
	}
}

void inicia_tiros(Tiro *tiros) {
	_tprintf(TEXT(" - Inicia %d Tiros.\n"), NUM_TIROS);
	int i;
	for (i = 0; i < NUM_TIROS; i++) {
		tiros[i].coord.x = 0;
		tiros[i].coord.y = 0;
		tiros[i].velocidade = 0;
	}
}

void inicia_powerups(PowerUp *powerups) {
	_tprintf(TEXT(" - Inicia %d PowerUps.\n"), NUM_POWERUPS);
	int i;
	for (i = 0; i < NUM_POWERUPS; i++) {
		//powerups[i].adquirido = NULL;
		powerups[i].coord.x = 0;
		powerups[i].coord.y = 0;
		powerups[i].dimensao.altura = 0;
		powerups[i].dimensao.largura = 0;
		powerups[i].duracao = 0;
		powerups[i].ocorrencia = 0;
		powerups[i].tipo = '0';
		powerups[i].velocidade = 0;
	}
}

void inicia_obstaculos(Obstaculo *obstaculos, PosicoesIniciais *pos_init) {
	_tprintf(TEXT(" - Inicia %d Obstáculos.\n"), NUM_OBSTACULOS);
	int i, j, xrand, yrand, pos_control = 0, conta = 0, pos = 0;
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		obstaculos[i].resistencia = 1; // random_l_h(1, 10);
		obstaculos[i].dimensao.altura = random_l_h(1, 6);
		obstaculos[i].dimensao.largura = random_l_h(1, 4);
		do {
			for (j = 0; j < TMP_POS; j++) {
				xrand = random_l_h(POS_Y_INICIAL, COLUNAS);
				yrand = random_l_h(POS_Y_INICIAL, POS_Y_LIMITE_NAV_DEF_MOV - 1);
				if (xrand != pos_init->obstaculos[j].x && yrand != pos_init->obstaculos[j].y)
					pos_control++;
			}
		} while (pos_control == 0);
		(pos_init->obstaculos + pos)->x = xrand;
		(pos_init->obstaculos + pos)->y = yrand;
		pos++;
		obstaculos[i].coord.x = xrand;
		obstaculos[i].coord.y = yrand;
	}
}

void inicia_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT(" - Inicia Pontuações.\n"));
	int i;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		pontuacoes[i].nav_inv = NUM_NAV_INVASORAS;
		pontuacoes[i].nav_def = NUM_NAV_DEFENSORAS;
		pontuacoes[i].bombas = 0;
		pontuacoes[i].tiros = 0;
		pontuacoes[i].powerups = 0;
		pontuacoes[i].obstaculos = NUM_OBSTACULOS;
	}
}

void mostra_posições_iniciais(PosicoesIniciais *pos_init) {
	_tprintf(TEXT(" - Mostra posições iniciais:\n"));
	int i;
	//#define TMP_POS (NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS)
	_tprintf(TEXT("NAV INV\n"));
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), pos_init->nav_inv[i].x, pos_init->nav_inv[i].y);
	}
	_tprintf(TEXT("\nNAV DEF\n"));
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), pos_init->nav_def[i].x, pos_init->nav_def[i].y);
	}
	_tprintf(TEXT("\nOBSTACULOS\n"));
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		_tprintf(TEXT("(%02d, %02d), "), pos_init->obstaculos[i].x, pos_init->obstaculos[i].y);
	}
	_tprintf(TEXT("\n"));
}