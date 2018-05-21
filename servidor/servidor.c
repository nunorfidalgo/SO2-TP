#include "servidor.h"

int _tmain(int argc, TCHAR *argv[]) {
	setlocale(LC_CTYPE, "Portuguese");
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis Jogo
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;
	// Threads do Jogo
	HANDLE			muNavInvs;
	HANDLE			htNavInvs;
	DWORD			idNavInvs;
	//HANDLE			muNavInvs, muNavDefs, muBatalha, muEfeitos;
	//HANDLE			htNavInvs, htNavDefs, htBatalha, htEfeitos;
	//DWORD			idNavInvs, idNavDefs, idBatalha, idEfeitos;
	//system("cls");

	if (argc > 1 && _tcscmp(argv[1], TEXT("?")) == 0) {
		_tprintf(TEXT("argumentos:\n"));
		_tprintf(TEXT("%s debug -> mostra os dados de jogo e mensagens...\n"), argv[0]);
		exit(0);
	}

	_tprintf(TEXT("\n********************************************************************************\n"));

	jogo = CriaMemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo);

	init_rand();

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
	//while (1) {}

	// Naves Invasoras
	muNavInvs = CreateMutex(NULL, FALSE, NULL);
	if (muNavInvs == NULL) {
		_tprintf(TEXT("Erro ao criar mutex para Naves Invasoras: (código=%d)\n"), GetLastError());
		exit(1);
	}
	htNavInvs = CreateThread(NULL, 0, naves_invasoras, (LPVOID)jogo->naves_invasoras, 0, &idNavInvs);
	if (htNavInvs != NULL) {
		_tprintf(TEXT("[Thread Naves Invasoras] id=%d;\n"), idNavInvs);
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread de Naves Invasoras! (código=%d)\n"), GetLastError());
		exit(1);
	}

	//// Naves Defensoras
	//muNavDefs = CreateMutex(NULL, FALSE, NULL);
	//if (muNavDefs == NULL) {
	//	_tprintf(TEXT("Erro ao criar mutex para Naves Defensoras! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}
	//htNavDefs = CreateThread(NULL, 0, naves_defensoras, (LPVOID)jogo->naves_defensoras, 0, &idNavDefs);
	//if (htNavDefs != NULL) {
	//	_tprintf(TEXT("[Thread Naves Defensoras] id=%d;\n"), idNavDefs);
	//}
	//else {
	//	_tprintf(TEXT("Erro ao criar Thread de Naves Defensoras! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}

	//// Batalha
	//muBatalha = CreateMutex(NULL, FALSE, NULL);
	//if (muBatalha == NULL) {
	//	_tprintf(TEXT("Erro ao criar mutex para Batalha! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}
	//htBatalha = CreateThread(NULL, 0, batalha, (LPVOID)jogo, 0, &idBatalha);
	//if (htBatalha != NULL) {
	//	_tprintf(TEXT("[Thread Batalha] id=%d;\n"), idBatalha);
	//}
	//else {
	//	_tprintf(TEXT("Erro ao criar Thread de Batalha! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}

	//// Efeitos
	//muEfeitos = CreateMutex(NULL, FALSE, NULL);
	//if (muEfeitos == NULL) {
	//	_tprintf(TEXT("Erro ao criar mutex para Efeitos! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}
	//htEfeitos = CreateThread(NULL, 0, efeitos, (LPVOID)jogo, 0, &idEfeitos);
	//if (htEfeitos != NULL) {
	//	_tprintf(TEXT("[Thread Efeitos] id=%d;\n"), idEfeitos);
	//}
	//else {
	//	_tprintf(TEXT("Err ao criar Thread de Efeitos! (código=%d)\n"), GetLastError());
	//	exit(1);
	//}

	WaitForSingleObject(htNavInvs, INFINITE);
	//WaitForSingleObject(htNavDefs, INFINITE);
	//WaitForSingleObject(htBatalha, INFINITE);
	//WaitForSingleObject(htEfeitos, INFINITE);

	CloseHandle(muNavInvs);
	//CloseHandle(muNavDefs);
	//CloseHandle(muBatalha);
	//CloseHandle(muEfeitos);


	//CloseHandle(hEvJogo);
	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nTerminou!!\n\n"));
	return 0;
}