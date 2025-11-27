#ifndef EVENTO
#define EVENTO

#include "entidades.h"
#include "fprio.h"

struct E_chega {
	int tempo;
	struct heroi *heroi;
	struct base *b;
	int tipo;
};

struct E_espera {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
	int tipo;
};

struct E_desiste {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
	int tipo;
};

struct E_avisa {
	int tempo;
	struct base *b;	
	int tipo;
};

struct E_entra {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
	int tipo;
};

struct E_sai {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
	int tipo;
};

struct E_viaja {
	int tempo;
	struct heroi *heroi;
	struct base *d;	
	int tipo;
};

struct E_morre {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
	int tipo;
};

struct E_missao {
	int tempo;
	struct missao *m;
	int tipo;
};

struct E_fim {
	int tempo;
	int tipo;
};

void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void avisa (int t, struct base *b, struct fprio_t *lef, int tipo);

void entra (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void sai (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef, int tipo);

void morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

void missao (int t, struct missao *m, struct fprio_t *lef, int tipo);

void fim (int t, struct fprio_t *lef, int tipo);




#endif
