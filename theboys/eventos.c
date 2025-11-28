#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "entidades.h"
#include "fprio.h"
//pode precisar de mais includes
#define TP_CHEGA       0
#define TP_ESPERA      1
#define TP_DESISTE     2
#define TP_AVISA       3
#define TP_ENTRA       4
#define TP_SAI         5
#define TP_VIAJA       6
#define TP_MORRE       7
#define TP_MISSAO      8
#define TP_FIM         9 
#define N_HABILIDADES  10
#define N_HEROIS       (N_HABILIDADES * 5)
#define N_BASES        (N_HEROIS / 5)


void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	
	h->base = b;
	
	int espera;
	
	if (!B_cheia && B_espera_vazia)
		espera = 1;	
	else
		espera = (h->paciencia) > (10 * fila_tamanho(b->espera));
	
	if (espera)
		insere_espera(t, h, b, lef, TP_ESPERA );
	else
		insere_desiste(t, h, b, lef, TP_DESISTE);
}

//cria e insere um evento chega
void insere_chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_chega *c = malloc(sizeof(struct E_chega));
	
	if (!c)
		return;
	//atribui os parametros ao novo chega
	c->tempo = t;
	c->h = h;
	c->b = b;
	c->tipo = tipo;
	
	//insere o evento na lef
	fprio_insere (lef, c, tipo, t);
}

//executa o evento espera
void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct heroi **herois int *tipo) {
	fila_insere (b->espera, h->id);
	
	insere_avisa(t, b, lef, herois, tipo);
}

//cria e insere um evento espera
void insere_espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_espera *e = malloc(sizeof(struct E_espera));

	if (!e)
		return;
	//atribui os parametros ao novo espera
	e->tempo = t;
	e->h = h;
	e->b = b;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}

//executa o evento desiste
void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct base **bases int *tipo) {
	int nova_base = aleat(0, N_BASES-1);
	
	insere_viaja(t, h, bases[nova_base], lef, TP_VIAJA);
}

//cria e insere um evento desiste
void insere_desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_desiste *d = malloc(sizeof(struct E_desiste));

	if (!d)
		return;
	//atribui os parametros ao novo evento
	d->tempo = t;
	d->h = h;
	d->b = b;
	d->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, d, tipo, t);
}

//executa o evento avisa
void avisa (int t, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo) {
	int id_ret;
	
	while(!B_cheia(b) && !B_espera_vazia(b)) {
		 fila_retira (b->espera, id_ret);		//funcao tinha retorno int e retorno por parametro *item **
		 cjto_insere (b->presentes, id_ret);
		 insere_entra(t, id_ret, b, lef, herois, TP_ENTRA);
	}
}

//cria e insere um evento avisa
void insere_avisa (int t, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_avisa *a = malloc(sizeof(struct E_avisa));

	if (!a)
		return;
	//atribui os parametros ao novo evento
	a->tempo = t;
	a->b = b;
	a->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, a, tipo, t);
}

//executa o evento entra
void entra (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo) {
	int tpb = 15 + herois[id]->paciencia * aleat(1, 20);
	
	insere_sai(t + tpb, id, b, lef, herois, TP_SAI);	
}

//cria e insere um evento entra
void insere_entra (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_entra *e = malloc(sizeof(struct E_entra));

	if (!e)
		return;
	//atribui os parametros ao novo evento
	e->tempo = t;
	e->h = h;
	e->b = b;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}

//executa o evento sai
void sai (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois, int *tipo) {
	int nova_base;
	
	cjto_retira (b->presentes, id);
	
	nova_base = aleat(0, N_BASES-1);
	insere_viaja(t, herois[id], bases[nova_base], lef, TP_VIAJA); 
	insere_avisa(t, b, lef, herois, TP_AVISA);
}

//cria e insere um evento sai
void insere_sai (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_sai *s = malloc(sizeof(struct E_sai));

	if (!s)
		return;
	//atribui os parametros ao novo evento
	s->tempo = t;
	s->h = h;
	s->b = b;
	s->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, s, tipo, t);
}

//executa o evento viaja
void viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef, int *tipo);
//cria e insere um evento viaja
void insere_viaja (int t, struct heroi *h, struct base *d, struct fprio_t *lef, int *tipo) {
	struct E_viaja *v = malloc(sizeof(struct E_viaja));

	if (!v)
		return;
	//atribui os parametros ao novo evento
	v->tempo = t;
	v->h = h;
	v->d = d;
	v->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, v, tipo, t);
}

//executa o evento morre
void morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo);
//cria e insere um evento morre
void insere_morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int *tipo) {
	struct E_morre *m = malloc(sizeof(struct E_morre));

	if (!m)
		return;
	//atribui os parametros ao novo evento
	m->tempo = t;
	m->h = h;
	m->b = b;
	m->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, m, tipo, t);
}

//executa o evento missao
void missao (int t, struct missao *m, struct fprio_t *lef, int *tipo);
//cria e insere um evento missao
void insere_missao (int t, struct missao *m, struct fprio_t *lef, int *tipo) {
	struct E_missao *e = malloc(sizeof(struct E_missao));

	if (!e)
		return;
	//atribui os parametros ao novo evento
	e->tempo = t;
	e->m = m;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}

//executa o evento fim
void fim (int t, struct fprio_t *lef, int *tipo);
//cria e insere um evento fim
void insere_fim (int t, struct fprio_t *lef, int *tipo) {
	struct E_fim *f = malloc(sizeof(struct E_fim));

	if (!f)
		return;
	//atribui os parametros ao novo evento
	f->tempo = t;
	f->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, f, tipo, t);
}
