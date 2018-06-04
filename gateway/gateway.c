#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"
#include "../utils.h"

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis Jogo
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;

	HANDLE			MutexJogo;
	HANDLE			SemLerJogo, SemEscreveJogo;

	TCHAR NomeSemaforoPodeEscrever[] = TEXT("Semáforo Pode Escrever");
	TCHAR NomeSemaforoPodeLer[] = TEXT("Semáforo Pode Ler");

	//HANDLE			MutexJogadores;
	//HANDLE			ThreatJogadores;
	//DWORD			IdJogadores;

	TCHAR input, i, j, pos_tiros = 0;


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

	if (argc > 1) {
		if (_tcscmp(argv[1], TEXT("debug")) == 0) {
			while (1) {
				WaitForSingleObject(SemLerJogo, INFINITE);
				WaitForSingleObject(MutexJogo, INFINITE);

				system("cls");
				mostra_tabuleiro_jogo();
				mostra_jogo_na_consola(jogo);

				//Sleep(VEL_MEIO_SEC);
				gotoxy(20, 25); // prompt


				//_tprintf(TEXT("[Erro](%d)\n"), GetLastError());
				if (jogo == NULL)
					_tprintf(TEXT("[Erro](%d)\n"), GetLastError());

				input = _gettch();
				input = toupper(input);
				if (input == 80) // CIMA
					for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
						jogo->naves_defensoras[i].coord.y++;
				if (input == 72) // BAIXO
					for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
						jogo->naves_defensoras[i].coord.y--;
				if (input == 77) // DIR
					for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
						jogo->naves_defensoras[i].coord.x++;
				if (input == 75) // ESQ
					for (i = 0; i < NUM_NAV_DEFENSORAS; i++)
						jogo->naves_defensoras[i].coord.x--;
				if (input == 27)
					exit(1);
				if (input == 32) {
					for (i = 0; i < NUM_NAV_DEFENSORAS; i++) {
						for (j = pos_tiros; j < NUM_TIROS; j++) {
							jogo->tiros[j].tipo = 'd';
							jogo->tiros[j].coord.x = jogo->naves_defensoras[i].coord.x;
							jogo->tiros[j].coord.y = jogo->naves_defensoras[i].coord.y;
							jogo->tiros[i].velocidade = random_l_h(1, 10);
							pos_tiros++;
							break;
						}
					}
				}

				//if (input == '')
				//if (input == '')
				//if (input == '')
				//if (input == '')

				_tprintf(TEXT("%d"), input);

				//_flushall();

				ReleaseMutex(MutexJogo);
				ReleaseSemaphore(SemEscreveJogo, 1, NULL);
			}
		}
		if (_tcscmp(argv[1], TEXT("?")) == 0) {
			_tprintf(TEXT("argumentos:\n"));
			_tprintf(TEXT("%s debug -> mostra os dados de jogo e mensagens...\n"), argv[0]);
		}
	}
	else {
		_tprintf(TEXT("Ligação estabelecida ao servidor... a aguardar algo??\n"));
	}

	//// Jogadores
	//muJogadores = CreateMutex(NULL, FALSE, NULL);
	//if (muJogadores == NULL) {
	//	_tprintf(TEXT("Erro ao criar mutex para Jogadores! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}
	//// Threat PowerUps
	//htJogadores = CreateThread(NULL, 0, jogadores, (LPVOID)jogo, 0, &idJogadores); // jogo->clientes add cliente to dados
	//if (htJogadores != NULL) {
	//	_tprintf(TEXT("[Thread Jogadores] id=%d;\n"), idJogadores);
	//}
	//else {
	//	_tprintf(TEXT("Erro ao criar Thread de Jogadores! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}

	//WaitForSingleObject(htJogadores, INFINITE);
	//CloseHandle(muJogadores);

	_tprintf(TEXT("\nterminou...\n"));
	return 0;
}
//
//DWORD __stdcall jogadores(void *ptr) {
//	Jogo *jogo = (Jogo *)ptr;
//	_tprintf(TEXT("- Funcao da Thread Jogadores:\n"));
//	return 0;
//}