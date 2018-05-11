#pragma once
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"


// tamanho padrão da linha de comandos do windows, mais tarde mudar para algo maior, como 500x500 ou 1000x1000
#define COLUNAS 80
#define LINHAS 25

#define NUM_CLIENTES 2
#define NUM_INVASORAS 6
#define NUM_DEFENSORAS 2
#define NUM_POWERUP 2

// Estrutura de dados
typedef struct {
	unsigned int x;
	unsigned int y;
} POS;

typedef struct {
	unsigned int tamanho;
	int tipo[10]; // definir tipos de powerups, 0-> nenhum
	POS coord;
} POWERUP;

typedef struct {
	POS coord;
} TIROS;

typedef struct {
	POS coord;
} BOMBA;

typedef struct {
	unsigned int tamanho;
	POS coord;
	POWERUP powerup;
} NAVE_INVASORAS;

typedef struct {
	unsigned int tamanho;
	POS coord;
	POWERUP powerup;
} NAVE_DEFENSORAS; // clientes

typedef struct {
	NAVE_INVASORAS	naves_invasoras;
	NAVE_DEFENSORAS	naves_defensoras; // clientes
	BOMBA			bombas;
	TIROS			tiros;
	POWERUP			powerups;
} JOGO;