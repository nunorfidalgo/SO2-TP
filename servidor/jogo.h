#pragma once

typedef struct {
	Posicao	nav_inv[NUM_NAV_INVASORAS];
	Posicao	nav_def[NUM_NAV_DEFENSORAS];
	Posicao	obstaculos[NUM_OBSTACULOS];
} PosicoesIniciais;

// inicia as vareaveis de jogo
void inicia_jogo(Jogo *jogo, BOOL debug);
void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init);
void inicia_naves_defensoras(NaveDefensora *naves_defensoras, PosicoesIniciais *pos_init);

void inicia_bombas(Bomba *bombas);
void inicia_tiros(Tiro *tiros);
void inicia_powerups(PowerUp *powerups);

void inicia_obstaculos(Obstaculo *obstaculos, PosicoesIniciais *pos_init);

void inicia_pontuacoes(Pontuacao *pontuacoes);

void mostra_posições_iniciais(PosicoesIniciais *pos_init);