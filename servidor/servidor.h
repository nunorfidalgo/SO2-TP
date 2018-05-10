#pragma once
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "../bridge/bridge.h"


#define NUM_INVASORAS 6
#define NUM_DEFENSORAS 2
#define NUM_POWERUP 2

// Estrutura de dados
typedef struct {
	unsigned int tamanho = 0;
	int tipo = 0; // definir tipos de powerups, 0-> nenhum
	bool em_uso = 0; // 0->disponivel, 1-> em_uso
	unsigned int x = 0;
	unsigned int y = 0;
} POWERUP;

typedef struct {
	unsigned int tamanho = 0; // ?
	bool tipo; // 0->tiro, 1->bomba
	unsigned int x = 0;
	unsigned int y = 0;
} ATAQUE;

typedef struct {
	unsigned int tamanho;
	//bool tipo; // 0->invasor, 1->defensor
	unsigned int x;
	unsigned int y;
	bool powerup;
	char powerupType;
} NAVE;

// Vectores dinamicos para uso no servidor
NAVE		*naves_invasoras;
NAVE		*naves_defensoras;
ATAQUE		*ataques;
POWERUP		*powerups;