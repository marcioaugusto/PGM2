#Para escrever comentários ##
############################# Makefile ##########################
all: lista

geometrias: funcoes.c main.c
	gcc -ogeometrias -Dtestegeo funcoes.c main.c -Wall -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lm -g -lallegro_ttf

lista: main.c funcoes.c
	gcc -olista -Dtestelista funcoes.c main.c -Wall -g

clean:
	rm -rf *.o

mrproper: clean
	rm -rf lista geometrias
