#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria () {
	struct fila_t *f;
	f = malloc(sizeof(struct fila_t));
	
	if (!f)
		return NULL;
		
	f->prim = NULL;
	f->ult = NULL;
	f->num = 0;
	
	return f;
}

struct fila_t *fila_destroi (struct fila_t *f) {
	if (!f)
		return NULL;
		
	struct fila_nodo_t *aux;
	struct fila_nodo_t *ptr;
	
    ptr = f->prim;

	/*incrementa iterador e libera nodo anterior*/
    while ((ptr != NULL))
    {
        aux = ptr;
        ptr = ptr->prox;
        free(aux);    
    }

    free(f);
    f = NULL;
    
    return NULL;
}

int fila_insere (struct fila_t *f, int item) {
	if (!f)
        return 0;
    
    struct fila_nodo_t *atual;
    struct fila_nodo_t *novo;
    
    /* verifica se já existe*/
    atual = f->prim;
    while (atual != NULL)
    {
        if (atual->item == item)
            return 0;
        atual = atual->prox;
    }
    
    /* cria o novo nodo */
    novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
        return 0;
    
    novo->item = item;
    novo->prox = NULL;
    
    /*fila vazia */
    if (f->prim == NULL)
    {
        f->prim = novo;
        f->ult = novo;
        f->num++;
        return 1;
    }
    
    /*insere no final*/ 
    f->ult->prox = novo;
    f->ult = novo;
   	f->num++;
   	
   	return 1;
}

int fila_retira (struct fila_t *f, int *item) {
	if (!f || !f->prim)
		return 0;
		
	struct fila_nodo_t *aux;
	
	/* guarda o valor*/
	*item = f->prim->item;
	
	/* remove o primeiro nodo*/
	aux = f->prim;
	f->prim = f->prim->prox;
	free(aux);
	f->num--;
	
	return 1;
}

int fila_tamanho (struct fila_t *f) {
	if (!f)
		return -1;
	
	return f->num;
}

void fila_imprime (struct fila_t *f) {
	if (!f)
		return;

	struct fila_nodo_t *aux;
	
	/*fila de tamanho 0*/
	if (!f->prim)
		return;

	aux = f->prim;
	
	/*fila de tamanho 1*/
	if (!aux->prox)
	{
		printf("%d ", aux->item);
		return;
	}	
	
	/*caso geral*/
	while (aux->prox->prox != NULL)
	{
		printf("%d ", aux->item);
		
		aux = aux->prox;
	}
	
	printf("%d ", aux->item);	
	printf("%d ", aux->prox->item);
	
	return;
}

