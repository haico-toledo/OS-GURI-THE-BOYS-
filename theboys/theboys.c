// programa principal do projeto "The Boys - 2024/2"
// Autor: HAICO DE TOLEDO BOEHS, GRR 20253482

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	int n_herois;				// numero de herois
	struct heroi **herois;		// vetor com os herois
	int n_bases;				// numero de bases
	struct base **bases;		// vetor com as bases
	int n_missoes;				// numero de missoes a cumprir
	struct missao **missoes;	// vetor com as missoes
	int n_habilidades;			// numero de habilidades distintas
	int n_compostos_v;			// quantidade de composto V disponivel
	int tamanho_mundo_x;		// maior coordenada cartesiana
	int tamanho_mundo_y;		// maior coordenada cartesiana
	long relogio;				// tempo atual do mundo
};

//atribui os valores iniciais para os parametros
//do mundo
void inicializa_mundo (struct mundo *m) {
	m->n_herois = N_HEROIS;
	m->herois = malloc(sizeof(struct heroi) * N_HEROIS + 1);	//malloc vetor herois
	m->n_bases = N_BASES;
	m->bases = malloc(sizeof(struct base) * N_BASES + 1);		//malloc vetor bases
	m->n_missoes = N_MISSOES;
	m->missoes = malloc(sizeof(struct missao) * N_MISSOES + 1); //malloc vetor missoes
	m->n_habilidades = N_HABILIDADES;
	m->n_compostos_v = N_COMPOSTOS_V;
	m->tamanho_mundo_x = N_TAMANHO_MUNDO;
	m->tamanho_mundo_y = N_TAMANHO_MUNDO;
	m->relogio = T_INICIO;
}


// programa principal
int main ()
{
	struct mundo *m = malloc(sizeof(struct mundo));	//malloc mundo ** poderia ser uma funcao cria_mundo
	struct fprio_t *lef;
	int i, base_aux, tempo_aux, local_aux[2], continua = 1, tipo, prio;
	int eventos_tratados = 0;
	void *evento;
	struct E_chega *aux_chega;
	struct E_espera *aux_espera;
	struct E_desiste *aux_desiste;
	struct E_avisa *aux_avisa;
	struct E_entra *aux_entra;
	struct E_sai *aux_sai;
	struct E_viaja *aux_viaja;
	struct E_morre *aux_morre;
	struct E_missao *aux_missao;
	//struct E_fim *aux_fim;
	
	srand(time(NULL));
	
	// inicia o mundo
	inicializa_mundo(m);
	
	// cria e inicializa entidades
	
	//herois - podia ser funcao **
	for (i=0; i < N_HEROIS; i++) {					//malloc herois **
		m->herois[i] = H_cria(i); 
	}
	m->herois[N_HEROIS] = NULL;
	
	//bases	- podia ser funcao **				
	for (i=0; i < N_BASES; i++) {					//malloc bases **
		local_aux[0] = aleat(0, N_TAMANHO_MUNDO);
		local_aux[1] = aleat(0, N_TAMANHO_MUNDO);
		m->bases[i] = B_cria(i, local_aux); 
	}
	m->bases[N_BASES] = NULL;
	
	//missoes - podia ser funcao **
	for (i=0; i < N_MISSOES; i++) {					//malloc missoes **
		local_aux[0] = aleat(0, N_TAMANHO_MUNDO);
		local_aux[1] = aleat(0, N_TAMANHO_MUNDO);
		m->missoes[i] = MI_cria(i, local_aux); 
	}
	m->missoes[N_MISSOES] = NULL;
	
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
		evento = fprio_retira(lef, &tipo, &prio);
		eventos_tratados++;
		switch (tipo) {
			case TP_CHEGA:
				aux_chega = (struct E_chega *) evento;
				if (aux_chega->h->vivo)
					chega(prio, aux_chega->h, aux_chega->b, lef);
				free(aux_chega);
				break;
				
			case TP_ESPERA:
				aux_espera = (struct E_espera *) evento;
				if (aux_espera->h->vivo)
					espera(prio, aux_espera->h, aux_espera->b, lef);
				free(aux_espera);
				break;
			
			case TP_DESISTE:
				aux_desiste = (struct E_desiste *) evento;
				if (aux_desiste->h->vivo)
					desiste(prio, aux_desiste->h, aux_desiste->b, lef, m->bases);
				free(aux_desiste);
				break;
			
			case TP_AVISA:
				aux_avisa = (struct E_avisa *) evento;
				avisa(prio, aux_avisa->b, lef);
				free(aux_avisa);
				break;
				
			case TP_ENTRA:
				aux_entra = (struct E_entra *) evento;
				if (m->herois[aux_entra->h_id]->vivo)
					entra(prio, aux_entra->h_id, aux_entra->b, lef, m->herois);
				free(aux_entra);
				break;
				
			case TP_SAI:
				aux_sai = (struct E_sai *) evento;
				if (m->herois[aux_sai->h_id]->vivo)
					sai(prio, aux_sai->h_id, aux_sai->b, lef, m->herois, m->bases);
				free(aux_sai);
				break;
				
			case TP_VIAJA:
				aux_viaja = (struct E_viaja *) evento;
				if (aux_viaja->h->vivo)
					viaja(prio, aux_viaja->h, aux_viaja->b, aux_viaja->d, lef);
				free(aux_viaja);
				break;
				
			case TP_MORRE:
				aux_morre = (struct E_morre *) evento;
				if (aux_morre->h->vivo)
					morre(prio, aux_morre->m_id, aux_morre->h, aux_morre->b, lef);
				free(aux_morre);
				break;
				
			case TP_MISSAO:
				aux_missao = (struct E_missao *) evento;
				missao(prio, &m->n_compostos_v, m->n_bases, aux_missao->m, m->bases, m->herois, lef);
				free(aux_missao);
				break;
			
			case TP_FIM:
				//aux_fim = (struct E_fim *) evento;
				fim(prio, eventos_tratados, m->herois, m->bases, m->missoes);
				continua = 0;
				break;
		}
	
	}	
	
	
	  

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

