#pragma once

#include <windows.h>
#include <tchar.h>

#ifdef BRIDGE_EXPORTS // mudar de DLL_EXPORTS -> ver em propriedades do project-> C\C++ -> Preprocessador
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif

extern "C" // usar em C ou C++
{
	extern DLL_IMP_API int nDLL;

	DLL_IMP_API int Teste(void);
	DLL_IMP_API int UmValor(int v);
	DLL_IMP_API int patrao();
	DLL_IMP_API int empregado();
}
