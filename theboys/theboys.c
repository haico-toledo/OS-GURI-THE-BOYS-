// programa principal do projeto "The Boys - 2024/2"
// Autor: HAICO DE TOLEDO BOEHS, GRR 20253482

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fprio.h"
#include "fila.h"
#include "eventos."
// seus #defines vão aqui

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


// programa principal
int main ()
{
  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

