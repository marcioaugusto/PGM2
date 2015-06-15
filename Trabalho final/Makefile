#Para escrever comentários ##
############################# Makefile ##########################
all: final

final: final.c main.c
	gcc -oSUMO final.c main.c -Wall -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lm -g -lallegro_ttf

clean:
	rm -rf *.o

mrproper: clean
	rm -rf fianl
