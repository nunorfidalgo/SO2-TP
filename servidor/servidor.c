#include "servidor.h"
#include "../bridge/bridge.h"
#include "../utils.h"
#include "jogo.h"

// fun��es das Threads
DWORD __stdcall naves_invasoras(void *ptr);
DWORD __stdcall batalha(void *ptr);
DWORD __stdcall efeitos(void *ptr);

// Vari�veis globais
TCHAR	NomeSemaforoPodeEscrever[] = TEXT("Escrever no sem�foro");
TCHAR	NomeSemaforoPodeLer[] = TEXT("Ler do sem�foro");
HANDLE	SemEscreveJogo;
HANDLE	SemLerJogo;
HANDLE	MutexJogo;

int _tmain(int argc, TCHAR *argv[]) {
	setlocale(LC_CTYPE, "Portuguese");
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	init_rand(); // inicializa o gerador de n�meros aleatorios

	// Vari�veis Jogo locais
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;

	HANDLE			htNavInvs, htBatalha, htEfeitos;
	DWORD			idNavInvs, idBatalha, idEfeitos;

	int input;

	if (argc > 1 && _tcscmp(argv[1], TEXT("?")) == 0) {
		_tprintf(TEXT("%s ? -> mostra esta ajuda;\n"), argv[0]);
		_tprintf(TEXT("%s debug -> mostra os dados de jogo e mensagens;\n"), argv[0]);
		exit(0);
	}

	_tprintf(TEXT("********************************************************************************\n"));

	jogo = CriaMemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo);

	MutexJogo = CreateMutex(NULL, TRUE, "Jogo");
	if (MutexJogo == NULL) {
		_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
		return 1;
	}

	// verificar se ja existe shm
	if (GetLastError() != ERROR_ALREADY_EXISTS) {
		// colocar IN a zero...
		jogo->In = 0;
		jogo->Out = 0;
		// (Mutex ou) restaurar valor do semaforo PodeEscrever(+10)... ou seja release de 10 unidades, alterar na criacao para 0 ate 10
		/*ReleaseSemaphore(PodeEscrever, 10, NULL);*/
		ReleaseMutex(MutexJogo);
	}

	SemEscreveJogo = CreateSemaphore(NULL, SEMAFORO_JOGO_NUM_ACCOES, SEMAFORO_JOGO_NUM_ACCOES, NomeSemaforoPodeEscrever);
	SemLerJogo = CreateSemaphore(NULL, 0, SEMAFORO_JOGO_NUM_ACCOES, NomeSemaforoPodeLer);
	if (SemEscreveJogo == NULL || SemLerJogo == NULL) {
		_tprintf(TEXT("[Erro]Cria��o de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	if (argc > 1 && _tcscmp(argv[1], TEXT("debug")) == 0) {
		inicia_jogo(jogo, TRUE);
		mostra_naves_invasoras(jogo->naves_invasoras);
		mostra_naves_defensoras(jogo->naves_defensoras);
		mostra_bombas(jogo->bombas);
		mostra_tiros(jogo->tiros);
		mostra_powerups(jogo->powerups);
		mostra_obstaculos(jogo->obstaculos);
		mostra_pontuacoes(jogo->pontuacoes);
	}
	else {
		inicia_jogo(jogo, FALSE);
	}

	_tprintf(TEXT("\n* sizeof(jogo): %d bytes\n"), sizeof(Jogo));
	_tprintf(TEXT("* Novo jogo pronto, a aguardar gateway...\n"));

	htNavInvs = CreateThread(NULL, 0, naves_invasoras, (LPVOID)jogo, 0, &idNavInvs);
	if (htNavInvs != NULL) {
		_tprintf(TEXT("- Thread[id=%d] Naves Invasoras;\n"), idNavInvs);
	}
	else {
		_tprintf(TEXT("## Erro ao criar Thread de Naves Invasoras! (c�digo=%d)\n"), GetLastError());
		exit(1);
	}

	htBatalha = CreateThread(NULL, 0, batalha, (LPVOID)jogo, 0, &idBatalha);
	if (htBatalha != NULL) {
		_tprintf(TEXT("- Thread[id=%d] Batalha;\n"), idBatalha);
	}
	else {
		_tprintf(TEXT("## Erro ao criar Thread de Batalha! (c�digo=%d)\n"), GetLastError());
		exit(1);
	}

	//htEfeitos = CreateThread(NULL, 0, efeitos, (LPVOID)jogo, 0, &idEfeitos);
	//if (htEfeitos != NULL) {
	//	_tprintf(TEXT("- Thread[id=%d] Efeitos;\n"), idEfeitos);
	//}
	//else {
	//	_tprintf(TEXT("## Erro ao criar Thread de Efeitos! (c�digo=%d)\n"), GetLastError());
	//	exit(1);
	//}

	// sair com ESC
	input = _gettch();
	input = toupper(input);
	_flushall();
	if (input == 27) // ESC = sair
		exit(1);

	WaitForSingleObject(htNavInvs, INFINITE);
	WaitForSingleObject(htBatalha, INFINITE);
	//WaitForSingleObject(htEfeitos, INFINITE);

	CloseHandle(MutexJogo);

	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nFim do jogo!!\n\n"));
	return 0;
}

/**** Fu��es das Threads ****/

DWORD __stdcall naves_invasoras(void *ptr) {
	_tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	Jogo *jogo = (Jogo *)ptr;

	///*Sleep(10000);
	//_tprintf(TEXT("Dormi 10 sec... fazer as naves inv mexer!!\n"));*/

	int i, counter = 0;
	float xrand, yrand;

	while (1) {
		_tprintf(TEXT("\nThread Naves Invasoras-----------------------------------------------------------------------------------------\n"));
		//WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		for (i = 0; i < NUM_NAV_INVASORAS; i++) {
			xrand = rand_01();
			yrand = rand_01();
			counter++;
			_tprintf(TEXT("xrand=%0.2f, yrand=%0.2f, counter=%d;\n"), xrand, yrand, counter);

			// descer
			if (yrand < 0.3) {
				if (jogo->naves_invasoras[i].coord.y < POS_Y_LIMITE_NAV_DEF_MOV) { // POS_FIM_TAB_Y
					jogo->naves_invasoras[i].coord.y++;
					_tprintf(TEXT("nave desce!!"));
				}
				if (jogo->naves_invasoras[i].coord.y >= POS_Y_LIMITE_NAV_DEF_MOV) {
					_tprintf(TEXT("\n\nFIM!! Invasores vencem!\n"));
					_gettch();
					exit(1);
				}
			}
			// andar para os lados
			if (xrand > 0.5) {
				if (jogo->naves_invasoras[i].coord.x < COLUNAS - 1) {
					jogo->naves_invasoras[i].coord.x++;
					_tprintf(TEXT("nave dir!!"));
				}
			}
			else {
				if (jogo->naves_invasoras[i].coord.x > POS_ZERO) {
					jogo->naves_invasoras[i].coord.x--;
					_tprintf(TEXT("nave esq!!"));
				}
			}
		}
		mostra_naves_invasoras(jogo->naves_invasoras);

		ReleaseMutex(MutexJogo);
		Sleep(VEL_200MS);
		//Sleep(VEL_UM_SEC);
		//Sleep(VEL_TRINTA_SEC);
		//ReleaseSemaphore(SemLerJogo, 1, NULL);
	}
	return 0;
}

