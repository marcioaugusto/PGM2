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

int main () {
    int n = 500;
    Circulo *circ;
    //Ponto2D *ponto;
   // system("clear");
    Circulo *encontrado;
    //encontrado = (Circulo*) malloc(2*sizeof(Circulo));
    Circulo *c;
    c = (Circulo*) malloc(2*sizeof(Circulo));
    c->centro.x = 171;
    c->centro.y = 61;
    c->raio = 5;
    c->cor.r = 6;
    c->cor.g = 7;
    c->cor.b = 8;
    AutoCompleta(&circ,200,n);
    //leArquivoInstancias("Arquivo.txt", &ponto, &circ,&n);
    //mostraCirculos(circ,n);
    bolha_gen(n,(void*) circ,sizeof(Circulo),compara_centro);puts("compara_centro");
    mostraCirculos(circ,n);
    printf("procurando centro = (%-3.2f,%-3.2f)\n",c->centro.x, c->centro.y);
    encontrado = (Circulo*) bsearch((void*) c, (void *)circ, n, sizeof(Circulo), compara);
    if(encontrado) {
    	printf("%s\n", "Circulo encontrado\n");
        mostraCirculos(encontrado,1);
    }
    else 
        printf("%s\n", "Circulo não encontrado");
    /*
    mostraInstancias(ponto,circ,n);
    printf("\n");
    mostraInstancias(ponto,c,1);
   
    
    mostraInstancias(ponto,circ,n);*/
	return 0;
}


