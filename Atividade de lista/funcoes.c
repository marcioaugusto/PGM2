#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "funcoes.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_ttf.h>

#ifdef testegeo
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *botao_sair = NULL, *botao_abre_arquivo = 0;
ALLEGRO_FONT *font;

void inserepelatela(ListaGen **lista) {

	int sair = 0;
	int na_area_central = 0;
	int q=0;
	Ponto2D ponto[3];

	printf("\nHá dois botões na tela.\n");
	printf("\nFaça tres pontos fora dos botoes.\n");
        
	while (!sair) {
        	// Verificamos se há eventos na fila
        	while (!al_is_event_queue_empty(fila_eventos)) {
            		ALLEGRO_EVENT evento;
            		al_wait_for_event(fila_eventos, &evento);
            		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) { // Se o evento foi de movimentação do mouse
                		// Verificamos se ele está sobre a região do retângulo central
                		if (evento.mouse.x >= LARGURA_TELA - 10 - al_get_bitmap_width(botao_abre_arquivo) &&
    				evento.mouse.x <= LARGURA_TELA -10 &&
                    		evento.mouse.y >= ALTURA_TELA - 10 - al_get_bitmap_height(botao_sair) - al_get_bitmap_height(botao_abre_arquivo)  && evento.mouse.y <= ALTURA_TELA-10 - al_get_bitmap_height(botao_sair)) {
                    			
					na_area_central = 1;
                		}
                		else {
                    			na_area_central = 0;
                		}
	 	        }
            		// Ou se o evento foi um clique do mouse
            		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                		if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10 &&
                    			evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    			evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10) {
                    		
					sair = 1;
		                }
				// Verificamos se ele está sobre a região do botao abre arquivo
                		else if (evento.mouse.x >= LARGURA_TELA - 10 - al_get_bitmap_width(botao_abre_arquivo) &&
    				evento.mouse.x <= LARGURA_TELA -10 &&
                    		evento.mouse.y >= ALTURA_TELA - 10 - al_get_bitmap_height(botao_sair) - al_get_bitmap_height(botao_abre_arquivo)  && evento.mouse.y <= ALTURA_TELA-10 - al_get_bitmap_height(botao_sair)) {
					leituraarqgen(lista,"primeira.geo");
					desenhagen(*lista,0,1);
		                }
				else{				
					al_draw_filled_circle(evento.mouse.x, evento.mouse.y,1, al_map_rgb(255, 255, 255));
					ponto[q].x = evento.mouse.x;
					ponto[q].y = evento.mouse.y;
					q ++;
					if (q==3){
					inseretriang(lista,ponto[0].x,ponto[0].y,ponto[1].x,ponto[1].y,ponto[2].x,ponto[2].y,255, 255, 255,3);
					al_draw_filled_triangle(ponto[0].x,ponto[0].y,ponto[1].x,ponto[1].y,ponto[2].x,ponto[2].y,al_map_rgb(255, 255, 255));
					al_draw_triangle(ponto[0].x,ponto[0].y,ponto[1].x,ponto[1].y,ponto[2].x,ponto[2].y,al_map_rgb(0, 0, 0),2);
					q = 0;
					}
				}
	            	}
		al_set_target_bitmap(botao_abre_arquivo);
		if (!na_area_central)
		    al_clear_to_color(al_map_rgb(255, 255, 255));
		else
		    al_clear_to_color(al_map_rgb(0, 255, 0));
		    al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_bitmap_width(botao_sair)/2, al_get_bitmap_height(botao_sair)/2 -14,ALLEGRO_ALIGN_CENTRE, "Abre");
		    al_draw_rectangle(0,0, al_get_bitmap_width(botao_abre_arquivo), al_get_bitmap_height(botao_abre_arquivo), al_map_rgb(0,0,0),10);

		// Desenhamos os retângulos na tela
		al_set_target_bitmap(al_get_backbuffer(janela));
		al_draw_bitmap(botao_abre_arquivo, LARGURA_TELA -			al_get_bitmap_width(botao_abre_arquivo) - 10,
			ALTURA_TELA - al_get_bitmap_height(botao_sair) - al_get_bitmap_height(botao_abre_arquivo) - 10, 0);
		al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10,
		               ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10, 0);
	 
		// Atualiza a tela
		al_flip_display();	        	
		}
	
	}
}

/* função de inicialização: retorna uma lista de retangulo vazia */
ListaGen *inicgeogen(void) {
	return NULL;
}

