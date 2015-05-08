#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* cria (void) {
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->n = 0;   					/* inicializa com zero elementos */   
	return p;
}

void push (Pilha* p, float v) {
	if (p->n == MAX) {   				/* capacidade esgotada */
	printf("Capacidade da pilha estourou.\n");
	exit(1);         				/* aborta programa */   
	}				   
	p->vet[p->n] = v;				/* insere elemento na próxima posição livre */
	p->n++;
}

float pop (Pilha* p) {
	float v;
	if (vazia(p)) {
		printf("Pilha vazia.\n");
			exit(1);			/* aborta programa */
	}
	v = p->vet[p->n-1];				/* retira elemento do topo */
	p->n--;   
	return v;
}

int vazia (Pilha* p) { 
	return (p->n == 0);
}

void libera (Pilha* p) {
	free(p);
}

void operacao(Pilha *p,char op) {
	float temp,teste;
	if (op == 79 | op == 111) {
		system("clear");
		printf("\n\n\t\tLISTA DE OPÇÕES\n\n");
		printf("\tinsira um número para ser adicionado à pilha\n");
		printf("\tdigite uma operação para executar (último(?)penúltimo)\n");
		printf("\tdigite o para ver as opções\n");
		printf("\tdigite q para fechar\n");
		scanf("%f",&temp);
	return;
	}
	if (p->n < 2 && op != 111){
		printf("\n\tNúmero insuficiente de operandos!");
	//scanf("%f",&temp);
	//system("usleep 1");
	//system("aplay -q /usr/share/skype/sounds/VoicemailReceived.wav ");
	//system("beep");
	//printf("\7");
	//system("clear");
	}
	else {
		switch (op) {
			case 43: {
				temp = pop(p) + pop(p);
			} break;
			case 45: {
				temp = pop(p) - pop(p);
			} break;
			case 42:
			case 88:
			case 120:{
				temp = pop(p) * pop(p);
			} break;
			case 47: {
				temp =  pop(p);
				teste = pop(p);
				if (!teste){
					push (p,teste);
					push (p,temp);
					printf("\tDivisão por 0 não permitida");
					return;
				}
				temp = temp / teste;
			} break;
			default: return;
		}
		push(p,temp);
	}
}

void printa(Pilha* p) {
	system("clear");
	printf("\n\n\t   Calculadora modo RPN\n\t(digite O para ver opções)\n\n");
	int i;
	for(i=0;i<p->n;i++) {
	printf("%.2f:\n",p->vet[i]);
	}
}

