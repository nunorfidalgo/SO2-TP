#pragma once

#include <windows.h>
#include <tchar.h>
#include "../dados.h"

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Funcões de teste
	int BRIDGE_API Teste(void);
	int BRIDGE_API UmValor(int v);

	// Mensagens
	int BRIDGE_API patrao();
	int BRIDGE_API empregado();

	Jogo BRIDGE_API * CriaMemoriaPartilhadaJogo(HANDLE &hMapMemParJogo, LARGE_INTEGER &tam_jogo);

	void BRIDGE_API gotoxy(int x, int y);
}