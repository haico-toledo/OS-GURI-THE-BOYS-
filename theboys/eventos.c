#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "entidades.h"
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#define T_FIM_DO_MUNDO 525600
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
#define N_MISSOES      (T_FIM_DO_MUNDO / 100)
#define N_HABILIDADES  10
#define N_HEROIS       (N_HABILIDADES * 5)
#define N_BASES        (N_HEROIS / 5)


//retorna o quadrado da distancia cartesiana entre dois pontos
int dist_cart (int xi, int xii, int yi, int yii) {
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
	
	for (i = 0; i < n_bases - 1; i++)
	{
		menor = i;
		for (j = i + 1; j < n_bases; j++)
		{
			//distancia da bmp for maior que da base j
			if (dist_cart(bases[menor]->local[0], local_m[0], bases[menor]->local[1], local_m[1]) > dist_cart(bases[j]->local[0], local_m[0], bases[j]->local[1], local_m[1])) 
				menor = j;    
		}
		
		aux = bases[i];
		bases[i] = bases[menor];
		bases[menor] = aux;
	}
}


void chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
	
	h->base = b->id;
	
	int espera = 0;
	
	if (!B_cheia(b) && B_espera_vazia(b))
		espera = 1;	
	else
		if ((h->paciencia) > (10 * fila_tamanho(b->espera)))
			espera = 1;
	
	if (espera) {
		insere_espera(t, h, b, lef, TP_ESPERA );
		printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", t, h->id, b->id, B_qtd_herois(b), b->lotacao);
	}
	
	else {
		insere_desiste(t, h, b, lef, TP_DESISTE);
		printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", t, h->id, b->id, B_qtd_herois(b), b->lotacao);
	}
}


void insere_chega (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo) {
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


void espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef) {
	fila_insere (b->espera, h->id);
	
	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", t, h->id, b->id, fila_tamanho(b->espera)-1);
	insere_avisa(t, b, lef, TP_AVISA);
}


void insere_espera (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo) {
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
	
	printf("%6d: DESIST HEROI %2d BASE %d", t, h->id, b->id);
	
	insere_viaja(t, h, b, bases[nova_base], lef, TP_VIAJA);
}


void insere_desiste (int t, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo) {
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


void avisa (int t, struct base *b, struct fprio_t *lef) {
	int id_ret;
	
	//imprime avisa 1
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", t, b->id, B_qtd_herois(b), b->lotacao);
	fila_imprime(b->espera);
	printf("]\n");
		
	while(!B_cheia(b) && !B_espera_vazia(b)) {		 		 
		fila_retira(b->espera, &id_ret);		//funcao tinha retorno int e retorno por parametro *item **
		cjto_insere(b->presentes, id_ret);
		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", t, b->id, id_ret);
		
		insere_entra(t, id_ret, b, lef, TP_ENTRA);
		
		 
		//grava se for a maior lotacao historica da base
		//TROCAR POR ESPERA_MAX
		if (cjto_card(b->presentes) > b->lot_max)
		b->lot_max = cjto_card(b->presentes);
		 
	}
}


void insere_avisa (int t, struct base *b, struct fprio_t *lef, int tipo) {
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


void entra (int t, int h_id, struct base *b, struct fprio_t *lef, struct heroi **herois) {
	int tpb = 15 + herois[h_id]->paciencia * aleat(1, 20);
	
	insere_sai(t + tpb, h_id, b, lef, TP_SAI);	
	
	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", t, h_id, b->id, B_qtd_herois(b), b->lotacao, t + tpb);
}


void insere_entra (int t, int h_id, struct base *b, struct fprio_t *lef, int tipo) {
	struct E_entra *e = malloc(sizeof(struct E_entra));

	if (!e)
		return;
	//atribui os parametros ao novo evento
	e->tempo = t;
	e->h_id = h_id;
	e->b = b;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}


void sai (int t, int h_id, struct base *b, struct fprio_t *lef, struct heroi **herois, struct base **bases) {
	int nova_base;
	
	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", t, h_id, b->id, B_qtd_herois(b), b->lotacao);
	
	cjto_retira (b->presentes, h_id);	
	nova_base = aleat(0, N_BASES-1);
	insere_viaja(t, herois[h_id], b, bases[nova_base], lef, TP_VIAJA); 
	insere_avisa(t, b, lef, TP_AVISA);
}


void insere_sai (int t, int h_id, struct base *b, struct fprio_t *lef, int tipo) {
	struct E_sai *s = malloc(sizeof(struct E_sai));

	if (!s)
		return;
	//atribui os parametros ao novo evento
	s->tempo = t;
	s->h_id = h_id;
	s->b = b;
	s->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, s, tipo, t);
}


void viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef) {
	int dist, dura;
	if (h->vivo) {
		dist = dist_cart(d->local[0], d->local[1], b->local[0], b->local[1]);
		dura = dist/h->velocidade;
		cjto_retira(b->presentes, h->id);
		insere_chega(t + dura, h, d, lef, TP_CHEGA);
		printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", t, h->id, b->id, d->id, dist, h->velocidade, t+ dura);
	}
}


