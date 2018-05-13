#include "gateway.h"

int _tmain(int argc, TCHAR *argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variáveis Mensagens
	Mensagem		*mensagens;
	HANDLE			hMapMemParMsg, hEvMsg;
	LARGE_INTEGER	tam_mensagem;

	// Variáveis Jogo
	Jogo			*jogo;
	HANDLE			hMapMemParJogo, hEvJogo;
	LARGE_INTEGER	tam_jogo;

	system("cls");
	_tprintf(TEXT("pronto...\n"));

	jogo = MemoriaPartilhadaJogo(hMapMemParJogo, tam_jogo);
	mostra_jogo_na_consola(jogo);

	//escreve_msgs(58);


	mensagens = MemoriaPartilhadaMensagens(hMapMemParMsg, tam_mensagem);

	//hEvMsg = OpenEvent(SYNCHRONIZE, true, TEXT("EvMensagens"));
	//if (hEvMsg == NULL) {
	//	_tprintf(TEXT("ERRO ao criar evento para Mensagens: %d\n"), GetLastError());
	//	exit(1);
	//}

	hEvMsg = OpenEvent(SYNCHRONIZE, true, TEXT("EvMensagens"));
	if (hEvMsg == NULL) {
		_tprintf(TEXT("ERRO ao aceder ao evento de Mensagens: %d\n"), GetLastError());
		_tprintf(TEXT("Confirme se a aplicação 'servidor' está em execução?\n"));
		exit(1);
	}
	EscreveMensagens(59, mensagens, &hEvMsg);

	CloseHandle(hEvMsg);
	UnmapViewOfFile(mensagens);
	CloseHandle(hMapMemParMsg);

	_tprintf(TEXT("\nterminou...\n"));
	return 0;
}