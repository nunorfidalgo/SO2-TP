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
#define NUM_OBSTACULOS 5
#define NUM_POWERUPS_NAVE 3

#define LIMITEY_NAV_DEFENSORAS 0.2
#define TAM 80 // isto é para retirar

typedef struct {
	int nave_defensora[NUM_NAV_DEFENSORAS];
	char texto[TAM];
} Mensagem;

// Estrutura de dados
// Coordenadas das naves no campo de jogo
typedef struct {
	unsigned int	x;
	unsigned int	y;
} Pos; // coordenadas (nao se pode usar Coord, é reservado)

// Dimensao dos elementos do jogo
typedef struct {
	unsigned int	altura;
	unsigned int	largura;
}Dimensao;

// Elemento de jogo - Powerup
typedef struct {
	unsigned int	duracao;
	unsigned int	velocidade;
	SYSTEMTIME		adquirido;
	unsigned int	ocorrencia;
	char			tipo; // definir tipos de powerups, 0-> nenhum, ver lista
	Dimensao		dimensao;
	Pos				coord;
} PowerUp;

// Elemento de jogo - Tiro
typedef struct {
	Pos				coord;
	unsigned int	velocidade;
} Tiro;

typedef struct {
	Pos				coord;
	unsigned int	velocidade;
} Bomba;

typedef struct {
	Pos				coord;
	Dimensao		dimensao;
	unsigned int	resistencia;
}Obstaculo;

typedef struct {
	unsigned int	resistencia;
	unsigned int	velocidade;
	char			tipo;
	Dimensao		dimensao;
	Pos				coord;
} NaveInvasora;

typedef struct {
	unsigned int	vidas;
	unsigned int	velocidade;
	Pos				coord;
	PowerUp			powerup[NUM_POWERUPS_NAVE];
	Dimensao		dimensao;
} NaveDefensora;

typedef struct {
	unsigned int	pontos;
	unsigned int	disparos;
	unsigned int	invasoras;
	unsigned int	vidas;
	unsigned int	powerups;
	unsigned int	colisoes;
} Pontuacao;

typedef struct {
	unsigned int	nivel; // ???? será assim para designar o nível / como fazer o incremento de dificuldade ????
	Pontuacao		pontuacoes[NUM_NAV_DEFENSORAS];
	NaveInvasora	naves_invasoras[NUM_NAV_INVASORAS];
	NaveDefensora	naves_defensoras[NUM_NAV_DEFENSORAS];
	Bomba			bombas[NUM_BOMBAS];
	Tiro			tiros[NUM_TIROS];
	PowerUp			powerups[NUM_POWERUP];
	Obstaculo		obstaculos[NUM_OBSTACULOS];
} Jogo;