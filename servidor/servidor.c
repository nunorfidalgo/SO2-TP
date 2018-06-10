#include "servidor.h"
#include "../bridge/bridge.h"
#include "../utils.h"
#include "jogo.h"

// Variáveis globais (definidas no servidor.h) 
BOOL	DEBUG = FALSE;
HANDLE	MutexJogo;
HANDLE	SemEscreveJogo;
HANDLE	SemLerJogo;

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
		_tprintf(TEXT("%s '?' -> mostra esta ajuda;\n"), argv[0]);
		_tprintf(TEXT("%s 'debug' -> mostra os dados de jogo e avisos;\n"), argv[0]);
		exit(0);
	}

	MutexJogo = CreateMutex(NULL, FALSE, "MutexJogo");
	if (MutexJogo == NULL) {
		_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
		return 1;
	}

	CriaSemaforoEscreveJogo(SemEscreveJogo);
	CriaSemaforoLerJogo(SemLerJogo);

	jogo = CriaMemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo);

	if (argc > 1 && _tcscmp(argv[1], TEXT("debug")) == 0) DEBUG = TRUE;
	inicia_jogo(jogo);
	if (DEBUG == TRUE) mostra_naves_invasoras(jogo->naves_invasoras);
	if (DEBUG == TRUE) mostra_naves_defensoras(jogo->naves_defensoras);
	if (DEBUG == TRUE) mostra_bombas(jogo->bombas);
	if (DEBUG == TRUE) mostra_tiros(jogo->tiros);
	if (DEBUG == TRUE) mostra_powerups(jogo->powerups);
	if (DEBUG == TRUE) mostra_obstaculos(jogo->obstaculos);
	if (DEBUG == TRUE) mostra_pontuacoes(jogo->pontuacoes);

	_tprintf(TEXT("\n** Uso de mémoria (jogo): %d bytes (%d Kb)\n\n"), sizeof(Jogo), sizeof(Jogo) / 1014);
	_tprintf(TEXT("* Novo jogo pronto, a aguardar gateway... (falta detectar o gateway a ligar e vice versa)\n\n"));

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
	_tprintf(TEXT("\n** 'ESC' -> termina..."));
	input = _gettch();
	input = toupper(input);
	_flushall();
	if (input == 27) // ESC = sair
		exit(1);

	WaitForSingleObject(htNavInvs, INFINITE);
	WaitForSingleObject(htBatalha, INFINITE);
	//WaitForSingleObject(htEfeitos, INFINITE);

	UnmapViewOfFile(jogo);
	CloseHandle(SemEscreveJogo);
	CloseHandle(SemLerJogo);
	CloseHandle(MutexJogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nFim do jogo!!\n\n"));
	return 0;
}