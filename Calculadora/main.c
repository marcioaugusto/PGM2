#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

int main (){
	Pilha *pilha;
	pilha = cria();
	char temp;
	float num;
	
	
	while(1) {
		printa(pilha);
		__fpurge(stdin);
	    	scanf("%c",&temp);
		if (temp==81|temp==113|temp==27)
			return 0;
		if (!(temp >= 48 & temp <= 57))
			operacao(pilha,temp);
		else {
			ungetc(temp, stdin);
			scanf("%f", &num);
			push(pilha, num);
		}
	}
	libera(pilha);
	return 0;
}
