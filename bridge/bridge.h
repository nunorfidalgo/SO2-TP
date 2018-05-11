#pragma once

#include <windows.h>
#include <tchar.h>

#define TAM 80 // isto é para retirar

typedef struct {
	LARGE_INTEGER msg;
} MENSAGEM;

// Memoria partilhada
MENSAGEM *mensagens;

// Threads?

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Funcões de teste
	int BRIDGE_API Teste(void);
	int BRIDGE_API UmValor(int v);

	void BRIDGE_API gotoxy(int x, int y);

	int BRIDGE_API patrao();
	int BRIDGE_API empregado();

	int BRIDGE_API inicia_campo(void);
}