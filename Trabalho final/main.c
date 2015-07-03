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
	srand(time(NULL));//para a geração de valores aleatórios
	Carro *car=NULL;
	int n;
	if(inicializar()) 
		printf("%s\n", "Inicio bem sucedido");
	else {
		fechajanela();
		return 0;
	}
	n = leituraArq(&car, "arquivos/Carros.car");
	if(!n) return 0;//se a leitura do arquivo falhou
	if (simulacao(car,n))
		CriaArq(car,n,"arquivos/Carros.car");
	fechajanela();
	return 0;
}