DWORD __stdcall batalha(void *ptr) {
	_tprintf(TEXT("- Funcao da Thread Batalha:\n"));
	Jogo *jogo = (Jogo *)ptr;
	int i;
	while (1) {
		//WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		// verificar as naves inv/def para terminar o jogo

		// bombas
		for (i = 0; i < NUM_BOMBAS; i++) {
			if (jogo->bombas[i].velocidade != 0) {
				jogo->bombas[i].coord.y--;
				//jogo->pontuacoes->bombas++;
				if (jogo->bombas[i].coord.y >= POS_FIM_TAB_Y) { // bomba desaparece
					jogo->bombas[i].velocidade = 0;
					jogo->bombas[i].coord.y = 0;
					jogo->bombas[i].coord.x = 0;
				}
			}
		}

		// tiros
		for (i = 0; i < NUM_TIROS; i++) {
			if (jogo->tiros[i].velocidade != 0) {
				jogo->tiros[i].coord.y--;
				if (jogo->tiros[i].coord.y <= POS_ZERO) { // tiro desaparece
					jogo->tiros[i].velocidade = 0;
					jogo->tiros[i].coord.y = 0;
					jogo->tiros[i].coord.x = 0;
				}
			}
		}

		/*_tprintf(TEXT("\nThread Batalha-----------------------------------------------------------------------------------------\n"));
		_tprintf(TEXT("POS_Y_LIMITE_NAV_DEF_MOV: %d\n"), POS_Y_LIMITE_NAV_DEF_MOV);*/
		//mostra_naves_defensoras(jogo->naves_defensoras);
		//mostra_bombas(jogo->bombas);
		//mostra_tiros(jogo->tiros);
		//mostra_powerups(jogo->powerups);
		//mostra_obstaculos(jogo->obstaculos);

		ReleaseMutex(MutexJogo);
		Sleep(VEL_200MS);
		//ReleaseSemaphore(SemLerJogo, 1, NULL);
	}
	return 0;
}

// thread para gerir os efeitos do powerups
DWORD __stdcall efeitos(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Efeitos:\n"));
	_tprintf(TEXT("\nThread Efeitos-----------------------------------------------------------------------------------------\n"));
	// gerir obstaculos... os tiros tiram a resistencia
	// gerir powerups
	return 0;
}