#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"
#include "../utils.h"

// funções das Threads
DWORD __stdcall jogadores(void *ptr);

void mostra_jogo_consola(Jogo *jogo);

// Variáveis globais
BOOL	DEBUG = FALSE;
HANDLE	MutexJogo;
HANDLE	SemLerJogo, SemEscreveJogo;
TCHAR	NomeSemaforoPodeEscrever[] = TEXT("Escrever no semáforo");
TCHAR	NomeSemaforoPodeLer[] = TEXT("Ler do semáforo");
int		input, i, j, pos_tiros = 0;

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis locais
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;
	HANDLE			ThreatJogadores;
	DWORD			IdJogadores;

	if (argc > 1 && _tcscmp(argv[1], TEXT("?")) == 0) {
		_tprintf(TEXT("%s '?' -> mostra esta ajuda;\n"), argv[0]);
		_tprintf(TEXT("%s 'debug' -> mostra os dados de jogo e avisos;\n"), argv[0]);
		exit(0);
	}

	MutexJogo = CreateMutex(NULL, FALSE, (LPCWSTR) "MutexJogo");
	if (MutexJogo == NULL) {
		_tprintf(TEXT("MutexJogo error: %d\n"), GetLastError());
		exit(1);
	}

	jogo = AcedeMemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo); // -mudar isto para o gateway nao estar a correr sem o servidor !!!!!

	SemEscreveJogo = CreateSemaphore(NULL, SEMAFORO_JOGO_NUM_ACCOES, SEMAFORO_JOGO_NUM_ACCOES, NomeSemaforoPodeEscrever);
	SemLerJogo = CreateSemaphore(NULL, 0, SEMAFORO_JOGO_NUM_ACCOES, NomeSemaforoPodeLer);

	if (SemEscreveJogo == NULL || SemLerJogo == NULL) {
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
		exit(1);
	}

	_tprintf(TEXT("\n** Ligação estabelecida ao servidor...\n"));

	// Threat Jogadores
	ThreatJogadores = CreateThread(NULL, 0, jogadores, (LPVOID)jogo, 0, &IdJogadores); // jogo->clientes add cliente to dados
	if (ThreatJogadores != NULL) {
		_tprintf(TEXT("[Thread Jogadores] id=%d;\n"), IdJogadores);
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread de Jogadores! (código=%d)\n"), GetLastError());
		exit(1);
	}

	WaitForSingleObject(ThreatJogadores, INFINITE);
	CloseHandle(MutexJogo);

	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nterminou...\n"));
	return 0;
}

DWORD __stdcall jogadores(void *ptr) {
	_tprintf(TEXT("- Funcao da Thread Jogadores:\n"));
	Jogo *jogo = (Jogo *)ptr;

	while (1) {
		//WaitForSingleObject(SemLerJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		system("cls");
		mostra_jogo_consola(jogo);

		//Sleep(VEL_MEIO_SEC);
		gotoxy(17, 25); // prompt

		//_tprintf(TEXT("[Erro](%d)\n"), GetLastError());
		/*if (jogo == NULL)
			_tprintf(TEXT("[Erro](%d)\n"), GetLastError());*/

			/*input = _gettch();
			input = toupper(input);*/
		input = 0;

		if (input == 27) // sair com ESC
			exit(1);

		// movimento da naves defensoras
		if (input == 80) { // CIMA
			for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
				if (jogo->naves_defensoras[i].coord.y < POS_FIM_TAB_Y - 1)
					jogo->naves_defensoras[i].coord.y++;
			}
		}
		if (input == 72) { // BAIXO
			for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
				if (jogo->naves_defensoras[i].coord.y > POS_Y_LIMITE_NAV_DEF_MOV)
					jogo->naves_defensoras[i].coord.y--;
			}
		}
		if (input == 77) { // DIR
			for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
				if (jogo->naves_defensoras[i].coord.x < COLUNAS - 1)
					jogo->naves_defensoras[i].coord.x++;
			}
		}
		if (input == 75) { // ESQ
			for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
				if (jogo->naves_defensoras[i].coord.x > POS_ZERO)
					jogo->naves_defensoras[i].coord.x--;
			}
		}

		if (input == 32) { // Tiro naves defensoras
			for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
				for (j = 0; j < NUM_TIROS; j++) {
					if (jogo->tiros[j].velocidade == 0) {
						pos_tiros = j;
						break;
					}
				}
				jogo->tiros[pos_tiros].coord.x = jogo->naves_defensoras[i].coord.x;
				jogo->tiros[pos_tiros].coord.y = jogo->naves_defensoras[i].coord.y;
				jogo->tiros[pos_tiros].velocidade = random_l_h(1, 10);
				jogo->pontuacoes->tiros++;
			}
		}

		//if (input == '')
		//if (input == '')
		//if (input == '')
		//if (input == '')
		//_tprintf(TEXT("%d"), input);

		_flushall();

		ReleaseMutex(MutexJogo);
		Sleep(VEL_UM_SEC);
		//ReleaseSemaphore(SemEscreveJogo, 1, NULL);
	}
	return 0;
}

