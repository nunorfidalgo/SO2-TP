#include "servidor.h"

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis Jogo
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;
	// Threads do Jogo
	//HANDLE			muNavInvs, muNavDefs, muBatalha, muEfeitos, muJogadores;
	//HANDLE			htNavInvs, htNavDefs, htBatalha, htEfeitos, htJogadores;
	//DWORD			idNavInvs, idNavDefs, idBatalha, idEfeitos, idJogadores;

	system("cls");

	jogo = MemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo);

	init_rand();
	inicia_jogo(jogo);

	mostra_naves_invasoras(jogo->naves_invasoras);
	mostra_naves_defensoras(jogo->naves_defensoras);
	mostra_bombas(jogo->bombas);
	mostra_tiros(jogo->tiros);
	mostra_powerups(jogo->powerups);
	mostra_pontuacoes(jogo->pontuacoes);
	mostra_obstaculos(jogo->obstaculos);

	// Naves Invasoras
	//muNavInvs = CreateMutex(NULL, FALSE, NULL);
	//if (muNavInvs == NULL) {
	//	_tprintf(TEXT("ERRO ao criar mutex para Naves Invasoras: %d\n"), GetLastError());
	//	exit(1);
	//}
	//htNavInvs = CreateThread(NULL, 0, naves_invasoras, (LPVOID)jogo->naves_invasoras, 0, &idNavInvs);
	//if (htNavInvs != NULL) {
	//	_tprintf(TEXT("[Thread Naves Invasoras] id=%d;\n"), idNavInvs);
	//}
	//else {
	//	_tprintf(TEXT("ERRO ao criar Thread de Naves Invasoras: %d\n"), GetLastError());
	//	exit(1);
	//}

	//// Naves Defensoras
	//muNavDefs = CreateMutex(NULL, FALSE, NULL);
	//if (muNavDefs == NULL) {
	//	_tprintf(TEXT("ERRO ao criar mutex para Naves Defensoras: %d\n"), GetLastError());
	//	exit(1);
	//}
	//htNavDefs = CreateThread(NULL, 0, naves_defensoras, (LPVOID)jogo->naves_defensoras, 0, &idNavDefs);
	//if (htNavDefs != NULL) {
	//	_tprintf(TEXT("[Thread Naves Defensoras] id=%d;\n"), idNavDefs);
	//}
	//else {
	//	_tprintf(TEXT("ERRO ao criar Thread de Naves Defensoras: %d\n"), GetLastError());
	//	exit(1);
	//}

	//// Batalha
	//muBatalha = CreateMutex(NULL, FALSE, NULL);
	//if (muBatalha == NULL) {
	//	_tprintf(TEXT("ERRO ao criar mutex para Batalha: %d\n"), GetLastError());
	//	exit(1);
	//}
	//htBatalha = CreateThread(NULL, 0, batalha, (LPVOID)jogo, 0, &idBatalha);
	//if (htBatalha != NULL) {
	//	_tprintf(TEXT("[Thread Batalha] id=%d;\n"), idBatalha);
	//}
	//else {
	//	_tprintf(TEXT("ERRO ao criar Thread de Batalha: %d\n"), GetLastError());
	//	exit(1);
	//}

	//// Efeitos
	//muEfeitos = CreateMutex(NULL, FALSE, NULL);
	//if (muEfeitos == NULL) {
	//	_tprintf(TEXT("ERRO ao criar mutex para Efeitos: %d\n"), GetLastError());
	//	exit(1);
	//}
	//htEfeitos = CreateThread(NULL, 0, efeitos, (LPVOID)jogo, 0, &idEfeitos);
	//if (htEfeitos != NULL) {
	//	_tprintf(TEXT("[Thread Efeitos] id=%d;\n"), idEfeitos);
	//}
	//else {
	//	_tprintf(TEXT("ERRO ao criar Thread de Efeitos: %d\n"), GetLastError());
	//	exit(1);
	//}

	//// Jogadores
	//muJogadores = CreateMutex(NULL, FALSE, NULL);
	//if (muJogadores == NULL) {
	//	_tprintf(TEXT("ERRO ao criar mutex para Jogadores: %d\n"), GetLastError());
	//	exit(1);
	//}
	//// Threat PowerUps
	//htJogadores = CreateThread(NULL, 0, jogadores, (LPVOID)jogo, 0, &idJogadores); // jogo->clientes add cliente to dados
	//if (htJogadores != NULL) {
	//	_tprintf(TEXT("[Thread Jogadores] id=%d;\n"), idJogadores);
	//}
	//else {
	//	_tprintf(TEXT("ERRO ao criar Thread de Jogadores: %d\n"), GetLastError());
	//	exit(1);
	//}

	//WaitForSingleObject(htNavInvs, INFINITE);
	//WaitForSingleObject(htNavDefs, INFINITE);
	//WaitForSingleObject(htBatalha, INFINITE);
	//WaitForSingleObject(htEfeitos, INFINITE);
	//WaitForSingleObject(htJogadores, INFINITE);

	//CloseHandle(muNavInvs);
	//CloseHandle(muNavDefs);
	//CloseHandle(muBatalha);
	//CloseHandle(muEfeitos);
	//CloseHandle(muJogadores);

	//CloseHandle(hEvJogo);
	UnmapViewOfFile(jogo);
	CloseHandle(hMapMemParJogo);

	_tprintf(TEXT("\nTerminou!!\n\n"));
	return 0;
}