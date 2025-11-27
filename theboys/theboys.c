// programa principal do projeto "The Boys - 2024/2"
// Autor: HAICO DE TOLEDO BOEHS, GRR 20253482

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fprio.h"
#include "fila.h"
#include "eventos.h"
#include "entidades.h"

// seus #defines vão aqui

#define T_INICIO           0
#define T_FIM_DO_MUNDO     525600
#define N_TAMANHO_MUNDO    20000
#define N_HABILIDADES      10
#define N_HEROIS           (N_HABILIDADES * 5)
#define N_BASES            (N_HEROIS / 5)
#define N_MISSOES          (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V      (N_HABILIDADES * 3)

// minimize o uso de variáveis globais

struct mundo {
	int *n_herois;				// numero de herois
	struct heroi **herois;		// vetor com os herois
	int *n_bases;				// numero de bases
	struct base **bases;		// vetor com as bases
	int *n_missoes;				// numero de missoes a cumprir
	struct missao **missoes;	// vetor com as missoes
	int *n_habilidades;			// numero de habilidades distintas
	int *n_compostos_v;			// quantidade de composto V disponivel
	int *tamanho_mundo;			// maior coordenada cartesiana
	long *relogio;				// tempo atual do mundo
}

//atribui os valores iniciais para os parametros
//do mundo
void inicializa_mundo (struct mundo *m) {
	m->n_herois = N_HEROIS;
	m->n_bases = N_BASES;
	m->n_missoes = N_MISSOES;
	m->n_habilidades = N_HABILIDADES;
	m->n_compostos_v = N_COMPOSTOS_V;
	m->tamanho_mundo = N_TAMANHO_MUNDO;
	m->relogio = T_INICIO;
}


// programa principal
int main ()
{
	struct mundo *m = malloc(sizeof(struct mundo));	//malloc mundo **
	
  // iniciar o mundo
  inicializa_mundo(m);
  
  

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

