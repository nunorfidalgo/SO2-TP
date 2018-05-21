#include "gateway.h"

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis Jogo
	Jogo			*jogo;
	HANDLE			hMapMemParJogo;
	LARGE_INTEGER	tam_jogo;

	/*HANDLE			muJogadores;
	HANDLE			htJogadores;
	DWORD			idJogadores;*/

	system("cls");
	//_tprintf(TEXT("iniciou...\n"));

	jogo = AcedeMemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo); // -mudar isto para o gateway nao estar a correr sem o servidor !!!!!

	if (argc > 1) {
		if (_tcscmp(argv[1], TEXT("debug")) == 0) {
			while (1) {
				system("cls");
				mostra_tabuleiro_jogo();
				mostra_jogo_na_consola(jogo);
				Sleep(MEIO_SEC);
				gotoxy(20, 25); // prompt
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