void mostra_jogo_consola(Jogo *jogo) {
	int i;
	// Limites jogo
	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_Y_INICIAL);
		_tprintf(TEXT("-"));
	}
	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_Y_LIMITE_NAV_DEF_MOV);
		_tprintf(TEXT("-"));
	}
	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_FIM_TAB_Y);
		_tprintf(TEXT("-"));
	}
	for (i = 0; i < COLUNAS; i++) {
		gotoxy(i, POS_FIM_Y);
		_tprintf(TEXT("-"));
	}
	for (i = 0; i < LINHAS + 2; i++) {
		gotoxy(COLUNAS, i);
		_tprintf(TEXT("|"));
	}
	gotoxy(POS_ZERO, POS_FIM_TAB_Y);
	_tprintf(TEXT("Mensagens:\n"));
	gotoxy(POS_ZERO, POS_ENVIAR_MSGS);
	_tprintf(TEXT("Enviar mensagem: \n"));
	gotoxy(82, 0);
	_tprintf(TEXT("* Phoenix (multiplayer)"));
	gotoxy(82, 2);
	_tprintf(TEXT("* Teclas:"));
	gotoxy(82, 3);
	_tprintf(TEXT(" - Setas CIMA, BAIXO, DIR, ESQ:"));
	gotoxy(82, 4);
	_tprintf(TEXT("   movimentos nave defensora"));
	gotoxy(82, 5);
	_tprintf(TEXT(" - SPACE: dispara 'tiro(s)'"));
	gotoxy(82, 6);
	_tprintf(TEXT(" - ENTER: dispara 'bomba'"));
	gotoxy(82, 7);
	_tprintf(TEXT(" - M: escreve 'mensagem'"));
	gotoxy(82, 8);
	_tprintf(TEXT(" - ESC: sair"));
	gotoxy(82, 10);
	_tprintf(TEXT("* Pontuações:"));
	gotoxy(82, 11);
	_tprintf(TEXT(" - Nav Inv: %d"), jogo->pontuacoes->nav_inv);
	gotoxy(82, 12);
	_tprintf(TEXT(" - Nav Inv b: %d"), jogo->pontuacoes->nav_inv_b);
	gotoxy(82, 13);
	_tprintf(TEXT(" - Nav Inv e: %d"), jogo->pontuacoes->nav_inv_e);
	gotoxy(82, 14);
	_tprintf(TEXT(" - Nav Inv i: %d"), jogo->pontuacoes->nav_inv_i);
	gotoxy(82, 15);
	_tprintf(TEXT(" - Nav Def: %d"), jogo->pontuacoes->nav_def);
	gotoxy(82, 16);
	_tprintf(TEXT(" - Bombas: %d"), jogo->pontuacoes->bombas);
	gotoxy(82, 17);
	_tprintf(TEXT(" - Tiros: %d"), jogo->pontuacoes->tiros);
	gotoxy(82, 18);
	_tprintf(TEXT(" - PowerUps: %d"), jogo->pontuacoes->powerups);
	gotoxy(82, 19);
	_tprintf(TEXT(" - Obstáculos: %d"), jogo->pontuacoes->obstaculos);

	// Naves Invasoras
	for (i = 0; i < NUM_NAV_INVASORAS; i++) {
		/*if (jogo->naves_invasoras[i].coord.y >= POS_Y_LIMITE_NAV_DEF_MOV) {
			gotoxy(30, 12);
			_tprintf(TEXT("FIM!! Invasores vencem!"));
			_gettch();
		}*/
		if (jogo->naves_invasoras[i].resistencia != 0) {
			gotoxy(jogo->naves_invasoras[i].coord.x, jogo->naves_invasoras[i].coord.y);
			//_tprintf(TEXT("i"));
			_tprintf(TEXT("%c"), jogo->naves_invasoras[i].tipo);
		}
	}
	// Naves Defensoras
	for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
		gotoxy(jogo->naves_defensoras[i].coord.x, jogo->naves_defensoras[i].coord.y);
		_tprintf(TEXT("d"));
	}
	// Bombas
	for (i = 0; i < NUM_BOMBAS; i++) {
		if (jogo->bombas[i].velocidade != 0) {
			gotoxy(jogo->bombas[i].coord.x, jogo->bombas[i].coord.y);
			_tprintf(TEXT("8"));
		}
	}
	// Tiros
	for (i = 0; i < NUM_TIROS; i++) {
		if (jogo->tiros[i].velocidade != 0) {
			gotoxy(jogo->tiros[i].coord.x, jogo->tiros[i].coord.y);
			_tprintf(TEXT("."));
		}
	}
	//// PowerUps
	//for (i = 0; i < NUM_POWERUPS; i++) {
	//	gotoxy(jogo->powerups[i].coord.x, jogo->powerups[i].coord.y);
	//	_tprintf(TEXT("*"));
	//}
	// Obstáculos
	for (i = 0; i < NUM_OBSTACULOS; i++) {
		if (jogo->obstaculos[i].resistencia != 0) {
			gotoxy(jogo->obstaculos[i].coord.x, jogo->obstaculos[i].coord.y);
			_tprintf(TEXT("#"));
		}
	}
}