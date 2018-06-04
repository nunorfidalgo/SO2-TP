#pragma once
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

// Velocidade
#define VEL_100MS 100
#define VEL_200MS 200
#define VEL_300MS 300
#define VEL_400MS 400
#define VEL_MEIO_SEC 500
#define VEL_UM_SEC 1000

// Semaforo de Jogo, cada posisção controla o array associado;
#define SEMAFORO_JOGO_NUM_ACCOES 7

// tamanho padrão da linha de comandos do windows, mais tarde mudar para algo maior, como 500x500 ou 1000x1000
#define COLUNAS 80
#define LINHAS 25

#define POS_ZERO 0
#define POS_X_INICIAL 0
#define POS_Y_INICIAL 5
#define POS_FIM_TAB_Y 22 // chat de msgs
#define POS_ENVIAR_MSGS 25
#define POS_FIM_Y 26
#define POS_Y_LIMITE_NAV_DEF_MOV (int)(POS_FIM_TAB_Y / 1.2)


// número maximo a mostrar no campo de batalha
#define NUM_NAV_INVASORAS 3
#define NUM_NAV_DEFENSORAS 1 // equivalente ao num de clientes, um cliente por cada nave defensora
#define NUM_BOMBAS 3 // (NUM_NAV_INVASORAS * 
#define NUM_TIROS 5 // ((NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS ) * 4) 
#define NUM_POWERUPS 2
#define NUM_POWERUPS_NAV_DEF 2
#define NUM_OBSTACULOS 20
#define TMP_POS (NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS)

// Mensagens
#define TEXTO 160

typedef struct {
	unsigned int	idJogador;
	TCHAR			texto[TEXTO];
	//HANDLE			hEvMsg;
} Mensagem;

// Estrutura de dados
// Coordenadas das naves no campo de jogo
typedef struct {
	unsigned int	x;
	unsigned int	y;
} Posicao; // coordenadas (nao se pode usar Coord, é reservado)

// Dimensao dos elementos do jogo
typedef struct {
	unsigned int	altura;
	unsigned int	largura;
} Dimensao;

// Elemento de jogo - Bomba
typedef struct {
	unsigned int	velocidade;
	Posicao			coord;
} Bomba;

// Elemento de jogo - Tiro
typedef struct {
	unsigned int	velocidade;
	// tipo de tiro, invasor ou defensor!!!!!!!!!!!!!!!!!!!!!!!!
	char			tipo;
	Posicao			coord;
} Tiro;

// Elemento de jogo - Powerup
typedef struct {
	SYSTEMTIME		adquirido;
	unsigned int	duracao;
	unsigned int	velocidade;
	unsigned int	ocorrencia;
	char			tipo; // definir tipos de powerups, 0-> nenhum, ver lista
	Dimensao		dimensao;
	Posicao			coord;
} PowerUp;

// Elemento de jogo - Nave Invasora
typedef struct {
	unsigned int	resistencia;
	unsigned int	velocidade;
	char			tipo;
	Dimensao		dimensao;
	Posicao			coord;
} NaveInvasora;

// Elemento de jogo - Nave Defensora
typedef struct {
	unsigned int	vidas;
	unsigned int	velocidade;
	Posicao			coord;
	Dimensao		dimensao;
	PowerUp			powerup[NUM_POWERUPS_NAV_DEF];
} NaveDefensora;

// Elemento de jogo - Pontuacao de cada jogador
typedef struct {
	unsigned int	pontos;
	unsigned int	disparos;
	unsigned int	invasoras;
	unsigned int	vidas;
	unsigned int	powerups;
	unsigned int	colisoes;
} Pontuacao;

// Elemento de jogo - Extra
typedef struct {
	unsigned int	resistencia;
	Posicao			coord;
	Dimensao		dimensao;
} Obstaculo;

typedef struct {
	unsigned int	nivel; // ???? será assim para designar o nível / como fazer o incremento de dificuldade ????
	unsigned int	In;
	unsigned int	Out;
	NaveInvasora	naves_invasoras[NUM_NAV_INVASORAS];
	NaveDefensora	naves_defensoras[NUM_NAV_DEFENSORAS];
	Bomba			bombas[NUM_BOMBAS];
	Tiro			tiros[NUM_TIROS];
	PowerUp			powerups[NUM_POWERUPS];
	Obstaculo		obstaculos[NUM_OBSTACULOS];
	Pontuacao		pontuacoes[NUM_NAV_DEFENSORAS];
} Jogo;
