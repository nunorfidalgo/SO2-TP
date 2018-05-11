#pragma once

#include <windows.h>
#include <tchar.h>
//#include "../servidor/dados.h"
#include "../servidor/dados.h"

#define TAM 80 // isto é para retirar

typedef struct {
	int nave_defensora[NUM_NAV_DEFENSORAS];
	char texto[TAM];
} Mensagem;

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Funcões de teste
	int BRIDGE_API Teste(void);
	int BRIDGE_API UmValor(int v);

	int BRIDGE_API patrao();
	int BRIDGE_API empregado();
}