/* inserção de retangulo no início: usando ponteiro para ponteiro*/
void insereretang(ListaGen** lista,double x1,double y1,double x2, double y2,int r, int g, int b, double thickness) {
	Retangulo *novo = (Retangulo*) malloc(sizeof(Retangulo));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return;
	}
	novo->x1 = x1;
	novo->y1 = y1;
	novo->x2 = x2;
	novo->y2 = y2;
	novo->r  = r;
	novo->g  = g;
	novo->b  = b;
	novo->thickness = thickness;

	/* aloca nó */
	ListaGen *Novo = (ListaGen*) malloc(sizeof(ListaGen));
	if (Novo==NULL) {
		free(novo);
		printf("Espaço insuficiente!");
		return;
	}
	Novo->tipo = retang;
	Novo->info = novo;
	Novo->prox = *lista;
	*lista = Novo;
}

/* inserção de circulo no início: usando ponteiro para ponteiro*/
void inserecirc(ListaGen** lista, double x, double y, double raio, int r, int g, int b, double thickness) {
	Circulo *novo = (Circulo*) malloc(sizeof(Circulo));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return;
	}
	novo->x = x;
	novo->y = y;
	novo->raio = raio;
	novo->r  = r;
	novo->g  = g;
	novo->b  = b;
	novo->thickness = thickness;

	/* aloca nó */
	ListaGen *Novo = (ListaGen*) malloc(sizeof(ListaGen));
	if (Novo==NULL) {
		free(novo);
		printf("Espaço insuficiente!");
		return;
	}
	Novo->tipo = circ;
	Novo->info = novo;
	Novo->prox = *lista;
	*lista = Novo;
}

/* inserção de triangulo no início: usando ponteiro para ponteiro*/
void inseretriang(ListaGen** lista, double x1, double y1,double x2, double y2,double x3, double y3, int r, int g, int b, double thickness){
	Triangulo *novo = (Triangulo*) malloc(sizeof(Triangulo));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return;
	}
	novo->x1 = x1;
	novo->y1 = y1;
	novo->x2 = x2;
	novo->y2 = y2;
	novo->x3 = x3;
	novo->y3 = y3;
	novo->r  = r;
	novo->g  = g;
	novo->b  = b;
	novo->thickness = thickness;

	/* aloca nó */
	ListaGen *Novo = (ListaGen*) malloc(sizeof(ListaGen));
	if (Novo==NULL) {
		free(novo);
		printf("Espaço insuficiente!");
		return;
	}
	Novo->tipo = triang;
	Novo->info = novo;
	Novo->prox = *lista;
	*lista = Novo;
}

/* função auxiliar: calcula área correspondente ao nó */
void calcareagen(ListaGen *p){  
	switch (p->tipo) {
		case retang: {        /* converte para retângulo e calcula área */
			Retangulo *r = (Retangulo*) p->info;
			printf("Retangulo de area = %.2f\n",(r->x2 - r->x1) * (r->y2 - r->y1));     
		}
		break;
		case triang: {        /* converte para triângulo e calcula área */      	
			Triangulo *t = (Triangulo*) p->info;
			double a,b,c,s;
			a = sqrt(pow(t->x1-t->x2,2)+pow(t->y1-t->y2,2));
			b = sqrt(pow(t->x2-t->x3,2)+pow(t->y2-t->y3,2));
			c = sqrt(pow(t->x3-t->x1,2)+pow(t->y3-t->y1,2));
			s = (a + b + c) / 2;
			printf("Triangulo de área errada = %.2f\n",sqrt(s*(s-a)*(s-b)*(s-c)));
		}
		break;
		case circ: {        /* converte para círculo e calcula área */        		
			Circulo *c = (Circulo*) p->info;
		        printf("Circulo de area = %.2f\n",2 * PI * 							c->raio * c->raio);
		}
	        break;
	}
}

/* função auxiliar: calcula área correspondente ao nó */
void desenhagen(ListaGen *p, double tempo, bool i){
	if (p!=NULL) {
		switch (p->tipo) {
			case retang: {       
				Retangulo *r = (Retangulo*) p->info;
				if (i)
					al_draw_filled_rectangle(r->x1,r->y1, r->x2, r->y2, al_map_rgb(r->r, r->g, r->b));
				else
					al_draw_rectangle(r->x1,r->y1, r->x2, r->y2, al_map_rgb(r->r, r->g, r->b),r->thickness);   
			}
			break;
			case triang: {        /* converte para triângulo e calcula área */
				Triangulo *t = (Triangulo*) p->info;
				if (i)
					al_draw_filled_triangle(t->x1,t->y1,t->x2,t->y2, t->x3,t->y3, al_map_rgb(t->r, t->g, t->b));
				else
					al_draw_triangle(t->x1,t->y1,t->x2,t->y2, t->x3,t->y3,	al_map_rgb(t->r, t->g, t->b),t->thickness);   
			}
			break;
			case circ: {
				Circulo *c = (Circulo*) p->info;
				if (i)
					al_draw_filled_circle(c->x, c->y, c->raio, al_map_rgb(c->r, c->g, c->b));
			else
					al_draw_circle(c->x, c->y, c->raio, al_map_rgb(c->r, c->g, c->b),c->thickness);
			}
			break;
		}
		al_flip_display();
		al_rest(tempo);
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		desenhagen(p->prox,tempo,i);
	}
}

