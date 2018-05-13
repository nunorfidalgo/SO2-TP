#pragma once

// inicia as vareaveis de jogo
void inicia_jogo(Jogo *jogo);
void inicia_naves_invasoras(NaveInvasora *naves_invasoras);
void inicia_naves_defensoras(NaveDefensora *naves_defensoras);
void inicia_bombas(Bomba *bombas);
void inicia_tiros(Tiro *tiros);
void inicia_powerups(PowerUp *powerups);
void inicia_pontuacoes(Pontuacao *pontuacoes);
void inicia_obstaculos(Obstaculo *obstaculos);

/*********** Fuções das Threads ***********/
DWORD __stdcall naves_invasoras(void *ptr);
DWORD __stdcall naves_defensoras(void *ptr);
DWORD __stdcall batalha(void *ptr);
DWORD __stdcall efeitos(void *ptr);
DWORD __stdcall jogadores(void *ptr);