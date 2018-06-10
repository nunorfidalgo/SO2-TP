#pragma once
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

// Velocidades
#define VEL_100MS 100
#define VEL_200MS 200
#define VEL_300MS 300
#define VEL_400MS 400
#define VEL_500MS 500
#define VEL_MEIO_SEC 500
#define VEL_600MS 600
#define VEL_700MS 700
#define VEL_800MS 800
#define VEL_900MS 900
#define VEL_1000MS 1000
#define VEL_UM_SEC 1000
#define VEL_DOIS_SEC 2000
#define VEL_CINCO_SEC 5000
#define VEL_DEZ_SEC 10000
#define VEL_TRINTA_SEC 30000

// Semaforo de Jogo, cada posis��o controla o array associado;
#define SEMAFORO_JOGO_NUM_ACCOES 7

// tamanho padr�o da linha de comandos do windows, mais tarde mudar para algo maior, como 500x500 ou 1000x1000
#define COLUNAS 80
#define LINHAS 25

// posi��es da consola
#define POS_ZERO 0
#define POS_Y_INICIAL 5
#define POS_FIM_TAB_Y 22 // chat de msgs
#define POS_ENVIAR_MSGS 25
#define POS_FIM_Y 26
#define POS_Y_LIMITE_NAV_DEF_MOV (int)(POS_FIM_TAB_Y / 1.2) // 20 %

// n�mero maximo a mostrar no campo de batalha
#define NUM_NAV_INVASORAS 10
#define NUM_NAV_DEFENSORAS 1 // equivalente ao n�mero de clientes, um cliente por cada nave defensora
#define MAX_BOMBAS 4
#define NUM_BOMBAS (NUM_NAV_INVASORAS*MAX_BOMBAS)
#define MAX_TIROS 15
#define NUM_TIROS (NUM_NAV_DEFENSORAS*MAX_TIROS)
#define NUM_POWERUPS 4
#define NUM_POWERUPS_NAV_DEF 1
#define NUM_OBSTACULOS 10
//#define TMP_POS (NUM_NAV_INVASORAS + NUM_NAV_DEFENSORAS + NUM_BOMBAS + NUM_TIROS + NUM_POWERUPS + NUM_OBSTACULOS)

// taxa de disparo das naves invasoras, cada movimento desconta e quando chega a zero dispara bomba
#define TAXA_DISPARO_NAV_BASICAS 20 
#define TAXA_DISPARO_NAV_ESQUIVAS  8// 40 %
#define TAXA_DISPARO_NAV_INVASIVAS 6

// Probabilidades
#define PROB_NAV_INV_ESQUIVA 0.4
#define PROB_NAV_INV_INVASIVA 0.2
#define PROB_DESCER 0.2
#define PROB_LADOS 0.5
//#define PROB_BOMBA 0.3
#define PROB_POWERUP 0.1

// Mensagens
#define TEXTO 160

typedef struct {
	unsigned int	idJogador;
	TCHAR			msg[TEXTO];
	//HANDLE			hEvMsg;
} Mensagem;

// Estrutura de dados
// Coordenadas das naves no campo de jogo
typedef struct {
	unsigned int	x;
	unsigned int	y;
} Posicao; // coordenadas (nao se pode usar Coord, � reservado)

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

// Elemento de jogo - Extra
typedef struct {
	unsigned int	resistencia;
	Posicao			coord;
	Dimensao		dimensao;
} Obstaculo;

// Elemento de jogo - Nave Invasora
typedef struct {
	unsigned int	resistencia;
	unsigned int	velocidade;
	char			tipo; // b-> basica, e->esquiva,  i-> invasivo
	unsigned int	taxa_disparo;
	char			direcao;
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

// Elemento de jogo - Pontuacao de cada jogador - rever estes valores
typedef struct {
	unsigned int	nav_inv;
	unsigned int	nav_inv_b;
	unsigned int	nav_inv_e;
	unsigned int	nav_inv_i;
	unsigned int	nav_def;
	unsigned int	tiros;
	unsigned int	bombas;
	unsigned int	powerups;
	unsigned int	obstaculos;
	//unsigned int	pontos; // ?? de cada nav_def
} Pontuacao;

typedef struct {
	unsigned int	nivel; // ???? ser� assim para designar o n�vel / como fazer o incremento de dificuldade ????
	//unsigned int	In;
	//unsigned int	Out;
	NaveInvasora	naves_invasoras[NUM_NAV_INVASORAS];
	NaveDefensora	naves_defensoras[NUM_NAV_DEFENSORAS];
	Bomba			bombas[NUM_BOMBAS];
	Tiro			tiros[NUM_TIROS];
	PowerUp			powerups[NUM_POWERUPS];
	Obstaculo		obstaculos[NUM_OBSTACULOS];
	Pontuacao		pontuacoes[NUM_NAV_DEFENSORAS];
} Jogo;
