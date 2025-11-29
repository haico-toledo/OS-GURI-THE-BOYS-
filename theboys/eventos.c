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

//retorna o quadrado da distancia cartesiana entre dois pontos
int dist_cart (int xi, int yi, int xi, int xii) {
	int dist = (xi - xii)*(xi - xii) + (yi - yii)*(yi - yii);
		if (dist >= 0)
			return dist;
		else
			return -dist; 
} 

//ordena as bases de acordo com a distancia de uma missao dada
void ordena_bases(struct base **bases, int local_m[2], int n_bases)
{
	struct base *aux;
	int i, j, menor;
	
	for (i = 0; i < n - 1; i++)
	{
		menor = i;
		for (j = i + 1; j < n; j++)
		{
			//distancia da bmp for maior que da base j
			if (dist_cart(bases[menor]->local[0], local_m[0], bases[menor]->local[1], local_m[1]) > dist_cart(bases[j]->local[0], local_m[0], bases[j]->local[1], local_m[1])) 
				menor = j;    
		}
		
		aux = (*)bases[i];
		bases[i] = bases[menor];
		(*)bases[menor] = aux;
	}
}


void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
	
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


void insere_chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
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


void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct heroi **herois) {
	fila_insere (b->espera, h->id);
	
	insere_avisa(t, b, lef, herois, tipo);
}


void insere_espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
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


void desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct base **bases) {
	int nova_base = aleat(0, N_BASES-1);
	
	insere_viaja(t, h, bases[nova_base], lef, TP_VIAJA);
}


void insere_desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
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


void avisa (int t, struct base *b, struct fprio_t *lef, struct heroi **herois) {
	int id_ret;
	
	while(!B_cheia(b) && !B_espera_vazia(b)) {
		 fila_retira (b->espera, id_ret);		//funcao tinha retorno int e retorno por parametro *item **
		 cjto_insere (b->presentes, id_ret);
		 insere_entra(t, id_ret, b, lef, herois, TP_ENTRA);
	}
}


void insere_avisa (int t, struct base *b, struct fprio_t *lef) {
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


void entra (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois) {
	int tpb = 15 + herois[id]->paciencia * aleat(1, 20);
	
	insere_sai(t + tpb, id, b, lef, herois, TP_SAI);	
}


void insere_entra (int t, int H_id, struct base *b, struct fprio_t *lef) {
	struct E_entra *e = malloc(sizeof(struct E_entra));

	if (!e)
		return;
	//atribui os parametros ao novo evento
	e->tempo = t;
	e->H_id = H_id;
	e->b = b;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}


void sai (int t, int id, struct base *b, struct fprio_t *lef, struct heroi **herois) {
	int nova_base;
	
	cjto_retira (b->presentes, id);
	
	nova_base = aleat(0, N_BASES-1);
	insere_viaja(t, herois[id], bases[nova_base], lef, TP_VIAJA); 
	insere_avisa(t, b, lef, herois, TP_AVISA);
}


void insere_sai (int t, int H_id, struct base *b, struct fprio_t *lef) {
	struct E_sai *s = malloc(sizeof(struct E_sai));

	if (!s)
		return;
	//atribui os parametros ao novo evento
	s->tempo = t;
	s->H_id = H_id;
	s->b = b;
	s->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, s, tipo, t);
}


void viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef) {
	int dist, dura;
	
	dist = dist_cart(d->local[0], d->local[1], b->local[0], b->local[1]);
	dura = dist/h->velocidade;
	insere_chega(t + dura, h, b, d, lef, TP_CHEGA);
}


void insere_viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef) {
	struct E_viaja *v = malloc(sizeof(struct E_viaja));

	if (!v)
		return;
	//atribui os parametros ao novo evento
	v->tempo = t;
	v->h = h;
	v->b = b;
	v->d = d;
	v->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, v, tipo, t);
}


void morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef, struct heroi **herois) {	
	cjto_retira(b->presentes, h->id);
	
	h->vivo = 0;
	
	insere_avisa(t, b, lef, herois);
}


void insere_morre (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
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


void missao (int t, int *n_v, int n_bases, struct missao *m, struct base **bases, struct heroi **herois, struct fprio_t *lef) {
	int bmp, achou = 0, i, j;
	struct cjto_t *aux = cjto_cria(N_HABILIDADES);
	
	//ordena bases por distancia
	ordena_bases(bases, m->local, n_bases);
	
	//acha bmp
	i = 0;
	while (i < N_BASES && !achou) {
		for (j=0; j < N_HEROIS; j++)
			aux = cjto_uniao(aux, herois[j]->habilidades);
		if (cjto_contem(aux, m->habilidades))
			achou = 1;
	}
	
	if (achou) {
		bmp = i;
		//aumentar a xp dos herois da bmp
		for (i=0; i < N_HEROIS; i++) {
			if (cjto_pertence(bases[bmp]->presentes, i))
				herois[i]->xp++;
		}
		m->feita = 1;
	}
	
	else
		bmp = bases[0];
		if (n_v > 0 && t % 2500 == 0) {
			n_v--;
			m->feita = 1;
			//mata o mais xp da base
		}
}


void insere_missao (int t, struct missao *m, struct fprio_t *lef) {
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


void fim (int t, struct fprio_t *lef);

void insere_fim (int t, struct fprio_t *lef) {
	struct E_fim *f = malloc(sizeof(struct E_fim));

	if (!f)
		return;
	//atribui os parametros ao novo evento
	f->tempo = t;
	f->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, f, tipo, t);
}
