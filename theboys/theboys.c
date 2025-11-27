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
#define TRES_DIAS		   4320
#define TP_CHEGA    0
#define TP_ESPERA   1
#define TP_DESISTE  2
#define TP_AVISA    3
#define TP_ENTRA    4
#define TP_SAI      5
#define TP_VIAJA    6
#define TP_MORRE    7
#define TP_MISSAO   8
#define TP_FIM      9 
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
	m->tamanho_mundo[0] = N_TAMANHO_MUNDO;
	m->tamanho_mundo[1] = N_TAMANHO_MUNDO;
	m->relogio = T_INICIO;
}


// programa principal
int main ()
{
	struct mundo *m = malloc(sizeof(struct mundo));	//malloc mundo ** poderia ser uma funcao cria_mundo
	struct fprio_t *lef;
	int i;
	int base_aux;
	int tempo_aux;
	int local_aux[2];
	int continua = 1;	
	
	
	// inicia o mundo
	inicializa_mundo(m);
	
	// cria e inicializa entidades
	
	//herois - podia ser funcao **
	for (i=0; i < N_HEROIS; i++) {					//malloc herois **
		m->herois[i] = H_cria(i); 
	}
	
	//bases	- podia ser funcao **				
	for (i=0; i < N_BASES; i++) {					//malloc bases **
		local_aux[0] = aleat(0, N_TAMANHO_MUNDO);
		local_aux[1] = aleat(0, N_TAMANHO_MUNDO);
		m->bases[i] = B_cria(i, local); 
	}
	
	//missoes - podia ser funcao **
	for (i=0; i < N_MISSOES; i++) {					//malloc missoes **
		local_aux[0] = aleat(0, N_TAMANHO_MUNDO);
		local_aux[1] = aleat(0, N_TAMANHO_MUNDO);
		m->missoes[i] = MI_cria(i, local); 
	}
	
	//cria e inicializa a lef
	lef = fprio_cria();
	
	//atribui base aos herois nos tres primeiros dias - podia ser funcao **
	for (i=0; i < N_HEROIS; i++) {
		base_aux = aleat(0, N_BASES-1);
		tempo_aux = aleat(0, TRES_DIAS);
		insere_chega(tempo_aux, m->herois[i], m->bases[base_aux], lef, TP_CHEGA);
	}
	
	//insere as missoes na lef
	for (i=0; i < N_MISSOES; i++) {
		tempo_aux = aleat(0, T_FIM_DO_MUNDO);
		insere_missao(tempo_aux, m->missoes[i], lef, TP_MISSAO);
	}
	
	//insere evento fim no final da lef
	insere_fim(T_FIM_DO_MUNDO, lef, TP_FIM);
	
	//loop principal
	while (continua) {
	
	}	
	
	
	  

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

