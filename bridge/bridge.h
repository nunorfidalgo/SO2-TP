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

	int BRIDGE_API patrao();
	int BRIDGE_API empregado();

	DWORD BRIDGE_API __stdcall inicia_naves_invasoras(void *ptr);
	DWORD BRIDGE_API __stdcall inicia_naves_defensoras(void *ptr);
	DWORD BRIDGE_API __stdcall inicia_bombas(void *ptr);
	DWORD BRIDGE_API __stdcall inicia_tiros(void *ptr);
	DWORD BRIDGE_API __stdcall inicia_powerups(void *ptr);

	void BRIDGE_API mostra_naves_invasoras(NaveInvasora *naves_invasoras);
	void BRIDGE_API mostra_naves_defensoras(NaveDefensora *naves_defensoras);
	void BRIDGE_API mostra_bombas(Bomba *bombas);
	void BRIDGE_API mostra_tiros(Tiro *tiros);
	void BRIDGE_API mostra_powerups(PowerUp *powerups);

	void BRIDGE_API gotoxy(int x, int y);
}