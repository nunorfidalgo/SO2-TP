#include "gateway.h"

int _tmain(int argc, TCHAR *argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// Variaveis
	Mensagem		*mensagens;

	HANDLE			hMapMemParMsg, hEvMsg;
	LARGE_INTEGER	tam_mensagem;

	system("cls");
	_tprintf(TEXT("pronto...\n"));

	mensagens = MemoriaPartilhadaMensagens(hMapMemParMsg, tam_mensagem);

	hEvMsg = OpenEvent(SYNCHRONIZE, true, TEXT("EvMensagens"));
	if (hEvMsg == NULL) {
		_tprintf(TEXT("ERRO ao criar evento para Mensagens: %d\n"), GetLastError());
		exit(1);
	}

	while (true) {
		EscreveMensagens(59, mensagens, hEvMsg);
	}

	CloseHandle(hEvMsg);
	UnmapViewOfFile(mensagens);
	CloseHandle(hMapMemParMsg);

	_tprintf(TEXT("\nterminou...\n"));
	return 0;
}