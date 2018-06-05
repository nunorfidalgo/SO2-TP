#include "servidor.h"
#include "../bridge/bridge.h"
#include "../utils.h"
#include "jogo.h"

// Variáveis globais (definidas no servidor.h)
BOOL	DEBUG = FALSE;
TCHAR	NomeSemaforoPodeEscrever[] = TEXT("Escrever no semáforo");
TCHAR	NomeSemaforoPodeLer[] = TEXT("Ler do semáforo");
HANDLE	SemEscreveJogo;
HANDLE	SemLerJogo;
HANDLE	MutexJogo;

int _tmain(int argc, TCHAR *argv[]) {
	setlocale(LC_CTYPE, "Portuguese");
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	init_rand(); // inicializa o gerador de números aleatorios

	// Variáveis locais
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

	if (argc > 1 && _tcscmp(argv[1], TEXT("debug")) == 0) DEBUG = TRUE;
	inicia_jogo(jogo);
	// if (DEBUG == TRUE) mostra_naves_invasoras(jogo->naves_invasoras);
	// if (DEBUG == TRUE) mostra_naves_defensoras(jogo->naves_defensoras);
	// if (DEBUG == TRUE) mostra_bombas(jogo->bombas);
	// if (DEBUG == TRUE) mostra_tiros(jogo->tiros);
	// if (DEBUG == TRUE) mostra_powerups(jogo->powerups);
	// if (DEBUG == TRUE) mostra_obstaculos(jogo->obstaculos);
	// if (DEBUG == TRUE) mostra_pontuacoes(jogo->pontuacoes);

	_tprintf(TEXT("\n* sizeof(jogo): %d bytes\n"), sizeof(Jogo));
	_tprintf(TEXT("* Novo jogo pronto, a aguardar gateway...\n"));

	htNavInvs = CreateThread(NULL, 0, naves_invasoras, (LPVOID)jogo, 0, &idNavInvs);
	if (htNavInvs != NULL) {
		_tprintf(TEXT("- Thread[id=%d] Naves Invasoras;\n"), idNavInvs);
	}
	else {
		_tprintf(TEXT("## Erro ao criar Thread de Naves Invasoras! (código=%d)\n"), GetLastError());
		exit(1);
	}

	htBatalha = CreateThread(NULL, 0, batalha, (LPVOID)jogo, 0, &idBatalha);
	if (htBatalha != NULL) {
		_tprintf(TEXT("- Thread[id=%d] Batalha;\n"), idBatalha);
	}
	else {
		_tprintf(TEXT("## Erro ao criar Thread de Batalha! (código=%d)\n"), GetLastError());
		exit(1);
	}

	htEfeitos = CreateThread(NULL, 0, efeitos, (LPVOID)jogo, 0, &idEfeitos);
	if (htEfeitos != NULL) {
		_tprintf(TEXT("- Thread[id=%d] Efeitos;\n"), idEfeitos);
	}
	else {
		_tprintf(TEXT("## Erro ao criar Thread de Efeitos! (código=%d)\n"), GetLastError());
		exit(1);
	}

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