void insere_viaja (int t, struct heroi *h, struct base *b, struct base *d, struct fprio_t *lef, int tipo) {
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


void morre (int t, int m_id, struct heroi *h, struct base *b, struct fprio_t *lef) {	
	cjto_retira(b->presentes, h->id);
	
	printf("%6d: MORRE HEROI %2d MISSAO %d\n", t, h->id, m_id);
	
	h->vivo = 0;
	h->base = -1;
	
	insere_avisa(t, b, lef, TP_AVISA);
}


void insere_morre (int t, int m_id, struct heroi *h, struct base *b, struct fprio_t *lef, int tipo) {
	struct E_morre *m = malloc(sizeof(struct E_morre));

	if (!m)
		return;
	//atribui os parametros ao novo evento
	m->tempo = t;
	m->h = h;
	m->b = b;
	m->tipo = tipo;
	m->m_id = m_id;

	//insere o evento na lef
	fprio_insere (lef, m, tipo, t);
}


void missao (int t, int *n_v, int n_bases, struct missao *m, struct base **bases, struct heroi **herois, struct fprio_t *lef) {
	int bmp, achou = 0, i, j, maiorxp;
	struct cjto_t *aux = cjto_cria(N_HABILIDADES);
	
	m->tentativas++;
	
	printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, m->id, m->tentativas);
	cjto_imprime(m->habilidades);
	printf(" ]\n");
	
	//ordena bases por distancia
	ordena_bases(bases, m->local, n_bases);
	
	//acha bmp
	i = 0;
	while (i < N_BASES && !achou) {
		for (j=0; j < N_HEROIS; j++) 
			if (herois[j]->base == i)
				aux = cjto_uniao(aux, herois[j]->habilidades);
		if (cjto_contem(aux, m->habilidades)) {
			achou = 1;
			break;
		}
		i++;
		aux = cjto_cria(N_HABILIDADES);
	}
	
	if (achou) {
		bmp = i;
		//aumentar a xp dos herois da bmp
		for (i=0; i < N_HEROIS; i++) {
			if (herois[i]->base == bmp)
				herois[i]->xp++;
		}
		m->feita = 1;
		bases[bmp]->mi_feitas++;
		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", t, m->id, bmp);
		cjto_imprime(aux);
		printf(" ]\n");
			
		return;
	}
	
	else
		if (*n_v > 0 && t % 2500 == 0) {			
			//acha a base mais proxima com herois
			i=0;
			while (bases[i] != NULL && B_vazia(bases[i])) {
				i++;
			}
			
			//se nao houver nenhuma base com herois vivos 
			//adia a missao
			if (bases[i] == NULL) {
				insere_missao(t + 24*60, m, lef, TP_MISSAO);
				printf("%6d: MISSAO %d IMPOSSIVEL\n", t, m->id);
				return;
			}
					
					
			//acha heroi mais experiente	
			bmp = i;

			maiorxp = 0;
			for (i=0; i < N_HEROIS; i++) 
				if (cjto_pertence(bases[bmp]->presentes, i))
					if (herois[i]->xp > herois[maiorxp]->xp)
						maiorxp = herois[i]->id;	
		
			//mata o mais xp da base
			insere_morre (t, m->id, herois[maiorxp], bases[bmp], lef, TP_MORRE);
			
			//incrementa a xp dos herois presentes na bmp
			for (i=0; i < N_HEROIS; i++) {
				if (cjto_pertence(bases[bmp]->presentes, i))
					herois[i]->xp++;
			}
				
			//decrementa o numero de compostos_v
			//marca missao como feita			
			n_v--;
			m->feita = 1;
			bases[bmp]->mi_feitas++;
			
			printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [", t, m->id, bmp);
			for (i=0; i < N_HABILIDADES; i++)
				printf("%d ", i);
			printf("]\n");
		}
		
		else {
			insere_missao(t + 24*60, m, lef, TP_MISSAO);
			printf("%6d: MISSAO %d IMPOSSIVEL\n", t, m->id);
		}
}


void insere_missao (int t, struct missao *m, struct fprio_t *lef, int tipo) {
	struct E_missao *e = malloc(sizeof(struct E_missao));

	if (!e)
		return;
	//atribui os parametros ao novo evento
	e->tempo = t;
	e->m = m;
	e->tentativas = 1;
	e->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, e, tipo, t);
}


