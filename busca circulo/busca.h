/*****************************************************
*
* Desenvolvedor: Marcio A. Augusto
*
* Engenharia Eletrônica
* Programação de Computadores II
* IFSC - Semestre 2015/1
*
******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct ponto2D{
    float x;
    float y;
};
typedef struct ponto2D Ponto2D;

struct corRGB{
    int r,g,b;
};
typedef struct corRGB CorRGB;

struct circulo{
    Ponto2D centro;
    float raio;
    CorRGB cor;
};
typedef struct circulo Circulo;

void leInstancias(Ponto2D *p,Circulo *c);
void mostraInstancias(const Ponto2D *p,const Circulo *c,int n);
int ehInterno(const Ponto2D *p,const Circulo *c);
int leArquivoInstancias(char nomearquivo[], Ponto2D **p, Circulo **c,int *num);
int compara_centro(void* a,void* b);
void* acessa (void* v, int i, int tam);
void troca (void* a, void* b, int tam);
void bolha_gen (int n, void* v, int tam, int(*cmp)(void*,void*));
int compara(const void* p1, const void* p2);
void mostraCirculos(const Circulo *c,int n);
void mostraPontos(const Ponto2D *p,int n);
void AutoCompleta(Circulo **c,int max, int n);
Circulo * buscacentro(int n,float x, float y, Circulo* c);