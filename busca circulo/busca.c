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

void leInstancias(Ponto2D *p, Circulo *c){
	printf("Digite as cordenadas (x e y) do ponto 1.\n");
	scanf("%f",&p->x);
	scanf("%f",&p->y);
	printf("Digite as cordenadas (x e y) do centro do circulo.\n");
	scanf("%f",&c->centro.x);
	scanf("%f",&c->centro.y);
	printf("Digite o raio do circulo.\n");
	scanf("%f",&c->raio);
	printf("Digite a cor(em RGB 0 a 255);\n");
	scanf("%i",&c->cor.r);
	scanf("%i",&c->cor.g);
	scanf("%i",&c->cor.b);
}

void mostraInstancias(const Ponto2D *p, const Circulo *c,int n){
	int i;
	for(i=0;i<n;i++){
		printf("Ponto%-2d = (%5.2f,%5.2f)\n",i+1,p[i].x,p[i].y);
	}
	for(i=0;i<n;i++){
		printf("Centro do circulo%-2i = \t(%5.2f,%5.2f)\tRaio = %.2f\tCor : R = %3i, G = %3i, B = %3i\n",i+1,c[i].centro.x,c[i].centro.y,c[i].raio,c[i].cor.r,c[i].cor.g,c[i].cor.b);
	}
}

void mostraPontos(const Ponto2D *p,int n){
	int i;
	for(i=0;i<n;i++){
		printf("Ponto%-2d = (%5.2f,%5.2f)\n",i+1,p[i].x,p[i].y);
	}
}

void mostraCirculos(const Circulo *c,int n){
	int i;
	for(i=0;i<n;i++){
		printf("Centro do circulo%-2i = \t(%.2f,%.2f)\tRaio = %.2f\tCor : R = %3i, G = %3i, B = %3i\n",i+1,c[i].centro.x,c[i].centro.y,c[i].raio,c[i].cor.r,c[i].cor.g,c[i].cor.b);
	}
}


double calcDistancia_const(const Ponto2D *p1, const Ponto2D *p2){
	double d=sqrt(pow(p1->x - p2->x,2)+ pow(p1->y - p2->y,2));
return d;
}

int ehInterno(const Ponto2D *p, const Circulo *c){
	double d=sqrt(pow(p->x - c->centro.x ,2)+ pow(p->y - c->centro.y,2));
	if ((c->raio) < d)
		return 0;
	else
		return 1;
}

int leArquivoInstancias(char nomearquivo[], Ponto2D **p, Circulo **c,int *num){
	int i,n,r,g,b;
	float x,y,raio;
	FILE *fp;
	fp = fopen(nomearquivo,"r");
	if (fp==NULL){
		printf("%s\n","Erro ao abrir arquivo." );
		return -1;
	}
	else{
		printf("%s\n","Arquivo aberto com sucesso." );
		fscanf(fp, "#numero de elementos\n%i\n",&n);
		*num = n;
		*c = (Circulo*) malloc(n*sizeof(Circulo));//cria vetor de n elementos do tipo Circulo
		*p = (Ponto2D*) malloc(n*sizeof(Ponto2D));//cria vetor de n elementos do tipo Ponto2D
		if (*c==NULL || *p==NULL) {
			printf("Espaço insuficiente!");
		return -1;
	}

		for(i=0;i<n;i++){
			fscanf(fp, "#Ponto\n%f %f\n",&x,&y);
			(*p+i)->x = x;
			(*p+i)->y = y;
			fscanf(fp, "#Circulo \n%f %f %f %i %i %i\n", &x, &y, &raio, &r, &g, &b);
			(*c+i)->centro.x = x;
			(*c+i)->centro.y = y;
			(*c+i)->raio = raio;
			(*c+i)->cor.r = r;
			(*c+i)->cor.g = g;
			(*c+i)->cor.b = b;
		}
		return 1;
	}
}

/* função de comparação para ponteiros de alunos */
int compara_centro(void* a, void* b) {
	Circulo* p1 = (Circulo*) a;
	Circulo* p2 = (Circulo*) b;
	if ((p1->centro.y == p2->centro.y)){
		if ((p1->centro.x > p2->centro.x))
			return 1;
		else
			return 0;
	}
	else {
		if ((p1->centro.y > p2->centro.y))
			return 1;
		else
			return 0;
	}
}

void bolha_gen (int n, void* v, int tam, int(*cmp)(void*,void*)) {
	puts("Bolha");
	int i, j;
	for (i=n-1; i>0; i--) {
		int fez_troca = 0;
		for (j=0; j<i; j++) {
			void* p1 = acessa(v,j,tam);
			void* p2 = acessa(v,j+1,tam);
			if (cmp(p1,p2)) {
				troca(p1,p2,tam);
				fez_troca = 1;
			}
		}
	if (fez_troca == 0)   /* nao houve troca */
	return;
	}
}

void troca (void* a, void* b, int tam){
	char* v1 = (char*) a;
	char* v2 = (char*) b;
	int i;
	for (i=0; i<tam; i++) {
		char temp = v1[i];
		v1[i] = v2[i];
		v2[i] = temp;
	}
}

void* acessa (void* v, int i, int tam) {
	char* t = (char*)v;
	t += tam*i;
	return (void*)t;
}

int compara(const void* p1, const void* p2) {
	Circulo *s1 = (Circulo*) p1;
	Circulo *s2 = (Circulo*) p2;
	//printf("Chegou %p, %p, %.2f, %.2f\n", s1, s2, s1->centro.x, s1->centro.y);
	printf("Chegou %p, %p, %.2f, %.2f\n", s1, s2, s2->centro.x, s2->centro.y);
	if (s2->centro.x == s1->centro.x && s2->centro.y == s1->centro.y) {
		return 0;
	}
	if (s2->centro.y >= s1->centro.y) { //conferir se condição está correta.
		return -1; 
	}
	else {
		return +1;
	}
}

void AutoCompleta(Circulo **c,int max, int n){
	int i;
	*c = (Circulo*) malloc(n*sizeof(Circulo));
	if (!c)
		printf("%s\n","Espaço insuficiente.");
	for(i=0;i<n;i++){
		(*c+i)->centro.x = rand() % max;
		(*c+i)->centro.y = rand() % max;
		(*c+i)->raio = rand() % max;
		(*c+i)->cor.r = rand() % 255;
		(*c+i)->cor.g = rand() % 255;
		(*c+i)->cor.b = rand() % 255;
	}
}
