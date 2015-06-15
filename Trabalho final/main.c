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

#include "final.h"

int main(void){
	Carro *car=NULL;
	int n;
	//bool salvar = 1;
	if(inicializar()) 
		printf("%s\n", "Inicio bem sucedido");
	else 
		return 0;
	n = leituraArq(&car, "arquivos/Carros.car");
	exibir_texto_centralizado("Seja bem vindo ao simulador de tráfego");
	//salvar = simulacao();
	if (simulacao())
		CriaArq(car,n,"arquivos/Carros.car");
	fechajanela();
	return 0;
}