void fim (int t, int e_t, struct heroi **herois, struct base **bases, struct missao **missoes) {
	int i, m_comp = 0, max_tpm=1, mortos=0;
	float porc = 0, media = 0, t_mort = 0;
	//imrpime o fim da simulacao
	printf("%6d: FIM\n", t);

	//imprime herois
	for (i=0; i < N_HEROIS; i++) {
		if (herois[i]->vivo) {
			printf("HEROI %2d VIVO ", i);
		}
		else {
			printf("HEROI %2d MORTO ", i);
			mortos++;
		}
		
		printf("PAC %3d VEL %4d EXP %4d HABS [ ", herois[i]->paciencia, herois[i]->velocidade, herois[i]->xp);
		cjto_imprime(herois[i]->habilidades);
		printf(" ]\n");
	}
	
	//imprime as bases
	for (i=0; i < N_BASES; i++)
		printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", i, bases[i]->lotacao, bases[i]->lot_max, bases[i]->mi_feitas);
		
	
	//imprime eventos tratados
	printf("EVENTOS TRATADOS: %d\n", e_t);
	
	//n de missoes cumpridas
	//missao com mais tentativas
	//media de tentativas por missao
	for (i=0; i < N_MISSOES; i++) {
		if (missoes[i]->feita)
			m_comp++;
		if (missoes[i]->tentativas > max_tpm)
			max_tpm = missoes[i]->tentativas;
		media += missoes[i]->tentativas;
	}
	
	//media
	media = (float) media / (float) N_MISSOES; //a media ta errada, era do numero de tentativas por missao
	//porcentagem
	porc = (float) m_comp / (float) N_MISSOES;
	
	//imprime missoes cumpridas
	printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", m_comp, N_MISSOES, porc * 100);
	
	//imprime tentativas/missao
	printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", 1, max_tpm, media);
	
	//imprime taxa de mortalidade
	t_mort = (mortos/N_HEROIS) * 100;
	printf("TAXA MORTALIDADE: %.1f%%\n", t_mort);
	
}

void insere_fim (int t, struct fprio_t *lef, int tipo) {
	struct E_fim *f = malloc(sizeof(struct E_fim));

	if (!f)
		return;
	//atribui os parametros ao novo evento
	f->tempo = t;
	f->tipo = tipo;

	//insere o evento na lef
	fprio_insere (lef, f, tipo, t);
}
