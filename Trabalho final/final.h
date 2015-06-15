/*****************************************************
*
* Desenvolvedor: Marcio Antonio Augusto
* E-mail: marcioantonioaugusto@hotmail.com
*
* Engenharia Eletrônica
* Programação de Computadores II
* IFSC - Semestre 2015/1
*
* Simulador de tráfego
*
******************************************************/

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
#include <time.h>
 
#define vermelho 0
#define verde 	 1
#define FPS 60.


 clock_t begin, end;
   double time_spent1,time_spent2,time_spent3;

struct ponto2D{
    int  x;							//localizacao x de um ponto localizado na tela
    int y;							//localizacao y de um ponto localizado na tela
};
typedef struct ponto2D Ponto2D;

struct carro{
	int id;								//indentidade
	Ponto2D loc;						//localizacao atual do carro
	Ponto2D inicio;						//localizacao inicial do carro
	Ponto2D destino;					//destino do carro
	int velocidade;						//velocidade atual
	char dir[20];						//vetor que indica quais as direcoes tomar para o menor caminho
};
typedef struct carro Carro;

struct frota{
	int n;
	Carro *car;
};
typedef struct frota Frota;

struct semaforo{
	int id;								//indentidade
	bool dir,esq,ret;					//indica quais sinais estao verdes ou vermelhos
};
typedef struct semaforo Semaforo;



struct rua{
	int id;								//indentidade
	Ponto2D inicio;						//define onde inicia a rua
	Ponto2D fim;						//define onde termina a estrada
	int num;							//define numero de pistas da estrada
	bool sentido;						//define sentido da rua se ela for simples
};
typedef struct rua Rua;

struct mapa{
	int id;								//indentidade
	Ponto2D tamanho;					//define o tamnho com os pontos cima/esquerda e baixo/direita
	Rua ruas[10];
};
typedef struct mapa Mapa;

char* definetrajeto(Carro car, Mapa map);
void  abrearquivo(char[]);
bool  inicializar();
void  fechajanela();
void  exibir_texto_centralizado(char msg[20]);
int   leituraArq(Carro **c, char nomedoarquivo[]);
void  CriaArq(Carro *c,int n,char nomedoarquivo[]);
void  atualiza_tela(bool *pause);
int   simulacao();
//int   PopUp(char frase[]);