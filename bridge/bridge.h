#pragma once

#include <windows.h>
#include <tchar.h>

#include "../dados.h"

#ifdef BRIDGE_EXPORTS
#define BRIDGE_API __declspec(dllexport)
#else
#define BRIDGE_API __declspec(dllimport)
#endif

// Mémoria partilhada: Jogo
Jogo BRIDGE_API *CriaMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo);
Jogo BRIDGE_API *AcedeMemoriaPartilhadaJogo(HANDLE *hMapMemParJogo, LARGE_INTEGER *tam_jogo);

// Semaforo do Jogo
void BRIDGE_API CriaSemaforoEscreveJogo(HANDLE *SemEscreveJogo);
void BRIDGE_API AcedeSemaforoEscreveJogo(HANDLE *SemEscreveJogo);
void BRIDGE_API CriaSemaforoLerJogo(HANDLE *SemLerJogo);
void BRIDGE_API AcedeSemaforoLerJogo(HANDLE *SemLerJogo);

// // Mémoria partilhada: Mensagens
//Mensagem BRIDGE_API * MemoriaPartilhadaMensagens(HANDLE	hMapMemParMsg, LARGE_INTEGER tam_mensagem);

// Semaforo das Mensagens
// Create SemMensagens
// Open SemMensagens

void BRIDGE_API gotoxy(int x, int y);