#pragma once

#include <windows.h>
#include <tchar.h>

#include "../dados.h"

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

Jogo BRIDGE_API *CriaMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo);
Jogo BRIDGE_API *AcedeMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo);

// Mensagens
//Mensagem BRIDGE_API * MemoriaPartilhadaMensagens(HANDLE	hMapMemParMsg, LARGE_INTEGER tam_mensagem);

void BRIDGE_API gotoxy(int x, int y);