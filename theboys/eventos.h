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
	int h_id; //id do heroi
	struct base *b;	
	int tipo;
};

struct E_sai {
	int tempo;
	int h_id; //id do heroi
	struct base *b;	
	int tipo;
};

struct E_viaja {
	int tempo;
	struct heroi *h;
	struct base *b;	
	struct base *d;	
	int tipo;
};

struct E_morre {
	int tempo;
	struct heroi *h;
	struct base *b;	
	int tipo;
	int m_id; //id da missao 
};

struct E_missao {
	int tempo;
	struct missao *m;
	int tentativas;
	int tipo;
};

struct E_fim {
	int tempo;
	int tipo;
};


//executa o evento chega
void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef);
//cria e insere o evento chega
void insere_chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento espera
void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef);
//cria e insere o evento espera
void insere_espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento desiste
void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct base **bases);
//cria e insere o evento desiste
void insere_desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento avisa
void avisa (int t, struct base *b, struct fprio_t *lef);
//cria e insere o evento avisa
void insere_avisa (int t, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento entra
void entra (int t, int h_id, struct base *b, struct fprio_t *lef, struct heroi **herois);
//cria e insere o evento entra
void insere_entra (int t, int h_id, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento sai
void sai (int t, int h_id, struct base *b, struct fprio_t *lef, struct heroi **herois, struct base **bases);
//cria e insere o evento sai
void insere_sai (int t, int h_id, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento viaja
void viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef);
//cria e insere o evento viaja
void insere_viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef, int tipo);

//executa o evento morre
void morre (int t, int m_id, struct heroi *h, struct base *b, struct fprio_t *lef);
//cria e insere o evento morre
void insere_morre (int t, int m_id, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo);

//executa o evento missao
void missao (int t, int *n_v, int n_bases, struct missao *m, struct base **bases, struct heroi **herois, struct fprio_t *lef);
//cria e insere o evento missao
void insere_missao (int t, struct missao *m, struct fprio_t *lef, int tipo);

//executa o evento fim
void fim (int t, int e_t, struct heroi **herois, struct base **bases, struct missao **missoes);
//cria e insere o evento fim
void insere_fim (int t, struct fprio_t *lef, int tipo);





#endif
