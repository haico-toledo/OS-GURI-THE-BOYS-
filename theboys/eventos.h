#ifndef EVENTO
#define EVENTO

#include "entidades.h"
#include "fprio.h"

struct E_chega {
	int tempo;
	struct heroi *heroi;
	struct base *b;
};

struct E_espera {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
};

struct E_desiste {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
};

struct E_avisa {
	int tempo;
	struct base *b;	
};

struct E_entra {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
};

struct E_sai {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
};

struct E_viaja {
	int tempo;
	struct heroi *heroi;
	struct base *d;	
};

struct E_morre {
	int tempo;
	struct heroi *heroi;
	struct base *b;	
};

struct E_missao {
	int tempo;
	struct missao *m;
};

struct E_fim {
	int tempo;
};

void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void avisa (int t, struct base *b, struct fprio_t *lef);

void entra (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void sai (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef);

void morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void missao (int t, struct missao *m, struct fprio_t *lef);

void fim (int t, struct fprio_t *lef);




#endif
