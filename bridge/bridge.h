#pragma once

#include <windows.h>
#include <tchar.h>

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	int BRIDGE_API Teste(void);
	int BRIDGE_API UmValor(int v);
	int BRIDGE_API patrao();
	int BRIDGE_API empregado();
}
