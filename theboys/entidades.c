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

int H_id (struct heroi)
	return heroi->id;
	
struct cjto_t H_habilidades (struct heroi)
	return hero->habilidades;
	
int H_paciencia (struct heroi)
	return heroi->paciencia;
	
int H_velocidade (struct heroi)
	return heroi->velocidade;
	
int H_xp (struct heroi)
	return heroi->xp;

int H_base (struct heroi)
	return heroi->base;

int H_inicializa (struct heroi h, int id) {
	heroi->id = id;	
	heroi->xp = 0;
	heroi->paciencia = aleat(MIN_PAC, MAX_PAC);											//paciencia entre 0 e 100
	heroi->velocidade = aleat(MIN_VEL, MAX_VEL); 										//velocidade entre 50 e 5000
	heroi->habilidades = cjto_aleat(aleat(MIN_HAB_HEROI, MAX_HAB_HEROI), N_HAB_TOTAL);	//sorteia de 1 a 3 habilidades das 10 possiveis
}
	
//incrementa 1 de xp
void H_incrementa_xp (struct heroi h) {
	heroi->xp++;
}

//altera a base atual do heroi
void H_muda_base (struct heroi h, struct base nova) {
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

int B_id (struct base)
	return base->id;
	
int B_lotacao (struct base)
	return base->lotacao;

struct cjto_t B_presentes (struct base)
	return base->presentes;

struct cjto_t B_espera (struct base)
	return base->espera;

int *B_local (struct base)
	return base->local;
	
void B_altera_lotacao (struct base b, int controle) {
	if (controle)
		b->lotacao++;
	else
		b->lotacao--;
}

void B_insere_heroi (struct base b, struct heroi h) {
	cjto_insere(&b, h->id);
}

void B_remove_heroi (struct base b, struct heroi h) {
	cjto_retira(&b, h->id);
}

void B_insere_fila (struct base b, struct heroi h) {
	fila_insere(b->espera, h->id);
}

void B_remove_fila (struct base b, struct heroi h) {
	fila_retira(b->espera, h->id);
}


//missao

struct missao {
	int *id; 					// identificador numerico
	struct cjto_t *habilidades;	// conjunto de habilidades necessarias
	int *local[2];				// localizacao cartesiana da missao
};

int MI_id (struct missao)
	return missao->id;
	
struct cjto_t MI_habilidades (struct missao)
	return missao->habilidades;
	
int *MI_local (struct missao)
	return missao->local;

