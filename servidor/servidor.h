#pragma once

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "../dados.h"

// Variáveis globais
extern BOOL		DEBUG;
extern TCHAR	NomeSemaforoPodeEscrever[];
extern TCHAR	NomeSemaforoPodeLer[];
extern HANDLE	SemEscreveJogo;
extern HANDLE	SemLerJogo;
extern HANDLE	MutexJogo;
extern int		pos_bombas;

typedef struct { // apenas usado na inicialização 
	Posicao	nav_inv[NUM_NAV_INVASORAS];
	Posicao	nav_def[NUM_NAV_DEFENSORAS];
	Posicao	obstaculos[NUM_OBSTACULOS];
} PosicoesIniciais;
