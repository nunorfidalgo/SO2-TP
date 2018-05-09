#pragma once

#include <windows.h>
#include <tchar.h>

#define TAM 80

// Estrutura de dados
typedef struct {
	int tamanho;
	int x;
	int y;
} NAVES;

typedef struct {
	int tamanho;
	int x;
	int y;
} TIROS;

typedef struct {
	int tamanho;
	int x;
	int y;
} POWERUPS;

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
