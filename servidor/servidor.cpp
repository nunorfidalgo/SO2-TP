#include "servidor.h"

int inicia_naves(TCHAR *argv) {
	////int i;
	//naves_invasoras = calloc(NUM_INVASORAS, sizeof(NAVE));
	//if (naves_invasoras == NULL) {
	//	_tprintf(TEXT("\n%s: Erro na alocacao de memoria das naves invasoras"), argv);
	//	return 1;
	//}
	///*for (i = 0; i < N_INVASORAS; i++) {
	//naves_invasoras[i].tamanho = 0;
	//naves_invasoras[i].x = 0;
	//naves_invasoras[i].y = 0;
	//naves_invasoras[i].powerup = 0;
	//naves_invasoras[i].powerupType = 'n';
	//}*/
	//naves_defensoras = calloc(NUM_DEFENSORAS, sizeof(NAVE));
	//if (naves_defensoras == NULL) {
	//	_tprintf(TEXT("\n%s: Erro na alocacao de memoria das naves defensoras!"), argv);
	//	return 1;
	//}
	///*for (i = 0; i < N_DEFENSORAS; i++) {
	//naves_defensoras[i].tamanho = 0;
	//naves_defensoras[i].x = 0;
	//naves_defensoras[i].y = 0;
	//naves_defensoras[i].powerup = 0;
	//naves_defensoras[i].powerupType = 'n';
	//}*/
	return 0;
}

//void mostra_naves(NAVE *equipa, int tamanho) {
//int i;
//for (i = 0; i < tamanho; i++)
//	_tprintf(TEXT("\n[Nave]: id=%d, tamnho=%d, x=%d, y=%d, powerup=%d, powerupType=%c;"), i, equipa[i].tamanho, equipa[i].x, equipa[i].y, equipa[i].powerup, equipa[i].powerupType);
//}

int _tmain(int argc, TCHAR *argv[]) {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	system("cls");
	_tprintf(TEXT("%s: pronto..."), argv[0]);

	//Chamar a funcao da Dll
	//Teste();
	//_tprintf(TEXT("\nValor: %d"), UmValor(45));

	//_tprintf(TEXT("\nBridge: A executar patrao..."));
	//patrao();

	inicia_naves(argv[0]);

	//_tprintf(TEXT("\n%s: Naves Invasoras:"), argv[0]);
	//mostra_naves(naves_invasoras, NUM_INVASORAS);
	//_tprintf(TEXT("\n%s: Naves Defensoras:"), argv[0]);
	//mostra_naves(naves_defensoras, NUM_DEFENSORAS);

	_tprintf(TEXT("\n%s: terminou..."), argv[0]);
	return 0;
}