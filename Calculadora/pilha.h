

#define MAX  50

struct pilha {
	int n;
   	float vet[MAX];
};
typedef struct pilha Pilha;


void operacao(Pilha *p,char op);
Pilha* cria (void);
void push (Pilha* p, float v);
float pop (Pilha* p);
int vazia (Pilha* p);
void libera (Pilha* p);
void printa(Pilha* p);
