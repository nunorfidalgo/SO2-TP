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

	system("cls");
	_tprintf(TEXT("pronto...\n"));

	jogo = MemoriaPartilhadaJogo(&hMapMemParJogo, &tam_jogo);
	mostra_jogo_na_consola(jogo);

	_tprintf(TEXT("\nterminou...\n"));
	return 0;
}