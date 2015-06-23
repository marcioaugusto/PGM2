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
 
#define vermelho 		0
#define verde 	 		1

/*CONFIGURAÇÕES*/
#define FPS 			60
#define MAPA_L 			5
#define MAPA_A 			4
#define SPRITE_A 		200
#define SPRITE_L 		200
#define BOTAO_A 		50
#define BOTAO_L 		100
#define LARGURA_TELA	(MAPA_L*SPRITE_L+100)
#define ALTURA_TELA 	(MAPA_A*SPRITE_A+100)
#define NUM_CARS		3

#define RUA_L   		100
#define DESLOC  		10

clock_t begin, end;

typedef int Vertex;

struct ponto2D{
    int  x;								//localizacao x de um ponto localizado na tela
    int  y;								//localizacao y de um ponto localizado na tela
};
typedef struct ponto2D Ponto2D;

struct carro{
	int id;								//indentidade
	Ponto2D loc;						//localizacao atual do carro
	Vertex inicio;						//localizacao inicial do carro
	Vertex destino;					    //destino do carro
	Ponto2D velocidade;					//velocidade atual
	int path[50];						//vetor que indica quais as direcoes tomar para o menor caminho
};
typedef struct carro Carro;

struct digraph {
   int V; 
   int A; 
   int **adj; 
};
typedef struct digraph *Digraph;
/*
struct frota{
	int n;
	Carro *car;
};
typedef struct frota Frota;

struct semaforo{
	int id;								//indentidade
	bool oeste,leste,norte,sul;			//indica quais sinais estao verdes ou vermelhos
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
*/
/*
struct mapa{
	int ligacoes[4][4];
	Ponto2D pontos[16];					//define o tamanho com os pontos cima/esquerda e baixo/direita
};
typedef struct mapa Mapa;
*/

int definetrajeto( Digraph G, Carro *car);
void  abrearquivo(char[]);
bool  inicializar();
void  fechajanela();
void  exibir_texto_centralizado(char msg[20]);
int   leituraArq(Carro **c, char nomedoarquivo[]);
void  CriaArq(Carro *c,int n,char nomedoarquivo[]);
void  atualiza_tela(bool *pause,int mapa[MAPA_A][MAPA_L],Carro* car,int n);
int   simulacao(Carro *car,int n);
void  draw_map(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]);
void  bolha_gen (int n, void* v, int tam, int(*cmp)(const void*,const void*));
int   compara_loc(const void* p1, const void* p2);
void* acessa (void* v, int i, int tam);
void  troca (void* a, void* b, int tam);
void converte_mapa(int mapa[MAPA_A][MAPA_L],int **mapa2);
void DIGRAPHshow( Digraph G);
Digraph DIGRAPHinit( int V);
int **MATRIXint( int r, int c, int val);
Digraph DIGRAPHrand1( int V, int A);
Vertex randV( Digraph G);
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w);
void pathR( Digraph G, Vertex v);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//int   PopUp(char frase[]);