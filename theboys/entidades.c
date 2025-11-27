#include "entidades.h"
#include "conjunto.h"
#include "fila.h"
#define MIN_PAC 0
#define MAX_PAC 100
#define MIN_VEL 50
#define MAX_VEL 5000
#define MIN_HAB_HEROI 1
#define MAX_HAB_HEROI 3
#define N_HAB_TOTAL 10
#define MIN_LOT_BASE 3
#define MAX_LOT_BASE 10
#define MIN_HAB_MISSAO 6

int aleat (int min, int max) 
	return rand() % (max - min + 1) + min;

//heroi

struct heroi {
	int *id; 					// identificador numerico 
	struct cjto_t *habilidades;	// conjunto de habilidades 
	int *paciencia; 			// nivel de paciencia 
	int *velocidade;			// velocidade de deslocamento
	int *xp; 					// qtd de missoes ja feitas
	int *base; 					// id da base atual
};

struct heroi *H_cria (int id) {
	struct heroi *h = malloc(sizeof(struct heroi));
	h->id = id;
	
	return h;
	
}

void H_destroi (struct heroi *h) {
	free(h);
	h = NULL;
}

int H_id (struct heroi *h) {
	return h->id;
}

struct cjto_t H_habilidades (struct heroi *h) {
	return h->habilidades;
}

int H_paciencia (struct heroi *h) {
	return h->paciencia;
}

int H_velocidade (struct heroi *h) {
	return h->velocidade;
}

int H_xp (struct heroi *h) {
	return h->xp;
}

int H_base (struct heroi *h) {
	return h->base;
}

int H_inicializa (struct heroi *h, int id) {
	h->id = id;	
	h->xp = 0;
	h->paciencia = aleat(MIN_PAC, MAX_PAC);											//paciencia entre 0 e 100
	h->velocidade = aleat(MIN_VEL, MAX_VEL); 										//velocidade entre 50 e 5000
	h->habilidades = cjto_aleat(aleat(MIN_HAB_HEROI, MAX_HAB_HEROI), N_HAB_TOTAL);	//sorteia de 1 a 3 habilidades das 10 possiveis
}
	
//incrementa 1 de xp
void H_incrementa_xp (struct heroi *h) {
	h->xp++;
}

//altera a base atual do heroi
void H_muda_base (struct heroi *h, struct base *nova) {
	heroi->base = nova;
}


//base

struct base {
	int *id;					// identificador numerico
	int *lotacao;				// maximo de herois 
	struct cjto_t *presentes;	// conjunto de herois na base
	struct fila_t *espera;		// fila de herois esperando para entrar
	int *local[2];				// localizacao cartesiana da base
};

struct base *B_cria (int id, int local[2]) {
	struct base *b = malloc(sizeof(struct base));
	b->id = id;
	b->local = local;
	
	return b;
}


int B_id (struct base *b) {
	return b->id;
}
	
	
int B_lotacao (struct base *b) {
	return b->lotacao;
}

struct cjto_t B_presentes (struct base *b) {
	return b->presentes;
}

struct cjto_t B_espera (struct base *b) {
	return b->espera;
}

int *B_local (struct base *b) {
	return b->local;
}

void B_altera_lotacao (struct base *b, int controle) {
	if (controle)
		b->lotacao++;
	else
		b->lotacao--;
}

void B_insere_heroi (struct base *b, struct heroi *h) {
	cjto_insere(&b, h->id);
}

void B_remove_heroi (struct base *b, struct heroi *h) {
	cjto_retira(&b, h->id);
}

void B_insere_fila (struct base *b, struct heroi *h) {
	fila_insere(b->espera, h->id);
}

void B_remove_fila (struct base *b, struct heroi *h) {
	fila_retira(b->espera, h->id);
}

int B_cheia (struct base *b) {
	if (cjto_card(b->presentes) == b->lotacao)
		return 1;
		
	return 0;
}	

int B_espera_vazia (struct base *b) {
	if (fila_tamanho(b->espera) == 0)
		return 1;
		
	return 0;
}

void B_inicializa (struct base *b, int id, int local[2]) {
	b->id = id;
	b->local = local;
	b->lotacao = aleat(MIN_LOT_BASE, MAX_LOT_BASE);
	b->presentes = cjto_cria(b->lotacao);
	b->espera = fila_cria();
}

//missao

struct missao {
	int *id; 					// identificador numerico
	struct cjto_t *habilidades;	// conjunto de habilidades necessarias
	int *local[2];				// localizacao cartesiana da missao
};

int MI_id (struct missao *m) {
	return m->id;
}

struct cjto_t MI_habilidades (struct missao *m) {
	return m->habilidades;
}

int *MI_local (struct missao *m) {
	return m->local;
}

int MI_inicializa (struct missao *m, int id, int local[2]) {
	m->id = id;
	m->local = local;
	m->habilidades = cjto_aleat(aleat(MIN_HAB_MISSAO, N_HAB_TOTAL), N_HAB_TOTAL);
}
