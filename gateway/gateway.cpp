#include "gateway.h"

int _tmain(int argc, TCHAR *argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("\nGateway: pronto..."));

	//Chamar a funcao da Dll
	Teste();
	_tprintf(TEXT("\nBridge: Valor: %d"), UmValor(120));

	
	_tprintf(TEXT("\nBridge: A executar empregado..."));
	empregado();

	_tprintf(TEXT("\nGateway: terminou...\n"));
	return 0;
}