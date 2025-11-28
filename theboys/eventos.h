#ifndef EVENTO
#define EVENTO

#include "entidades.h"
#include "fprio.h"


struct E_chega {
	int tempo;
	struct heroi *h;
	struct base *b;
	int tipo;
};

struct E_espera {
	int tempo;
	struct heroi *h;
	struct base *b;	
	int tipo;
};

struct E_desiste {
	int tempo;
	struct heroi *h;
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
	struct heroi *h;
	struct base *b;	
	int tipo;
};

struct E_sai {
	int tempo;
	struct heroi *h;
	struct base *b;	
	int tipo;
};

struct E_viaja {
	int tempo;
	struct heroi *h;
	struct base *d;	
	int tipo;
};

struct E_morre {
	int tempo;
	struct heroi *h;
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


//executa o evento chega
void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);
//cria e insere o evento chega
void insere_chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento espera
void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo);
//cria e insere o evento espera
void insere_espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento desiste
void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);
//cria e insere o evento desiste
void insere_desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento avisa
void avisa (int t, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo);
//cria e insere o evento avisa
void insere_avisa (int t, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento entra
void entra (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo);
//cria e insere o evento entra
void insere_entra (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento sai
void sai (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo);
//cria e insere o evento sai
void insere_sai (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento viaja
void viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef, int *tipo);
//cria e insere o evento viaja
void insere_viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef, int *tipo);

//executa o evento morre
void morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);
//cria e insere o evento morre
void insere_morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);

//executa o evento missao
void missao (int t, struct missao *m, struct fprio_t *lef, int *tipo);
//cria e insere o evento missao
void insere_missao (int t, struct missao *m, struct fprio_t *lef, int *tipo);

//executa o evento fim
void fim (int t, struct fprio_t *lef, int *tipo);
//cria e insere o evento fim
void insere_fim (int t, struct fprio_t *lef, int *tipo);





#endif
