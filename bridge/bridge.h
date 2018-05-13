#pragma once

#include <windows.h>
#include <tchar.h>
#include "../dados.h"

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

extern "C" {
	// Funcões de teste
	int BRIDGE_API Teste(void);
	int BRIDGE_API UmValor(int v);

	// Mostrar a informação dos dados de jogo
	void BRIDGE_API mostra_naves_invasoras(NaveInvasora *naves_invasoras);
	void BRIDGE_API mostra_naves_defensoras(NaveDefensora *naves_defensoras);
	void BRIDGE_API mostra_bombas(Bomba *bombas);
	void BRIDGE_API mostra_tiros(Tiro *tiros);
	void BRIDGE_API mostra_powerups(PowerUp *powerups);
	void BRIDGE_API mostra_pontuacoes(Pontuacao *pontuacoes);
	void BRIDGE_API mostra_obstaculos(Obstaculo *obstaculos);
	void BRIDGE_API mostra_jogo_na_consola(Jogo *jogo);

	// 
	Jogo BRIDGE_API * MemoriaPartilhadaJogo(HANDLE &hMapMemParJogo, LARGE_INTEGER &tam_jogo);

	// Mensagens
	Mensagem BRIDGE_API * MemoriaPartilhadaMensagens(HANDLE	&hMapMemParMsg, LARGE_INTEGER &tam_mensagem);
	void BRIDGE_API escreve_msgs(int id);
	void BRIDGE_API le_msgs();
	void BRIDGE_API EscreveMensagens(int idJogador, Mensagem *mensagens, HANDLE hEvMsg);
	void BRIDGE_API LeMensagens(Mensagem *mensagens, HANDLE hEvMsg);

	void BRIDGE_API gotoxy(int x, int y);
}