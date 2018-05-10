#pragma once

#include <windows.h>
#include <tchar.h>

#define TAM 80 // isto é para retirar

// tamanho padrão da linha de comandos do windows, mais tarde mudar para algo maior, como 500x500 ou 1000x1000
#define COLUNAS 80
#define LINHAS 25

#define NUM_CLIENTES 2

typedef struct {
	char ocupa_posicao; // I-> invasor, D-> defensor, P-> powerup, t-> tiro
} CAMPO_BATALHA;

typedef struct {
	LARGE_INTEGER msg;
} MENSAGEM;

// Memoria partilhada
CAMPO_BATALHA CampoBatalha[COLUNAS][LINHAS];
MENSAGEM mensagens[NUM_CLIENTES];

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