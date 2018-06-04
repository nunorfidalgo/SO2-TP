#include "servidor.h"
#include "../bridge/bridge.h"
#include "../utils.h"
#include "jogo.h"

// funções das Threads
DWORD __stdcall naves_invasoras(void *ptr);
DWORD __stdcall batalha(void *ptr);
DWORD __stdcall efeitos(void *ptr);

// Variáveis globais
TCHAR	NomeSemaforoPodeEscrever[] = TEXT("Escrever no semáforo");
TCHAR	NomeSemaforoPodeLer[] = TEXT("Ler do semáforo");
HANDLE	SemEscreveJogo;
HANDLE	SemLerJogo;
HANDLE	MutexJogo;

int total_tiros_nav_inv = 0, total_tiros_nav_def = 0;

int _tmain(int argc, TCHAR *argv[]) {
	setlocale(LC_CTYPE, "Portuguese");
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	
	init_rand(); // inicializa o gerador de números aleatorios

	// Variáveis Jogo locais
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
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	if (argc > 1 && _tcscmp(argv[1], TEXT("debug")) == 0) {
		inicia_jogo(jogo, TRUE);
		//mostra_naves_invasoras(jogo->naves_invasoras);
		//mostra_naves_defensoras(jogo->naves_defensoras);
		//mostra_bombas(jogo->bombas);
		//mostra_tiros(jogo->tiros);
		//mostra_powerups(jogo->powerups);
		//mostra_obstaculos(jogo->obstaculos);
		//mostra_pontuacoes(jogo->pontuacoes);
	}
	else {
		inicia_jogo(jogo, FALSE);
	}

	_tprintf(TEXT("\n* sizeof(jogo): %d bytes\n"), sizeof(Jogo));
	_tprintf(TEXT("* Novo jogo pronto, a aguardar gateway...\n"));

	htNavInvs = CreateThread(NULL, 0, naves_invasoras, (LPVOID)jogo->naves_invasoras, 0, &idNavInvs);
	if (htNavInvs != NULL) {
		_tprintf(TEXT("Thread[id=%d] Naves Invasoras;\n"), idNavInvs);
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread de Naves Invasoras! (código=%d)\n"), GetLastError());
		exit(1);
	}

	htBatalha = CreateThread(NULL, 0, batalha, (LPVOID)jogo, 0, &idBatalha);
	if (htBatalha != NULL) {
		_tprintf(TEXT("Thread[id=%d] Batalha;\n"), idBatalha);
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread de Batalha! (código=%d)\n"), GetLastError());
		exit(1);
	}

	htEfeitos = CreateThread(NULL, 0, efeitos, (LPVOID)jogo, 0, &idEfeitos);
	if (htEfeitos != NULL) {
		_tprintf(TEXT("Thread[id=%d] Efeitos;\n"), idEfeitos);
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread de Efeitos! (código=%d)\n"), GetLastError());
		exit(1);
	}

	// sair com ESC
	input = _gettch();
	input = toupper(input);
	if (input == 27) // ESC = sair
		exit(1);

	WaitForSingleObject(htNavInvs, INFINITE);
	WaitForSingleObject(htBatalha, INFINITE);
	WaitForSingleObject(htEfeitos, INFINITE);

	CloseHandle(MutexJogo);

	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nFim do jogo!!\n\n"));
	return 0;
}

/**** Fuções das Threads ****/

DWORD __stdcall naves_invasoras(void *ptr) {
	_tprintf(TEXT("- Funcao da Thread Naves Invasoras:\n"));
	NaveInvasora *naves_invasoras = (NaveInvasora *)ptr;
	
	/*Sleep(10000);
	_tprintf(TEXT("Dormi 10 sec... fazer as naves inv mexer!!\n"));*/

	// gotoxy( x     , y     );
	// gotoxy(COLUNAS, LINHAS);

	/*int i;
	float xrand, yrand;
	while (1) {

		WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		for (i = 0; i < NUM_NAV_INVASORAS; i++) {
			xrand = rand_01();
			yrand = rand_01();
			if (xrand < 0.5 && (naves_invasoras[i].coord.x > 0 || naves_invasoras[i].coord.x < COLUNAS))
				naves_invasoras[i].coord.x++;
			if (yrand < 0.5 && (naves_invasoras[i].coord.y > 0 || naves_invasoras[i].coord.y < POS_FINAL_NAV_DEF_Y))
				naves_invasoras[i].coord.y++;
		}

		ReleaseMutex(MutexJogo);
		Sleep(VEL_100MS);
		ReleaseSemaphore(SemLerJogo, 1, NULL);
		//_tprintf(TEXT("\nThread Naves Invasoras-----------------------------------------------------------------------------------------\n"));
		//mostra_naves_invasoras(jogo->naves_invasoras);

	}*/
	return 0;
}

DWORD __stdcall batalha(void *ptr) {
	_tprintf(TEXT("- Funcao da Thread Batalha:\n"));
	Jogo *jogo = (Jogo *)ptr;
	int i;
	while (1) {
		WaitForSingleObject(SemEscreveJogo, INFINITE);
		WaitForSingleObject(MutexJogo, INFINITE);

		// tiros
		for (i = 0; i < NUM_TIROS; i++) {

			// tiro de naves invasoras
			if (jogo->tiros[i].tipo == 'i') {
				if (jogo->tiros[i].coord.y < POS_FIM_TAB_Y - 1) {
					jogo->tiros[i].coord.y++;
					total_tiros_nav_inv++;
				}
				else { // tiro desaparece
					jogo->tiros[i].tipo = '0';
					jogo->tiros[i].velocidade = 0;
					jogo->tiros[i].coord.y = 0;
					jogo->tiros[i].coord.x = 0;
				}
			}

			// tiro de naves defensoras
			if (jogo->tiros[i].tipo == 'd') {
				jogo->tiros[i].coord.y--;
				total_tiros_nav_def++;
				if (jogo->tiros[i].coord.y <= POS_ZERO) {// tiro desaparece
					jogo->tiros[i].tipo = '0';
					jogo->tiros[i].velocidade = 0;
					jogo->tiros[i].coord.y = 0;
					jogo->tiros[i].coord.x = 0;
				}
			}

		}

		/*jogo->bombas[i].coord.y++;
		jogo->powerups[i].coord.y++;*/

		_tprintf(TEXT("\nThread Batalha-----------------------------------------------------------------------------------------\n"));
		_tprintf(TEXT("POS_Y_LIMITE_NAV_DEF_MOV: %d\n"), POS_Y_LIMITE_NAV_DEF_MOV);
		mostra_naves_defensoras(jogo->naves_defensoras);
		//mostra_bombas(jogo->bombas);
		mostra_tiros(jogo->tiros);
		//mostra_powerups(jogo->powerups);
		//mostra_obstaculos(jogo->obstaculos);


		ReleaseMutex(MutexJogo);
		//Sleep(VEL_100MS);
		ReleaseSemaphore(SemLerJogo, 1, NULL);
	}
	return 0;
}

DWORD __stdcall efeitos(void *ptr) {
	Jogo *jogo = (Jogo *)ptr;
	_tprintf(TEXT("- Funcao da Thread Efeitos:\n"));
	_tprintf(TEXT("\nThread Efeitos-----------------------------------------------------------------------------------------\n"));
	return 0;
}