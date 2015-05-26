#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#define PI 3.141592

enum tipo{circ=1,retang,triang};
typedef enum tipo Tipo;

struct ponto2D{
    double x;
    double y;
};
typedef struct ponto2D Ponto2D;
/*
struct geo{
	double x1,y1,x2,y2,thickness;
	int r,g,b;
	struct geo *prox;
};
*/
/* Define um nó genérico */
struct listagen {
	int   tipo;
	void *info;
	struct listagen *prox;
};
typedef struct listagen ListaGen;

struct lista {
	int info;
	struct lista * prox;
};
typedef struct lista Lista;

struct retang{
	double x1,y1,x2,y2,thickness;
	int r,g,b;
};
typedef struct retang Retangulo;

struct circ{
	double x,y,raio,thickness;
	int r,g,b;
};
typedef struct circ Circulo;

struct triang{
	double x1,y1,x2,y2,x3,y3,thickness;
	int r,g,b;
};
typedef struct triang Triangulo;



#ifdef testegeo
void leituraarqgen(ListaGen **lista, char nomedoarquivo[]);
void inserepelatela(ListaGen **lista);
ListaGen *inicgeogen(void);
void imprimegeogen(ListaGen *lista);
void desenhagen(ListaGen *p, double tempo, bool i);
bool inicializar();
void fechajanela();
void insereretang(ListaGen** lista,double x1,double y1,double x2, double y2,int r, int g, int b, double thickness);
void inserecirc(ListaGen** lista, double x, double y, double raio, int r, int g, int b, double thickness);
void inseretriang(ListaGen** lista, double x1, double y1,double x2, double y2,double x3, double y3, int r, int g, int b, double thickness);
void exibir_texto_centralizado2(char msg[20]);
void exibir_texto_centralizado();
void manipular_entrada(ALLEGRO_EVENT evento);

#endif

#ifdef testelista
Lista* insere (Lista* l, int i);
void insere2 (Lista** l, int i);
void leituraarq(Lista **l, char nomedoarquivo[]);
Lista* inicializa (void);
void imprime (Lista* l);
void imprime2 (Lista* l);
int vazia (Lista* l);
Lista* busca (Lista* l, int v);
Lista* retira (Lista* l, int v);
void retira2 (Lista** l, int v);
void libera (Lista* l);
void insereord(Lista** l, int i);
#endif

/*Ideia (: desenho mais matematico*/
