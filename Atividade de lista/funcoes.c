#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define PI 3.141592

typedef struct lista Lista;

struct lista {
	int info;
	Lista * prox;
};

#ifdef testegeo
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

ALLEGRO_DISPLAY *janela = NULL;

struct geo{
	double x1,y1,x2,y2,thickness;
	int r,g,b;
	struct geo *prox;
};

/* função de inicialização: retorna uma lista de retangulo vazia */
struct geo* inicgeo(void) {
	return NULL;
}

/* inserção de retangulo no início: usando ponteiro para ponteiro*/
void inseregeo(struct geo ** lista,double x1,double y1,double x2, double y2,int r, int g, int b, double thickness) {
	struct geo *novo = (struct geo *) malloc(sizeof(struct geo));
	novo->x1 = x1;
	novo->y1 = y1;
	novo->x2 = x2;
	novo->y2 = y2;
	novo->r  = r;
	novo->g  = g;
	novo->b  = b;
	novo->thickness = thickness;
	novo->prox = *lista;
	*lista = novo;
}

/*funcao para liberar espaco reservado para lista de formas geometricas*/
void liberageo (struct geo* l) {
	struct geo* p = l;
	while (p != NULL) {
		struct geo* t = p->prox; /* guarda referência para o próximo elemento*/
 		free(p); /* libera a memória apontada por p */
 		p = t; /* faz p apontar para o próximo */
 	}
}

void imprimegeo(struct geo *lista) {
	if (lista->x1 < 0)
		printf("Centro(%.2f,%.2f), raio = %.2f\ncolor = (%i, %i, %i), thickness = %.2f\n\n",lista->y1,lista->x2,lista->y2,lista->r,lista->g,lista->b,lista->thickness);
	else	
	 	printf("x1 = %.2f, y1 = %.2f\nx2 = %.2f, y2 = %.2f\ncolor = (%i, %i, %i), thickness = %.2f\n\n",lista->x1,lista->y1,lista->x2,lista->y2,lista->r,lista->g,lista->b,lista->thickness);
 	if (lista->prox != NULL)
  		imprimegeo(lista->prox);
}

/*calcula a area do objeto*/
void calcarea (struct geo *l) {
	
	if (l->x1 < 0) //se for um circulo
		printf("Circulo de area = %.2f\n",2 * PI * 							l->y2 * l->y2);	//y2 é o raio
	else//se for um retangulo
		printf("Retangulo de area = %.2f\n",(l->x2 - l->x1) * 							    (l->y2 - l->y1));
	if (l->prox != NULL)
  		calcarea(l->prox);	
}

/*desenha o objeto na tela usando o allegro-5.0*/
void desenha(struct geo* l, double tempo, bool i) {
	if (l->x1 < 0)
		if (i)
			al_draw_filled_circle(l->y1, l->x2, l->y2, 				al_map_rgb(l->r, l->g, l->b));
		else
			al_draw_circle(l->y1, l->x2, l->y2, 				al_map_rgb(l->r, l->g, l->b),l->thickness);
	else
		if (i)
			al_draw_filled_rectangle(l->x1,l->y1, l->x2, l->y2, 				al_map_rgb(l->r, l->g, l->b));
		else
			al_draw_rectangle(l->x1,l->y1, l->x2, l->y2, 				al_map_rgb(l->r, l->g, l->b),l->thickness);
    	al_flip_display();
	al_rest(tempo);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (l->prox!=NULL)
		desenha(l->prox,tempo,i);
}

void fechajanela() {
	al_destroy_display(janela);
	printf("Janela fechada\n");
}

bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a biblioteca Allegro.\n");
        return false;
    }
 
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
        return false;
    }
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
 
    al_set_window_title(janela, "Testando allegro_primitives");
 
    return true;
}

#endif

#ifdef testelista
/* inserção no início: retorna a lista atualizada */
Lista* insere (Lista* l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = l;
	return novo;
}
/* inserção no início */
void insere2 (Lista** l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = *l;
	*l = novo;
}

/* inserção ordenada: retorna a lista atualizada */
void insereord (Lista** l, int i) {
	Lista* t = *l;
	Lista* ant = NULL;
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	if (*l == NULL || (*l)->info >= i) {
		novo->prox = *l;
		//return novo;
		*l = novo;
	}
	else {
		while (t != NULL && t->info < i) {
			ant = t;
			t = t->prox;
		}
		novo->prox = t;
		ant->prox  = novo;
		//return l;
	}
}

/*função de leitura de arquivo*/
void leituraarq(Lista **l, char nomedoarquivo[]) {
	FILE *fp;
	int i;
	fp = fopen(nomedoarquivo,"r");
	if (fp==NULL)
		printf("Arquivo não localizado.\n");
	else
		while(1){			
			fscanf(fp," %i", &i);
			if(feof(fp))
				break;
			insereord(l, i);
			printf("escaneou %i\n",i);
		}
} 

/* função de inicialização: retorna uma lista vazia */
Lista* inicializa (void) {
	return NULL;
}


/* função imprime: imprime valores dos elementos */
void imprime (Lista* l) {
	Lista* p; /* variável auxiliar para percorrer a lista */
	for (p = l; p != NULL; p = p->prox)
	 	printf("end = %p info = %d prox = %p\n",p, p->info, p->prox);
	printf("--------------------------------------\n");
}

/*funcao imprime de forma recursiva*/
void imprime2 (Lista* l) {
	printf("end = %p info = %d prox = %p\n",l, l->info, l->prox);
	if (l->prox != NULL)
		imprime2(l->prox);
	else
		printf("--------------------------------------\n");
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int vazia (Lista* l) {
	return (l == NULL);
}

/* função busca: busca um elemento na lista */
Lista* busca (Lista* l, int v) {
	Lista* p;
	for (p=l; p!=NULL; p=p->prox)
		if (p->info == v)
			return p;
	return NULL; /* não achou o elemento */
}

/* função retira: retira elemento da lista */
Lista* retira (Lista* l, int v) {
	Lista* ant = NULL; /* ponteiro para elemento anterior */
	Lista* p = l; /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while (p != NULL && p->info != v) {
		ant = p;
		p = p->prox;
	}
	/* verifica se achou elemento */
	if (p == NULL)
		return l; // não achou: retorna lista original
	if (ant == NULL)
		l = p->prox;// retira elemento do inicio
	else
		ant->prox = p->prox;// retira elemento do meio da lista
	free(p);
	return l;
}

/*funcao para liberar espaco reservado para lista*/
void libera (Lista* l) {
	Lista* p = l;
	while (p != NULL) {
		Lista* t = p->prox; /* guarda referência para o próximo elemento*/
 		free(p); /* libera a memória apontada por p */
 		p = t; /* faz p apontar para o próximo */
 	}
}






/*/* inserção no início: retorna a lista atualizada *
Lista* insere (Lista* l, double i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = l;
	return novo;
}
*/
/* função retira2: retira elemento da lista */
void retira2 (Lista** l, int v) {
	Lista* ant = NULL; /* ponteiro para elemento anterior */
	Lista* p = *l; /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while (p != NULL && p->info != v) {
		ant = p;
		p = p->prox;
	}
	/* verifica se achou elemento */
	if (p != NULL){// achou 
		if (ant == NULL)
			*l = p->prox;// retira elemento do inicio
		else
			ant->prox = p->prox;// retira elemento do meio da lista
	}
	free(p);
	//return l;
}

#endif










