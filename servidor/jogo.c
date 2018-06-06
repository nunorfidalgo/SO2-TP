#include "servidor.h"
#include "../bridge/bridge.h"
#include "../utils.h"
#include "jogo.h"

// variavel global -> ver em servidor.h
int pos_bombas = 0;

/**** Função de inicialização dos dados do jogo  ***********************************************/
void inicia_jogo(Jogo *jogo) {
	_tprintf(TEXT("* Novo Jogo:\n"));

	PosicoesIniciais pos_init;

	inicia_naves_invasoras(jogo->naves_invasoras, &pos_init, jogo->pontuacoes);
	inicia_naves_defensoras(jogo->naves_defensoras, &pos_init);
	inicia_obstaculos(jogo->obstaculos, &pos_init);

	inicia_bombas(jogo->bombas);
	inicia_tiros(jogo->tiros);
	inicia_powerups(jogo->powerups);
	inicia_pontuacoes(jogo->pontuacoes);

	if (DEBUG == TRUE) mostra_posições_iniciais(&pos_init);
}

/**** Funções de mostrar os dados ****/
//void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init) {
//void inicia_naves_invasoras(Jogo *jogo, PosicoesIniciais *pos_init) {
void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init, Pontuacao *pontuacoes) {
	_tprintf(TEXT(" - Inicia %d Naves Invasoras.\n"), NUM_NAV_INVASORAS);
	int i, j, xrand, yrand, pos_control = 0, conta = 0, pos = 0;
	float nrand;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {

		// b-> basica, e->esquiva,  i-> invasivo
		nrand = rand_01();
		//if (DEBUG == TRUE) _tprintf(TEXT("nrand=%0.2f;\n"), nrand);
		if (nrand <= PROB_NAV_INV_INVASIVA) {
			naves_invasoras[i].tipo = 'i';
			naves_invasoras[i].direcao = '0';
			naves_invasoras[i].resistencia = 8; // random_l_h(4, 10);
			naves_invasoras[i].velocidade = 200; // random_l_h(1, 10) * 100; // em MS
			naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_INVASIVAS;
			pontuacoes->nav_inv_i++;
		}
		else if (nrand <= PROB_NAV_INV_ESQUIVA) {
			naves_invasoras[i].tipo = 'e';
			naves_invasoras[i].direcao = '0';
			naves_invasoras[i].resistencia = 3; // random_l_h(4, 10);
			naves_invasoras[i].velocidade = 800; // random_l_h(1, 10) * 100; // em MS
			naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_ESQUIVAS;
			pontuacoes->nav_inv_e++;
		}
		else {
			naves_invasoras[i].tipo = 'b';
			naves_invasoras[i].direcao = 'd'; // d->direita, e->esquerda
			naves_invasoras[i].resistencia = 1; // random_l_h(4, 10);
			naves_invasoras[i].velocidade = 1000; // random_l_h(1, 10) * 100; // em MS
			naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_BASICAS;
			pontuacoes->nav_inv_b++;
		}
		do {
			for (j = 0; j < NUM_NAV_INVASORAS; j++) {
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
			for (u = 0; u < NUM_NAV_DEFENSORAS; u++) {
				xrand = random_l_h(POS_ZERO, COLUNAS);
				yrand = random_l_h(POS_Y_LIMITE_NAV_DEF_MOV, POS_FIM_TAB_Y - 1);
				if (xrand != pos_init->nav_def[u].x && yrand != pos_init->nav_def[u].y)
					pos_control++;
			}
		} while (pos_control == 0);
		(pos_init->nav_def + pos)->x = xrand;
		(pos_init->nav_def + pos)->y = yrand;
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
		obstaculos[i].resistencia = 2; // random_l_h(1, 10);
		obstaculos[i].dimensao.altura = random_l_h(1, 6);
		obstaculos[i].dimensao.largura = random_l_h(1, 4);
		do {
			for (j = 0; j < NUM_OBSTACULOS; j++) {
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

/**** Mostrar a informação dos dados de jogo  ***********************************************/
void mostra_naves_invasoras(NaveInvasora *naves_invasoras) {
	_tprintf(TEXT("\n# Mostra Naves Invasoras:\n"));
	int i;
	for (i = 0; i < NUM_NAV_INVASORAS; i++)
		_tprintf(TEXT(" - Nave[%d]: posição=(%2d,%2d), tipo=%c, taxa_disparo=%d, dimensão=(%2d,%2d), resistencia=%d, velocidade=%d, direcao=%c;\n"),
			i, naves_invasoras[i].coord.x, naves_invasoras[i].coord.y, naves_invasoras[i].tipo, naves_invasoras[i].taxa_disparo, naves_invasoras[i].dimensao.altura, naves_invasoras[i].dimensao.largura, naves_invasoras[i].resistencia, naves_invasoras[i].velocidade, naves_invasoras[i].direcao);
}

void mostra_naves_defensoras(NaveDefensora *naves_defensoras) {
	_tprintf(TEXT("\n# Mostra Naves Defensoras:\n"));
	int i, j;
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT(" - Nave[%d]: posição=(%2d,%2d), dimensão=(%2d,%2d), vidas=%d, velocidade=%d\n"), i, naves_defensoras[i].coord.x, naves_defensoras[i].coord.y, naves_defensoras[i].dimensao.altura, naves_defensoras[i].dimensao.largura, naves_defensoras[i].vidas, naves_defensoras[i].velocidade);
		for (j = 0; j < NUM_POWERUPS_NAV_DEF; j++) {
			_tprintf(TEXT(" - Nave[%d]->PowerUps[%d]: posição=(%2d,%2d), dimensão=(%2d,%2d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, j, naves_defensoras[i].powerup[j].coord.x, naves_defensoras[i].powerup[j].coord.y, naves_defensoras[i].powerup[j].dimensao.altura, naves_defensoras[i].powerup[j].dimensao.largura, naves_defensoras[i].powerup[j].duracao, naves_defensoras[i].powerup[j].velocidade, naves_defensoras[i].powerup[j].ocorrencia, naves_defensoras[i].powerup[j].tipo);
		}
	}
}

void mostra_bombas(Bomba *bombas) {
	_tprintf(TEXT("\n# Mostra Bombas:\n"));
	int i;
	for (i = 0; i < NUM_BOMBAS; i++)
		_tprintf(TEXT(" - Bomba[%d]: posição=(%2d,%2d), velocidade=%d;\n"), i, bombas[i].coord.x, bombas[i].coord.y, bombas[i].velocidade);
}

void mostra_tiros(Tiro *tiros) {
	_tprintf(TEXT("\n# Mostra Tiros:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		_tprintf(TEXT(" - Tiro[%d]: posição=(%2d,%2d), velocidade=%d;\n"), i, tiros[i].coord.x, tiros[i].coord.y, tiros[i].velocidade);
}

void mostra_powerups(PowerUp *powerups) {
	_tprintf(TEXT("\n# Mostra PowerUps:\n"));
	int i;
	for (i = 0; i < NUM_POWERUPS; i++)
		_tprintf(TEXT(" - PowerUps[%d]: posição=(%2d,%2d), dimensão=(%2d,%2d), duração=%d, adquirido=?, velocidade=%d, ocorrência=%d, tipo=%c;\n"), i, powerups[i].coord.x, powerups[i].coord.y, powerups[i].dimensao.altura, powerups[i].dimensao.largura, powerups[i].duracao, powerups[i].velocidade, powerups[i].ocorrencia, powerups[i].tipo);
}

void mostra_obstaculos(Obstaculo *obstaculos) {
	_tprintf(TEXT("\n# Mostra Obstáculos:\n"));
	int i;
	for (i = 0; i < NUM_OBSTACULOS; i++)
		_tprintf(TEXT(" - Obstáculo[%d]: posição=(%2d,%2d), resistência=%d, dimensão=(%2d,%2d);\n"), i, obstaculos[i].coord.x, obstaculos[i].coord.y, obstaculos[i].resistencia, obstaculos[i].dimensao.altura, obstaculos[i].dimensao.largura);
}

void mostra_pontuacoes(Pontuacao *pontuacoes) {
	_tprintf(TEXT("\n# Mostra Pontuações:\n"));
	int i;
	for (i = 0; i < NUM_TIROS; i++)
		/*_tprintf(TEXT(" - Pontuação[%d]: pontos=%d, disparos=%d, invasoras=%d, vidas=%d, powerups=%d, colisões=%d;\n"), i, pontuacoes[i].pontos, pontuacoes[i].disparos, pontuacoes[i].invasoras, pontuacoes[i].vidas, pontuacoes[i].powerups, pontuacoes[i].powerups);*/
		_tprintf(TEXT(" - Pontuação[%d]: nav_inv=%d, nav_def=%d, bombas[%d]: tiros=%d, powerups=%d, obstáculos=%d;\n"), i, pontuacoes[i].nav_inv, pontuacoes[i].nav_def, pontuacoes[i].bombas, pontuacoes[i].tiros, pontuacoes[i].powerups, pontuacoes[i].obstaculos);
}

void mostra_posições_iniciais(PosicoesIniciais *pos_init) {
	_tprintf(TEXT("\n* Mostra posições iniciais:\n"));
	int i;
	//#define TMP_POS (NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS)
	_tprintf(TEXT(" - Naves Invasoras: "));
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		_tprintf(TEXT("(%02d,%02d), "), pos_init->nav_inv[i].x, pos_init->nav_inv[i].y);
	}
	_tprintf(TEXT("\n"));
	_tprintf(TEXT(" - Naves Defensoras: "));
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		_tprintf(TEXT("(%02d,%02d), "), pos_init->nav_def[i].x, pos_init->nav_def[i].y);
	}
	_tprintf(TEXT("\n"));
	_tprintf(TEXT(" - Obstáculos: "));
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		_tprintf(TEXT("(%02d,%02d), "), pos_init->obstaculos[i].x, pos_init->obstaculos[i].y);
	}
	_tprintf(TEXT("\n"));
}

/**** Fuções das Threads ************************************************************************************************************/
DWORD __stdcall naves_invasoras(void *ptr) {
	if (DEBUG == TRUE) _tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	Jogo *jogo = (Jogo *)ptr;
	int counter = 0;
	while (1) {

		//if (DEBUG == TRUE) _tprintf(TEXT("\nThread Naves Invasoras-----------------------------------------------------------------------------------------\n"));
		//WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		counter++;
		//if (DEBUG == TRUE) _tprintf(TEXT("counter=%d;\n"), counter);

		mover_naves_invasoras(jogo);

		if (DEBUG == TRUE) mostra_naves_invasoras(jogo->naves_invasoras);

		ReleaseMutex(MutexJogo);

		//Sleep(VEL_200MS);
		//Sleep(VEL_500MS);
		Sleep(VEL_UM_SEC);

		//ReleaseSemaphore(SemLerJogo, 1, NULL);
	}
	return 0;
}

DWORD __stdcall batalha(void *ptr) {
	if (DEBUG == TRUE) _tprintf(TEXT("- Funcao da Thread Batalha:\n"));
	Jogo *jogo = (Jogo *)ptr;
	while (1) {

		// if (DEBUG == TRUE) _tprintf(TEXT("\nThread Batalha-----------------------------------------------------------------------------------------\n"));

		//WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		// verificar as naves inv/def para terminar o jogo

		// bombas
		bombas(jogo);

		// tiros
		tiros(jogo);

		//if (DEBUG == TRUE) _tprintf(TEXT("POS_Y_LIMITE_NAV_DEF_MOV: %d\n"), POS_Y_LIMITE_NAV_DEF_MOV);
		// if (DEBUG == TRUE) mostra_naves_defensoras(jogo->naves_defensoras);
		if (DEBUG == TRUE) mostra_bombas(jogo->bombas);
		// if (DEBUG == TRUE) mostra_tiros(jogo->tiros);
		//if (DEBUG == TRUE) mostra_obstaculos(jogo->obstaculos);

		ReleaseMutex(MutexJogo);

		//Sleep(VEL_500MS);
		Sleep(VEL_UM_SEC);

		//ReleaseSemaphore(SemLerJogo, 1, NULL);
	}
	return 0;
}

// thread para gerir os efeitos do powerups
DWORD __stdcall efeitos(void *ptr) {
	//if (DEBUG == TRUE) _tprintf(TEXT("- Funcao da Thread Efeitos:\n"));
	Jogo *jogo = (Jogo *)ptr;
	// gerir obstaculos... os tiros tiram a resistencia
	// gerir powerups
	//int i, t;
	//while (1) {
	//	//if (DEBUG == TRUE) _tprintf(TEXT("\nThread Efeitos-----------------------------------------------------------------------------------------\n"));
	//	//WaitForSingleObject(SemEscreveJogo, INFINITE);
	//	WaitForSingleObject(MutexJogo, INFINITE);

	//	// powerups
	// powerups(jogo);

	//	//if (DEBUG == TRUE) mostra_powerups(jogo->powerups);
	//

	//	ReleaseMutex(MutexJogo);
	//	//Sleep(VEL_200MS);
	//	Sleep(VEL_UM_SEC);
	//	//ReleaseSemaphore(SemLerJogo, 1, NULL);
	//}
	return 0;
}

/**** Funções de batalha ***********************************************/
void mover_naves_invasoras(Jogo *jogo) {
	int i, j;
	float xrand, yrand;
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {

		/*	if (jogo->naves_invasoras[i].coord.y >= POS_Y_LIMITE_NAV_DEF_MOV) {
		_tprintf(TEXT("\n\nFIM!! Invasores vencem!\n"));
		_gettch();
		exit(1);
		}*/

		// nave invasora basica
		if (jogo->naves_invasoras[i].tipo == 'b') {
			// andar para a direita
			if (jogo->naves_invasoras[i].direcao == 'd') {
				if (jogo->naves_invasoras[i].coord.x < COLUNAS - 1) {
					jogo->naves_invasoras[i].coord.x++;
				}
				else {
					jogo->naves_invasoras[i].coord.y++;
					jogo->naves_invasoras[i].direcao = 'e';
				}
			}
			else if (jogo->naves_invasoras[i].direcao == 'e') {
				if (jogo->naves_invasoras[i].coord.x > POS_ZERO) {
					jogo->naves_invasoras[i].coord.x--;
				}
				else {
					jogo->naves_invasoras[i].coord.y++;
					jogo->naves_invasoras[i].direcao = 'd';
				}
			}
		}

		// nave invasora esquiva
		if (jogo->naves_invasoras[i].tipo == 'e') {
			xrand = rand_01();
			yrand = rand_01();
			//if (DEBUG == TRUE) _tprintf(TEXT("xrand=%0.2f, yrand=%0.2f;\n"), xrand, yrand);

			// andar para cima e para baixa 
			if (yrand <= PROB_LADOS) { // este prob é de 50%, não vale a pena estar a criar outro define
				if (jogo->naves_invasoras[i].coord.y < POS_Y_LIMITE_NAV_DEF_MOV) {
					jogo->naves_invasoras[i].coord.y++;
				}
			}
			else {
				if (jogo->naves_invasoras[i].coord.y > POS_ZERO) {
					jogo->naves_invasoras[i].coord.y--;
					//if (DEBUG == TRUE) _tprintf(TEXT("nave desce!!\n"));
				}
			}

			// andar para os lados
			if (xrand <= PROB_LADOS) {
				if (jogo->naves_invasoras[i].coord.x < COLUNAS - 1) {
					jogo->naves_invasoras[i].coord.x++;
				}
			}
			else {
				if (jogo->naves_invasoras[i].coord.x > POS_ZERO) {
					jogo->naves_invasoras[i].coord.x--;
				}
			}
		}

		// nave invasora invasiva
		if (jogo->naves_invasoras[i].tipo == 'i') {
			xrand = rand_01();
			yrand = rand_01();
			//if (DEBUG == TRUE) _tprintf(TEXT("xrand=%0.2f, yrand=%0.2f;\n"), xrand, yrand);
			// descer
			if (yrand <= PROB_DESCER) {
				if (jogo->naves_invasoras[i].coord.y < POS_Y_LIMITE_NAV_DEF_MOV) {
					jogo->naves_invasoras[i].coord.y++;
					//if (DEBUG == TRUE) _tprintf(TEXT("nave desce!!\n"));
				}
			}
			// andar para os lados
			if (xrand <= PROB_LADOS) {
				if (jogo->naves_invasoras[i].coord.x < COLUNAS - 1) {
					jogo->naves_invasoras[i].coord.x++;
					//if (DEBUG == TRUE) _tprintf(TEXT("nave dir!!\n"));
				}
			}
			else {
				if (jogo->naves_invasoras[i].coord.x > POS_ZERO) {
					jogo->naves_invasoras[i].coord.x--;
					//if (DEBUG == TRUE) _tprintf(TEXT("nave esq!!\n"));
				}
			}
		}

		// disparar bombas
		if (jogo->naves_invasoras[i].taxa_disparo <= 0) {
			for (j = 0; j < NUM_BOMBAS; j++) {
				if (jogo->bombas[j].velocidade == 0) {
					pos_bombas = j;
					break;
				}
			}
			jogo->bombas[pos_bombas].coord.x = jogo->naves_invasoras[i].coord.x;
			jogo->bombas[pos_bombas].coord.y = jogo->naves_invasoras[i].coord.y;
			jogo->bombas[pos_bombas].velocidade = 1; //random_l_h(1, 10);
			jogo->pontuacoes->bombas++;

			if (jogo->naves_invasoras[i].tipo == 'b')
				jogo->naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_BASICAS;
			if (jogo->naves_invasoras[i].tipo == 'e')
				jogo->naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_ESQUIVAS;
			if (jogo->naves_invasoras[i].tipo == 'i')
				jogo->naves_invasoras[i].taxa_disparo = TAXA_DISPARO_NAV_INVASIVAS;
		}

		// a cada movimento decresce a taxa de disparo
		jogo->naves_invasoras[i].taxa_disparo--;
	}
}

/**** Funções de batalha ***********************************************/
void bombas(Jogo *jogo) {
	int i, n;
	for (i = 0; i < NUM_BOMBAS; i++) {
		//for (n = 0; n < NUM_NAV_INVASORAS; n++) {
		if (jogo->bombas[i].velocidade != 0) {
			jogo->bombas[i].coord.y++;
			if (jogo->bombas[i].coord.y >= POS_FIM_TAB_Y) { // bomba desaparece
				jogo->bombas[i].velocidade = 0;
				jogo->bombas[i].coord.y = 0;
				jogo->bombas[i].coord.x = 0;
			}
		}
		//}
	}
}

void tiros(Jogo *jogo) {
	int i, t, o;
	for (t = 0; t < NUM_TIROS; t++) {
		if (jogo->tiros[t].velocidade != 0) {
			jogo->tiros[t].coord.y--;
			// obstaculos
			for (o = 0; o < NUM_OBSTACULOS; o++) {
				if (jogo->obstaculos[o].resistencia > 0) {
					if (jogo->obstaculos[o].coord.x == jogo->tiros[t].coord.x && jogo->obstaculos[o].coord.y == jogo->tiros[t].coord.y) {
						jogo->obstaculos[o].resistencia--;
						jogo->tiros[t].velocidade = 0;
						jogo->tiros[t].coord.y = 0;
						jogo->tiros[t].coord.x = 0;
						if (jogo->obstaculos[o].resistencia <= 0) {
							jogo->obstaculos[o].coord.x = 0;
							jogo->obstaculos[o].coord.y = 0;
							jogo->obstaculos[o].dimensao.altura = 0;
							jogo->obstaculos[o].dimensao.largura = 0;
							jogo->pontuacoes->obstaculos--;
						}
					}
				}

			}
			// naves invasoras
			for (i = 0; i < NUM_NAV_INVASORAS; i++) {
				if (jogo->naves_invasoras[i].resistencia > 0) {
					if (jogo->naves_invasoras[i].coord.x == jogo->tiros[t].coord.x && jogo->naves_invasoras[i].coord.y == jogo->tiros[t].coord.y) {
						jogo->naves_invasoras[i].resistencia--;
						jogo->tiros[t].velocidade = 0;
						jogo->tiros[t].coord.y = 0;
						jogo->tiros[t].coord.x = 0;
						if (jogo->naves_invasoras[i].resistencia <= 0) {
							jogo->naves_invasoras[i].coord.x = 0;
							jogo->naves_invasoras[i].coord.y = 0;
							jogo->naves_invasoras[i].dimensao.altura = 0;
							jogo->naves_invasoras[i].dimensao.largura = 0;
							jogo->pontuacoes->nav_inv--;
						}
					}
				}
			}
			if (jogo->tiros[t].coord.y <= POS_ZERO) { // tiro desaparece
				jogo->tiros[t].velocidade = 0;
				jogo->tiros[t].coord.y = 0;
				jogo->tiros[t].coord.x = 0;
			}
		}
	}
}

/**** Funções de efeitos ***********************************************/
void powerups(Jogo *Jogo) {

}