void fechajanela() {
    /*Desaloca os recursos utilizados na aplicação*/
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(botao_abre_arquivo);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
	printf("Janela fechada\n");
	system("sleep 2");
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
 
    al_init_font_addon();//habilita o uso de fontes

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    font = al_load_font("DejaVuSans.ttf", 20, 0);
    if (!font)
    {
        fprintf(stderr, "Falha ao carregar a fonte.\n");
        return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    al_set_window_title(janela, "Marcio Augusto");
    al_clear_to_color(al_map_rgb(0, 150, 0));

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

	// Alocamos o botão para fechar a aplicação
    	botao_sair = al_create_bitmap(100, 50);
    	if (!botao_sair) {
        	fprintf(stderr, "Falha ao criar botão de saída.\n");
        	al_destroy_bitmap(botao_abre_arquivo);
        	al_destroy_display(janela);
        	return -1;
    	}

	// Colorimos o bitmap do botão de sair
        al_set_target_bitmap(botao_sair);
        al_clear_to_color(al_map_rgb(255, 0, 0));
	al_draw_rectangle(0,0, al_get_bitmap_width(botao_sair), al_get_bitmap_height(botao_sair), al_map_rgb(0,0,0),10);   

	//escrevemos no bitmap do botao sair
	//al_set_target_bitmap(botao_sair);
	al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_bitmap_width(botao_sair)/2, al_get_bitmap_height(botao_sair)/2 - 14,ALLEGRO_ALIGN_CENTRE, "sair");

	// Alocamos o retângulo botao de abrir arquivo
    	botao_abre_arquivo = al_create_bitmap(100 , 50);
    	if (!botao_abre_arquivo) {
        	fprintf(stderr, "Falha ao criar bitmap.\n");
        	al_destroy_display(janela);
        	return -1;
    	}

	// Colorimos o bitmap do botão central
        al_set_target_bitmap(botao_abre_arquivo);
        al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_rectangle(0,0, al_get_bitmap_width(botao_abre_arquivo), al_get_bitmap_height(botao_abre_arquivo), al_map_rgb(0,0,0),10);  
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
 

    return true;
}

void leituraarqgen(ListaGen **lista, char nomedoarquivo[]) {
	char tipo[10];
	int r,g,b;
	double i,j,k,l,m,n,thickness;
	FILE *fp;
	fp = fopen(nomedoarquivo,"r");
	if (fp==NULL)
		printf("Arquivo não localizado.\n");
	else {
		printf("Arquivo aberto com sucesso.\n");
		while(1) {
			fscanf(fp," %s", tipo);
			if(feof(fp))
				break;
			if (!memcmp(tipo,"retangulo",2)) {
			fscanf(fp,"%lf %lf %lf %lf %i %i %i %lf\n",&i,&j,&k,&l,&r,&g,&b,&thickness);
			insereretang(lista,i,j,k,l,r,g,b,thickness); 
			}
			else if (!memcmp(tipo,"triangulo",2)) {
			fscanf(fp,"%lf %lf %lf %lf %lf %lf %i %i %i %lf\n",&i,&j,&k,&l,&m,&n,&r,&g,&b,&thickness);
			inseretriang(lista,i,j,k,l,m,n,r,g,b,thickness);
			}
        		else if (!memcmp(tipo,"circulo",2)) {
		        fscanf(fp,"%lf %lf %lf %i %i %i %lf\n",&i,&j,&k,&r,&g,&b,&thickness);
			inserecirc(lista,i,j,k,r,g,b,thickness);
			}
		        else {
				printf("Erro ao identificar tipo\n");
				break; 
			}
		}
	}
}



#endif

#ifdef testelista
/* inserção no início: retorna a lista atualizada */
Lista* insere (Lista* l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return l;
	}
	novo->info = i;
	novo->prox = l;
	return novo;
}
/* inserção no início */
void insere2 (Lista** l, int i) {
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return;
	}
	novo->info = i;
	novo->prox = *l;
	*l = novo;
}

/* inserção ordenada: retorna a lista atualizada */
void insereord (Lista** l, int i) {
	Lista* t = *l;
	Lista* ant = NULL;
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	if (novo==NULL) {
		printf("Espaço insuficiente!");
		return;
	}
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
}

#endif