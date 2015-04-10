#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct lista Lista;

#include "funcoes.h"

struct lista {
	int info;
	Lista * prox;
};

struct geo {
	double x1, y1, x2, y2, thickness;
	int r,g,b;
	struct geo *prox;
};
#ifdef testegeo
	bool inicializar();
#endif

int main (void) {
#ifdef testelista
	printf("\n\nTestando as funcoes de lista\n\n");
	fflush(stdout);
	Lista* l; /* declara uma lista não iniciada */
	l = inicializa(); /* inicia lista vazia */
	leituraarq(&l,"teste.txt");
	imprime2(l);
        insereord(&l, 20);
	insereord(&l, 16); /* insere na lista o elemento 16 */
	insereord(&l, 11); /* insere na lista o elemento 11 */
	insereord(&l, 15); /* insere na lista o elemento 15 */
	insereord(&l, 13); /* insere na lista o elemento 13 */
	imprime2(l); /* imprimirá: 11 13 15 16 20 */
	retira2(&l, 16);
	imprime(l);  /* imprimirá: 11 13 15 20*/
	retira2(&l, 13);
	imprime2(l); /* imprimirá: 11 15 20 */
	libera(l);
#endif
#ifdef testegeo
	if (!inicializar())
        	return -1;
	printf("\n\nTestando as funcoes de retangulo\n\n");
	struct geo *geo;
	geo = inicgeo();
	inseregeo(&geo, 1., 4., 315., 300., 255, 255, 255, 5.);
	imprimegeo(geo);
	inseregeo(&geo, -1, 250., 420., 200., 255, 0, 255, 10.);
	inseregeo(&geo, 15., 9., 600., 380.,0, 255, 255, 15.);
	inseregeo(&geo, -1, 320., 240., 200., 0, 255, 0, 2.);
	imprimegeo(geo);
	calcarea(geo);
	desenha(geo,0.5,0);
	desenha(geo,1,1);
	fechajanela();
	liberageo(geo);
#endif
	return 0;
}

