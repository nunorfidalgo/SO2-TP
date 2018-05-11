void inicia_jogo(Jogo *jogo);
void inicia_naves_invasoras(NaveInvasora *naves_invasoras);
void inicia_naves_defensoras(NaveDefensora *naves_defensoras);
void inicia_bombas(Bomba *bombas);
void inicia_tiros(Tiro *tiros);
void inicia_powerups(PowerUp *powerups);

void mostra_naves_invasoras(NaveInvasora *naves_invasoras);
void mostra_naves_defensoras(NaveDefensora *naves_defensoras);
void mostra_bombas(Bomba *bombas);
void mostra_tiros(Tiro *tiros);
void mostra_powerups(PowerUp *powerups);

// Funcões para as Threads
DWORD __stdcall naves_invasoras(void *ptr);
DWORD __stdcall naves_defensoras(void *ptr);
DWORD __stdcall batalha(void *ptr);
DWORD __stdcall efeitos(void *ptr);
DWORD __stdcall jogadores(void *ptr);