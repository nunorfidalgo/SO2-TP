#include "servidor.h"

// Variaveis globais
Jogo		jogo;
Mensagem	mensagens;

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("pronto...") );

	//Chamar a funcao da Dll
	//Teste();
	//_tprintf(TEXT("\nValor: %d"), UmValor(45));

	//_tprintf(TEXT("\nBridge: A executar patrao..."));
	//patrao();

	inicia_jogo(&jogo);
	mostra_naves_invasoras(jogo.naves_invasoras);
	mostra_naves_defensoras(jogo.naves_defensoras);
	mostra_bombas(jogo.bombas);
	mostra_tiros(jogo.tiros);
	mostra_powerups(jogo.powerups);

	_tprintf(TEXT("\nterminou..."));
	return 0;
}