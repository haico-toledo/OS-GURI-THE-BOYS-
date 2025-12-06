#ifndef ENTIDADE
#define ENTIDADE

//entidades

//descreve a entidade heroi
struct heroi {
	int id; 					// identificador numerico 
	struct cjto_t *habilidades;	// conjunto de habilidades 
	int paciencia; 				// nivel de paciencia 
	int velocidade;				// velocidade de deslocamento
	int xp; 					// qtd de missoes ja feitas
	int base; 					// id da base atual
	int vivo;					// 1 se esta vivo, 0 se esta morto
};

//descreve a entidade base
struct base {
	int id;						// identificador numerico
	int lotacao;				// maximo de herois 
	int lot_max;                // maximo de herois que esteviveram na base ao mesmo tempo
	struct cjto_t *presentes;	// conjunto de herois na base
	struct fila_t *espera;		// fila de herois esperando para entrar
	int local[2];				// localizacao cartesiana da base
	int mi_feitas;				// n de missoes cumpridas
};

//descreve a entidade missao
struct missao {
	int id; 					// identificador numerico
	struct cjto_t *habilidades;	// conjunto de habilidades necessarias
	int local[2];				// localizacao cartesiana da missao
	int feita; 					// 1 se foi cumprida, 0 se nao foi
	int tentativas;				// n de tentativas para realizar a missao
};

//funcoes para as entidades

//retorna um numero aleatorio entre min e max
int aleat (int min, int max);

//heroi

//cria um heroi com o id dado
struct heroi *H_cria (int id);

//libera a memoria alocada para o heroi
void H_destroi (struct heroi *h);

//retorna o id do heroi
int H_id (struct heroi *h);

//retorna as habilidades do heroi
struct cjto_t H_habilidades (struct heroi *h);
	
//retorna a paciencia do heroi
int H_paciencia (struct heroi *h);
	
//retorna a velocidade do heroi
int H_velocidade (struct heroi *h);
	
//retorna o xp do heroi
int H_xp (struct heroi *h);

//retorna a base atual do heroi
int H_base (struct heroi *h);

//incrementa 1 de xp
void H_incrementa_xp (struct heroi *h);

//altera a base atual do heroi
void H_muda_base (struct heroi *h, struct base *nova);


//base

//cria base com id e local indicados
struct base *B_cria (int id, int local[2]);

//libera memoria alocada para a base
void B_destroi (struct base *b);

//retorna o id da base
int B_id (struct base *b);

//retorna a lotacao da base
int B_lotacao (struct base *b);

//retorna a lot_max da base
int B_lot_max (struct base *b);

//retorna o conjunto de herois presentes
struct cjto_t B_presentes (struct base *b);

//retorna a fila de espera
struct fila_t B_espera (struct base *b);

//retorna o local cartesiano da base
int *B_local (struct base *b);

//retorna a mi_feitas da base
int B_mi_feitas (struct base *b);

//altera a lotacao
//se o controle eh 1, aumenta em 1 o numero de herois. Se eh 0, decrementa.
void B_altera_lotacao (struct base *b, int controle);

//insere heroi na base
void B_insere_heroi (struct base *b, int id);

//remove heroi da base
void B_remove_heroi (struct base *b, int id);

//insere heroi na fila de espera
void B_insere_fila (struct base *b, int id);

//remove heroi na primeira posicao da espera
void B_remove_fila (struct base *b, int id);

//retorna 1 se a base esta cheia e 0 caso contrario
int B_cheia (struct base *b);

//retorna 1 se a base esta vazia e 0 caso contrario
int B_vazia (struct base *b);

//retorna 1 se a fila de espera esta vazia e 0 caso contrario
int B_espera_vazia (struct base *b);

//retorna quantos herois estao na base
int B_qtd_herois (struct base *b);

//missao

//cria missao com id e local dados
struct missao *MI_cria (int id, int local[2]);

//libera memoria alocada para a missao
void MI_destroi (struct missao *m);

//retorna o id da missao
int MI_id (struct missao *m);

//retorna o conjunto de habilidades necessarias
struct cjto_t MI_habilidades (struct missao *m);

//retorna o local cartesiano da missao
int *MI_local (struct missao *m);










#endif
