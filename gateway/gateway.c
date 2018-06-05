#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"
#include "../utils.h"

// funções das Threads
DWORD __stdcall jogadores(void *ptr);

// Variáveis globais
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

	MutexJogo = CreateMutex(NULL, FALSE, "MutexJogo");
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

	//if (argc > 1) {
	//	if (_tcscmp(argv[1], TEXT("debug")) == 0) {
	//		
	//	}
	//	if (_tcscmp(argv[1], TEXT("?")) == 0) {
	//		_tprintf(TEXT("argumentos:\n"));
	//		_tprintf(TEXT("%s debug -> mostra os dados de jogo e mensagens...\n"), argv[0]);
	//	}
	//}
	//else {
	//	_tprintf(TEXT("Ligação estabelecida ao servidor... a aguardar algo??\n"));
	//}

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
		/*mostra_tabuleiro_jogo();
		mostra_jogo_na_consola(jogo);*/
		mostra_jogo(jogo);

		//Sleep(VEL_MEIO_SEC);
		gotoxy(17, 25); // prompt

		//_tprintf(TEXT("[Erro](%d)\n"), GetLastError());
		/*if (jogo == NULL)
			_tprintf(TEXT("[Erro](%d)\n"), GetLastError());*/

		input = _gettch();
		input = toupper(input);

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
		//ReleaseSemaphore(SemEscreveJogo, 1, NULL);
	}
	return 0;
}