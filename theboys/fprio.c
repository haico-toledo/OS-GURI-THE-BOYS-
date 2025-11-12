// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  struct fpnodo_t *fim; // nao uso no tad mas pode ser util
  int num ;         // número de itens na fila
} ;

// A COMPLETAR

struct fprio_t *fprio_cria ()
{
	struct fprio_t *fp;
	fp = malloc(sizeof(struct fprio_t));
	
	if (!fp)
		return NULL;
	
	fp->num = 0;
    fp->fim = NULL;
	fp->prim = NULL;
	
	return fp;
}


struct fprio_t *fprio_destroi (struct fprio_t *f)
{
	if (!f)
		return NULL;
		
	struct fpnodo_t *aux;
	struct fpnodo_t *ptr;
	
    ptr = f->prim;

	/*incrementa iterador e libera nodo anterior*/
    while ((ptr != NULL))
    {
        aux = ptr;
        ptr = ptr->prox;
        free(aux->item);
        free(aux);    
    }

    free(f);
    f = NULL;
    
    return NULL;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
    if (!f || !item)
        return -1;
    
    struct fpnodo_t *atual;
    struct fpnodo_t *anterior;
    struct fpnodo_t *novo;
    
    /* verifica se já existe*/
    atual = f->prim;
    while (atual != NULL)
    {
        if (atual->item == item)
            return -1;
        atual = atual->prox;
    }
    
    /* cria o novo nodo */
    novo = malloc(sizeof(struct fpnodo_t));
    if (!novo)
        return -1;
    
    novo->item = item;
    novo->tipo = tipo;
    novo->prio = prio;
    novo->prox = NULL;
    
    /*fila vazia */
    if (f->prim == NULL)
    {
        f->prim = novo;
        f->num++;
        return f->num;
    }
    
    /*insere no início*/
    if (prio < f->prim->prio)
    {
        novo->prox = f->prim;
        f->prim = novo;
        f->num++;
        return f->num;
    }
    
    /*insere normal*/
    anterior = f->prim;
    atual = f->prim->prox;
    while (atual != NULL && atual->prio <= prio)
    {
        anterior = atual;
        atual = atual->prox;
    }
    novo->prox = anterior->prox;
    anterior->prox = novo;
    f->num++;
    
    return f->num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
	if (!f || !f->prim || !tipo || !prio)
		return NULL;
		
	struct fpnodo_t *aux;
	void *retirado;
	
	/* guarda os valores*/
	*tipo = f->prim->tipo;
	*prio = f->prim->prio;
	retirado = f->prim->item;
	
	/* remove o primeiro nodo*/
	aux = f->prim;
	f->prim = f->prim->prox;
	free(aux);
	f->num--;
	
	return retirado;
}

int fprio_tamanho (struct fprio_t *f)
{
	if (!f)
		return -1;
	
	return f->num;
}


void fprio_imprime (struct fprio_t *f)
{	
	if (!f)
		return;

	struct fpnodo_t *aux;
	
	/*fp de tamanho 0*/
	if (!f->prim)
		return;

	aux = f->prim;
	
	/*fp de tamanho 1*/
	if (!aux->prox)
	{
		printf("(%d %d)", aux->tipo, aux->prio);
		return;
	}	
	
	/*caso geral*/
	while (aux->prox->prox != NULL)
	{
		printf("(%d %d) ", aux->tipo, aux->prio);
		
		aux = aux->prox;
	}
	
	printf("(%d %d) ", aux->tipo, aux->prio);	
	printf("(%d %d)", aux->prox->tipo, aux->prox->prio);
	
	return;
}

