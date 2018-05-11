#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

// tamanho padrão da linha de comandos do windows, mais tarde mudar para algo maior, como 500x500 ou 1000x1000
#define COLUNAS 80
#define LINHAS 25

#define NUM_NAV_INVASORAS 4
#define NUM_NAV_DEFENSORAS 2 // equivalente ao num de clientes, um cliente por cada nave defensora
#define NUM_BOMBAS 10
#define NUM_TIROS 10
#define NUM_POWERUP 2


#define TAM 80 // isto é para retirar

typedef struct {
	int nave_defensora[NUM_NAV_DEFENSORAS];
	char texto[TAM];
} Mensagem;

// Estrutura de dados
typedef struct {
	unsigned int	x;
	unsigned int	y;
} Pos; // coordenadas (nao se pode usar Coord, é reservado)

typedef struct {
	unsigned int	tamanho;
	char			tipo; // definir tipos de powerups, 0-> nenhum, ver lista
	Pos				coord;
} PowerUp;

typedef struct {
	Pos				coord;
} Tiro;

typedef struct {
	Pos				coord;
} Bomba;

typedef struct {
	unsigned int	tamanho;
	Pos				coord;
	PowerUp			powerup;
} NaveInvasora;

typedef struct {
	unsigned int	tamanho;
	Pos				coord;
	PowerUp			powerup;
} NaveDefensora;

typedef struct {
	NaveInvasora	naves_invasoras[NUM_NAV_INVASORAS];
	NaveDefensora	naves_defensoras[NUM_NAV_DEFENSORAS];
	Bomba			bombas[NUM_BOMBAS];
	Tiro			tiros[NUM_TIROS];
	PowerUp			powerups[NUM_POWERUP];
} Jogo;