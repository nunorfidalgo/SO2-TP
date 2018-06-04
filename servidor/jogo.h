#pragma once

// inicia as vareaveis de jogo
void inicia_jogo(Jogo *jogo, BOOL debug);
int inicia_naves_invasoras(NaveInvasora *naves_invasoras, Posicao *posicoes_iniciais, int pos);
int inicia_naves_defensoras(NaveDefensora *naves_defensoras, Posicao *posicoes_iniciais, int pos);
//int inicia_bombas(Bomba *bombas, Posicao *posicoes_iniciais, int pos);
int inicia_tiros(Tiro *tiros, Posicao *posicoes_iniciais, int pos);
//int inicia_powerups(PowerUp *powerups, Posicao *posicoes_iniciais, int pos);
int inicia_obstaculos(Obstaculo *obstaculos, Posicao *posicoes_iniciais, int pos);
void inicia_pontuacoes(Pontuacao *pontuacoes);

void mostra_posições_iniciais(Posicao *posicoes_iniciais);

/*********** Fuções das Threads ***********/
//DWORD __stdcall naves_invasoras(void *ptr);
//DWORD __stdcall naves_defensoras(void *ptr);
//DWORD __stdcall batalha(void *ptr);
//DWORD __stdcall efeitos(void *ptr);
//DWORD __stdcall jogadores(void *ptr);