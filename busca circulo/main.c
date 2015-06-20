/*****************************************************
*
* Desenvolvedor: Marcio A. Augusto
*
* Engenharia Eletrônica
* Programação de Computadores II
* IFSC - Semestre 2015/1
*
******************************************************/
#include "busca.h"

#define max 200

#ifdef AVALIATEMPO
   clock_t begin, end;
   double time_spent1,time_spent2,time_spent3;
#endif



int main () {
    srand(time(NULL));//para a geração de valores aleatórios
    int n = 5000;
    Circulo *circ;
    //Ponto2D *ponto;
   // system("clear");
    Circulo *encontrado;
    //encontrado = (Circulo*) malloc(2*sizeof(Circulo));
    Circulo *c;
    c = (Circulo*) malloc(2*sizeof(Circulo));
    c->centro.x = rand() % max;
    c->centro.y = rand() % max;
    c->raio = 5;
    c->cor.r = 6;
    c->cor.g = 7;
    c->cor.b = 8;
    AutoCompleta(&circ,max,n);    

    #ifdef AVALIATEMPO
        begin = clock();
        bolha_gen(n,(void*) circ,sizeof(Circulo),compara_centro);
        end = clock();
        time_spent1 = (double) (end - begin) / CLOCKS_PER_SEC;
        mostraCirculos(circ,n);

        begin = clock();
        encontrado =buscacentro(n,c->centro.x,c->centro.y, circ);
        end = clock();
        time_spent3 = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("procurando centro = (%-3.2f,%-3.2f)\n",c->centro.x, c->centro.y);

        if(encontrado) {
        printf("%s\n", "Circulo encontrado\n");
        mostraCirculos(encontrado,1);
    }
    else 
        printf("%s\n", "Circulo não encontrado");
        
        begin = clock();
        encontrado = (Circulo*) bsearch((void*) c, (void *)circ, n, sizeof(Circulo), compara);
        end = clock();
        time_spent2 = (double) (end - begin) / CLOCKS_PER_SEC;

        if(encontrado) {
        printf("%s\n", "Circulo encontrado\n");
        mostraCirculos(encontrado,1);
    }
    else 
        printf("%s\n", "Circulo não encontrado");

        printf("Tempo gasto para organizar um vetor de %i valores usando o bolha: %f\n",n, time_spent1); //1.386117
        printf("Tempo gasto para encontrar um valor em %i usando o BSEARCH: %f\n",n, time_spent2); //0.000047
        printf("Tempo gasto para encontrar um valor em %i usando o buscacentro: %f\n",n, time_spent3); //0.0000
        printf("n=%d\n", n);
    #else
        bolha_gen(n,(void*) circ,sizeof(Circulo),compara_centro);puts("compara_centro");
        mostraCirculos(circ,n);
        encontrado = (Circulo*) bsearch((void*) c, (void *)circ, n, sizeof(Circulo), compara);
    #endif

	return 0;
}


