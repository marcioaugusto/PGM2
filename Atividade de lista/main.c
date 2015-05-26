#include "funcoes.h"

#ifdef testegeo
//	bool inicializar();
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
	//char nomedoarquivo[100];
	if (!inicializar())
        	return -1;
	printf("\n\nTestando as funcoes de geometrias\n\n");
	al_flip_display();
	ListaGen *listagen;
	listagen = inicgeogen();
	inserepelatela(&listagen);
	//printf("Digite o nome do arquivo:");
	//scanf("%s",nomedoarquivo);
	//leituraarqgen(&listagen,"primeira.geo");//nomedoarquivo);
	//imprimegeogen(listagen);
	//desenhagen(listagen,0.05,0);
	//desenhagen(listagen,0.05,1);
	fechajanela();
	//liberageo(geo);
#endif
	return 0;
}

