#pragma once

// inicializa as variav�is de jogo
void inicia_jogo(Jogo *jogo);
//void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init);
void inicia_naves_invasoras(NaveInvasora *naves_invasoras, PosicoesIniciais *pos_init, Pontuacao *pontuacoes);
void inicia_naves_defensoras(NaveDefensora *naves_defensoras, PosicoesIniciais *pos_init);
void inicia_bombas(Bomba *bombas);
void inicia_tiros(Tiro *tiros);
void inicia_powerups(PowerUp *powerups);
void inicia_obstaculos(Obstaculo *obstaculos, PosicoesIniciais *pos_init);
void inicia_pontuacoes(Pontuacao *pontuacoes);

// Mostrar a informa��o dos dados de jogo
void mostra_naves_invasoras(NaveInvasora *naves_invasoras);
void mostra_naves_defensoras(NaveDefensora *naves_defensoras);
void mostra_bombas(Bomba *bombas);
void mostra_tiros(Tiro *tiros);
void mostra_powerups(PowerUp *powerups);
void mostra_obstaculos(Obstaculo *obstaculos);
void mostra_pontuacoes(Pontuacao *pontuacoes);
void mostra_posi��es_iniciais(PosicoesIniciais *pos_init);

// fun��es das Threads
DWORD __stdcall naves_invasoras(void *ptr);
DWORD __stdcall batalha(void *ptr);
DWORD __stdcall efeitos(void *ptr);

// fun��es das naves invasoras
void mover_naves_invasoras(Jogo *jogo);

// fun��es de batalha
void bombas(Jogo *jogo);
void tiros(Jogo *jogo);

// fun��es de efeitos
void powerups(Jogo *Jogo);