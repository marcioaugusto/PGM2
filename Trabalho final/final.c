/*****************************************************
*
* Desenvolvedor: Marcio Antonio Augusto
* E-mail: marcioantonioaugusto@hotmail.com
*
* Engenharia Eletrônica
* Programação de Computadores II
* IFSC - Semestre 2 15/
*
* Simulador de tráfego
*
******************************************************/

#include "final.h"

int teste=0;
int dx = 0;
int dy = 0;
int dir= 0;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *background   = NULL;
ALLEGRO_BITMAP *botao_salvar = NULL;
ALLEGRO_BITMAP *botao_sair   = NULL;
ALLEGRO_BITMAP *botao_criar  = NULL;
ALLEGRO_BITMAP *Sprite_cruz  = NULL;
ALLEGRO_BITMAP *Sprite_rua_v = NULL;
ALLEGRO_BITMAP *Sprite_rua_h = NULL;
ALLEGRO_BITMAP *Sprite_T     = NULL;
ALLEGRO_BITMAP *Sprite_L     = NULL;
ALLEGRO_BITMAP *Sprite_car   = NULL;
ALLEGRO_EVENT evento;
/*
int mapa[16][16]={{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
                  { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1},
                  { 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                  { 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1},
                  { 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
                  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
                  { 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                  { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
                  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
                  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
                  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};
*/

int mapa[MAPA_A][MAPA_L];
int mapa2[MAPA_A*MAPA_L][MAPA_A*MAPA_L];
int definetrajeto(Carro car, int mapa[MAPA_A][MAPA_L], int x, int y,int v){
    unsigned int n = 255,n1 = 255;
	//printf("definindo melhor trajeto para o carro %d\n", car.id);
    if (car.destino.x == x && car.destino.y == y)
        return 0;
    else
        if(mapa[x+1][y] && v != 4 && x < MAPA_L)//para leste
            n1=definetrajeto(car,mapa,x+1,y,2);
            if(n > n1)
                n = n1;
        if(mapa[x-1][y] && v != 2 && x > 0)//para oeste
            n1=definetrajeto(car,mapa,x-1,y,4);
            if (n > n1)
                n = n1;
        if(mapa[x][y-1] && v != 8 && y < MAPA_A)//para sul
            n1 = definetrajeto(car,mapa,x,y+1,1);
            if (n > n1)
                n = n1;
        if(mapa[x][y+1] && v != 1 && y > 0)//para norte
            n1 = definetrajeto(car,mapa,x,y-1,8);
            if (n > n1)
                n = n1;
    return n;
}

bool inicializar(){
    if (!al_init())
    {
	  fprintf(stderr, "Falha ao inicializar a biblioteca Allegro.\n");
	  return false;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar teclado.\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
	  fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
	  return false;
    }
 
    al_init_font_addon();//habilita o uso de fontes
    //al_init_image_addon();

    if (!al_init_ttf_addon())//habilita fontes ttf
    {
	  fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
	  return false;
    }
    
    if (!al_init_image_addon())//habilita o uso de imagens
    {
      fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
      return false;
    }

    font = al_load_font("arquivos/DejaVuSans.ttf", 20, 0);
    if (!font)
    {
	  fprintf(stderr, "Falha ao carregar a fonte.\n");
	  return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
	  fprintf(stderr, "Falha ao criar janela.\n");
	  return false;
    }
    al_set_window_title(janela, "Simulador de Trafego");
    al_set_target_bitmap(al_get_backbuffer(janela));
    al_clear_to_color(al_map_rgb(255, 255, 0));

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
	  fprintf(stderr, "Falha ao inicializar o mouse.\n");
	  return false;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
	  fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
	  return false;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
	  fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
	  return false;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse e do teclado
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    Sprite_rua_v = al_create_bitmap(SPRITE_L, SPRITE_A);
    if (!Sprite_rua_v) {
        fprintf(stderr, "Falha ao criar Sprite_rua.\n");
        return false;
    }
    Sprite_rua_h = al_create_bitmap(SPRITE_L, SPRITE_A);
    if (!Sprite_rua_h) {
        fprintf(stderr, "Falha ao criar Sprite_rua2.\n");
        return false;
    }
    Sprite_cruz = al_create_bitmap(SPRITE_L, SPRITE_A);
    if (!Sprite_cruz) {
        fprintf(stderr, "Falha ao criar Sprite_cruz.\n");
        return false;
    }
    Sprite_T = al_create_bitmap(SPRITE_L, SPRITE_A);
    if (!Sprite_T) {
        fprintf(stderr, "Falha ao criar Sprite_T.\n");
        return false;
    }
    Sprite_L = al_create_bitmap(SPRITE_L, SPRITE_A);
    if (!Sprite_L) {
        fprintf(stderr, "Falha ao criar Sprite_L.\n");
        return false;
    }
    Sprite_car = al_load_bitmap("arquivos/Vermelho.png");
    if (!Sprite_car) {
        fprintf(stderr, "Falha ao criar Sprite_car.\n");
        return false;
    }
    al_set_target_bitmap(Sprite_rua_v);
    al_clear_to_color(al_map_rgb(50, 255, 50));
    al_draw_filled_rectangle((SPRITE_L- RUA_L)/2,0, SPRITE_L - (SPRITE_L- RUA_L)/2, SPRITE_A, al_map_rgb(50, 50, 50));
    //al_draw_rectangle(0,0, SPRITE_L, SPRITE_A, al_map_rgb(0, 0, 00),5);


    al_set_target_bitmap(Sprite_cruz);
    al_draw_bitmap(Sprite_rua_v, 0,0, 0);
    al_draw_filled_rectangle(0,(SPRITE_A - RUA_L)/2,SPRITE_L,SPRITE_A - (SPRITE_A - RUA_L)/2 ,al_map_rgb(50, 50, 50));
    //al_draw_rectangle(0,0, SPRITE_L, SPRITE_A, al_map_rgb(0, 0, 00),5);

    al_set_target_bitmap(Sprite_rua_h);
    al_clear_to_color(al_map_rgb(50, 255, 50));
    al_draw_filled_rectangle(0,(SPRITE_A - RUA_L)/2,SPRITE_L,SPRITE_A - (SPRITE_A - RUA_L)/2 ,al_map_rgb(50, 50, 50));
    //al_draw_rectangle(0,0, SPRITE_L, SPRITE_A, al_map_rgb(0, 0, 00),5);

    al_set_target_bitmap(Sprite_T);
    al_draw_bitmap(Sprite_cruz, 0,0,0);
    al_draw_filled_rectangle(0,0,(SPRITE_L - RUA_L)/2,SPRITE_A ,al_map_rgb(50, 255, 50));
    //al_draw_rectangle(0,0, SPRITE_L, SPRITE_A, al_map_rgb(0, 0, 00),5);

    al_set_target_bitmap(Sprite_L);
    al_draw_bitmap(Sprite_T, 0,0,0);
    al_draw_filled_rectangle(0,SPRITE_A - (SPRITE_A - RUA_L)/2,SPRITE_L,SPRITE_A ,al_map_rgb(50, 255, 50));
    //al_draw_rectangle(0,0, SPRITE_L, SPRITE_A, al_map_rgb(0, 0, 00),5);

    // Alocamos o background 
    background = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
    if (!background) {
        fprintf(stderr, "Falha ao criar background.\n");
        return false;
    }

    // Alocamos o botão para fechar a aplicação
    botao_sair  = al_create_bitmap(BOTAO_L, BOTAO_A);
    botao_criar = al_create_bitmap(BOTAO_L, BOTAO_A);
    botao_salvar = al_create_bitmap(BOTAO_L, BOTAO_A);
    if (!botao_sair || !botao_criar || !botao_salvar) {
        fprintf(stderr, "Falha ao criar botoes.\n");
        return false;
    }

    cria_mapa2(background,mapa);

    // Colorimos o bitmap do botão de sair
    al_set_target_bitmap(botao_sair);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,00),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Sair");
    al_set_target_bitmap(botao_criar);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,00),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Criar");
    al_set_target_bitmap(botao_salvar);
    al_clear_to_color(al_map_rgb(0, 255, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,00),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Salvar");

    return true;
}

void fechajanela(){
    /*Desaloca os recursos utilizados na aplicação*/
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(Sprite_rua_v);
    al_destroy_bitmap(Sprite_cruz);
    al_destroy_bitmap(background);
 
	printf("Janela fechada\n");
	//system("sleep 1");
}

void exibir_texto_centralizado(char msg[20]) {
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, msg);
}

void atualiza_tela(bool *pause) {
    char msg[5];
    int i,j;
    al_set_target_bitmap(background);
    if (teste){
        srand(time(NULL));//para a geração de valores aleatórios
        teste = 0;
        *pause =1;
        for(i=0;i<MAPA_A;i++){
            for(j=0;j<MAPA_L;j++){
               mapa[i][j] = 1;//rand() % 2;
            }
        }
        cria_mapa2(background,mapa);
    }

    //al_draw_rotated_bitmap(Sprite_L, SPRITE_L/2,SPRITE_A/2,2*SPRITE_L,2*SPRITE_A ,teste*M_PI/2, 0);
     
    sprintf(msg, "%.1f", 1/((double) (end - begin) / CLOCKS_PER_SEC));
   // msg = (char[10])((double) (end - begin) / CLOCKS_PER_SEC);
    al_set_target_bitmap(al_get_backbuffer(janela));
    al_clear_to_color(al_map_rgb(50, 255, 50));
    al_draw_bitmap(background, /*dx*/0, /*dy*/0, 0);
    al_draw_scaled_rotated_bitmap(Sprite_car,al_get_bitmap_width(Sprite_car)/2,al_get_bitmap_height(Sprite_car)/2,/*335,164,*/dx+al_get_bitmap_width(Sprite_car)/2,-dy+al_get_bitmap_height(Sprite_car)/2,0.25,0.25,dir*M_PI/2,0);
    al_draw_bitmap(botao_sair, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - BOTAO_A -DESLOC, 0);
    al_draw_bitmap(botao_salvar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 2*BOTAO_A -DESLOC, 0);
    al_draw_bitmap(botao_criar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 3*BOTAO_A -DESLOC, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0 , *pause== 0?msg:"Pausado");
    //printf("FPS = %.2f\n0",1/((double) (end - begin) / CLOCKS_PER_SEC));
    al_flip_display();
}

int leituraArq(Carro **c, char nomedoarquivo[]) {
    char tipo[10];
    int i,n,x1,y1,x2,y2;
    FILE *fp;
    fp = fopen(nomedoarquivo,"r");
    if (fp==NULL){
        printf("Arquivo não localizado.\n");
        return 0;
    }
    printf("Arquivo aberto com sucesso.\n");
    fscanf(fp,"%s %i\n",tipo,&n);
    
    if (!strcmp(tipo,"Carro"))
        *c = (Carro*) malloc(n*sizeof(Carro));                              //cria vetor de n elementos do tipo Carro
    else{
        printf("%s\n", "Arquivo em formato não esperado\n");
        return 0;
    }
    if (*c==NULL ) {
            printf("Espaço insuficiente!");
            return 0;
    }
    i = n-1;
    for(;i>=0;i--){
        fscanf(fp,"%d %d %d %d\n",&x1,&y1,&x2,&y2);
        (*c+i)->id = i;
        (*c+i)->inicio.x = x1;
        (*c+i)->inicio.y = y1;
        (*c+i)->loc.x = x1;
        (*c+i)->loc.y = y1;
        (*c+i)->destino.x = x2;
        (*c+i)->destino.y = y2;
    }
    bolha_gen(n,(void*) *c,sizeof(Carro),compara_loc);puts("compara_loc");
    return n;
}

void CriaArq(Carro *c,int i,char nomedoarquivo[]){
    printf("Arquivo Salvo\n");
    FILE *fp;
    fp = fopen(nomedoarquivo,"w");
    fprintf(fp, "%s %i\n", "Carro",i);
    i--;
    for(;i>=0;i--){
        fprintf(fp,"%d %d %d %d\n",c[i].inicio.x,c[i].inicio.y,c[i].destino.x,c[i].destino.y);
    }
}

int simulacao(Carro *car,int n){
    int sair =0;
    int salvar = 0;
    bool pause = 0;
    bool criar;
    while(!sair){//loop da simulação
        begin = clock();
        while (!al_is_event_queue_empty(fila_eventos)) {
             al_wait_for_event(fila_eventos, &evento);
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN || evento.keyboard.repeat){
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        sair = 1;
                    printf("%s\n", "KEY");
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    dir = 0;
                    dx +=10;
                    printf("%s\n", "KEY");
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    dir = 2;
                    dx -=10;
                    al_set_target_bitmap(background);
                    printf("%s\n", "KEY <-");
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP){
                    dir = 3;
                    dy +=10;
                    printf("%s\n", "KEY");
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN){
                    dir = 1;
                    dy -=10;
                    printf("%s\n", "KEY");
                }
            }
            else if (evento.type == ALLEGRO_EVENT_KEY_CHAR  || evento.keyboard.repeat) {
                printf("%c\n", evento.keyboard.unichar);
                if (evento.keyboard.repeat)
                    printf("%s\n", "Repetido");
                switch(evento.keyboard.unichar){
                    case 'd':
                    case 'D':
                        teste+=1;
                        printf("Teste = %i\n", teste);
                        break;
                    case 'p':
                    case 'P':
                        pause = !pause;
                        break;
                    case 's':
                    case 'S':
                        printf("Define trajeto %i.\n",definetrajeto2(car[0], mapa, car[0].inicio.x,car[0].inicio.y,0));
                        /*printf("Salvar e sair.\n");
                        salvar = 1;
                        sair =1;*/
                        break;
                    case 'c':
                    case 'C':
                        criar =1;
                        break;
                    default:
                        break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (evento.mouse.x >= LARGURA_TELA - BOTAO_L){
                    if(evento.mouse.y <= ALTURA_TELA -DESLOC && evento.mouse.y >= ALTURA_TELA - BOTAO_A -DESLOC) //se o click foi sobre o botão sair
                        sair = 1;
                    if(evento.mouse.y <= ALTURA_TELA - BOTAO_A -DESLOC && evento.mouse.y >= ALTURA_TELA - 2*BOTAO_A -DESLOC){
                        salvar = 1;
                        sair   = 1;
                    }
                    if(evento.mouse.y <= ALTURA_TELA - 2*BOTAO_A -DESLOC && evento.mouse.y >= ALTURA_TELA - 3*BOTAO_A -DESLOC)
                       criar = 1;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                sair = 1;
        }
        if (criar){
            printf("Criar\n");
            criar = 0;
        }
        while(((double) (end - begin) / CLOCKS_PER_SEC)<(1./FPS) && !pause){//define FPS maxima   
            end = clock();  
        }
        atualiza_tela(&pause);
    }
    return salvar;
}

int PopUp(char frase[]){
    al_draw_filled_rectangle(LARGURA_TELA/4.,ALTURA_TELA/4.,LARGURA_TELA*3/4.,ALTURA_TELA*3/4.,al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, strcat(frase,"\'s\' Sim \t\'n\'Não"));
    al_flip_display();
    while(1){
        if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
            puts("teclado");
            switch(evento.keyboard.unichar){
                case 'n':
                    printf("Não.\n");
                    return 0;
                case 's':
                    printf("Sim.\n");
                    return 1;
            }
        }
    }
}

void cria_mapa(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]){
    int i,j,n=0;
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgb(50, 255, 50));
    for (i=0;i<MAPA_A;i++){
        for (j=0;j<MAPA_L;j++){
            if(mapa[i][j]){
                n = 0;
                if(j>0)
                    n += 1 * mapa[i][j-1];
                if(i>0)
                    n += 2 * mapa[i-1][j];
                if(i<MAPA_A-1)
                    n += 4 * mapa[i+1][j];
                if(j<MAPA_L-1)
                    n += 8 * mapa[i][j+1];
                switch(n){
                    case 0:
                        break;
                    case 1:
                    case 8:
                    case 9:
                        al_draw_bitmap(Sprite_rua_h, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 2:
                    case 4:
                    case 6:
                        al_draw_bitmap(Sprite_rua_v, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 15:
                        al_draw_bitmap(Sprite_cruz, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 7:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);
                        break;
                    case 11:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);
                        break;
                    case 13:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);
                        break;
                    case 14:
                        al_draw_bitmap(Sprite_T, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 3:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);
                        break;
                    case 5:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);
                        break;
                    case 10:
                        al_draw_bitmap(Sprite_L, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 12:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);
                        break;
                    default:
                        al_draw_bitmap(Sprite_rua_v, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                }
            }
        }
    }
}

void bolha_gen (int n, void* v, int tam, int(*cmp)(const void*,const void*)) {
    puts("Bolha");
    //Circulo* c;
    int i, j;
    void* p1;
    void* p2;
    for (i=n-1; i>0; i--) {
        int fez_troca = 0;
        for (j=0; j<i; j++) {
            p1 = acessa(v,j,tam);
            p2 = acessa(v,j+1,tam);
            if (cmp(p1,p2)) {
                troca(p1,p2,tam);
                fez_troca = 1;
            }
        }
        if (fez_troca == 0)   /* nao houve troca */
            return;

    }
}

int compara_loc(const void* p1, const void* p2) {
    Carro *s1 = (Carro*) p1;
    Carro *s2 = (Carro*) p2;
    //printf("Chegou (%p, %p), %.2f, %.2f\n", s1, s2, s1->pos.x, s1->pos.y);
    printf("Chegou %p, %p, %i, %i\n", s1, s2, s2->inicio.x, s2->loc.y);
    if (s2->loc.x == s1->loc.x && s2->loc.y == s1->loc.y) {
        return 0;
    }
    if (s2->loc.y == s1->loc.y){
        if (s2->loc.x >= s1->loc.x) //conferir se condição está correta.
            return -1; 
        else
            return +1;
    }
    if (s2->loc.y >= s1->loc.y) //conferir se condição está correta.
        return -1;
    else
        return +1;
}

void* acessa (void* v, int i, int tam) {
    char* t = (char*)v;
    t += tam*i;
    return (void*)t;
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

void cria_mapa2(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]){
    int i,j,n=0;
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgb(50, 255, 50));
    for (i=0;i<MAPA_A;i++){
        for (j=0;j<MAPA_L;j++){
            if(mapa[i][j]){
                n = 0;
                if(j>0)
                    if(mapa[i][j-1])
                        n += 1;
                if(i>0)
                    if(mapa[i-1][j])
                        n += 2;
                if(i<MAPA_A-1)
                    if (mapa[i+1][j])
                        n += 4;
                if(j<MAPA_L-1)
                    if (mapa[i][j+1])
                        n += 8;
                switch(n){
                    case 0:
                        break;
                    case 9:
                        mapa[i][j] = 2;
                    case 8:
                    case 1:
                        al_draw_bitmap(Sprite_rua_h, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 6:
                        mapa[i][j] = 2;
                    case 4:
                    case 2:
                        al_draw_bitmap(Sprite_rua_v, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 15:
                        mapa[i][j] = 4;
                        al_draw_bitmap(Sprite_cruz, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 7:
                        mapa[i][j] = 3;
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);
                        break;
                    case 11:
                        mapa[i][j] = 3;
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);
                        break;
                    case 13:
                        mapa[i][j] = 3;
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);
                        break;
                    case 14:
                        mapa[i][j] = 3;
                        al_draw_bitmap(Sprite_T, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 3:
                        mapa[i][j] = 2;
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);
                        break;
                    case 5:
                        mapa[i][j] = 2;
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);
                        break;
                    case 10:
                        mapa[i][j] = 3;
                        al_draw_bitmap(Sprite_L, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                    case 12:
                        mapa[i][j] = 2;
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);
                        break;
                    default:
                        al_draw_bitmap(Sprite_rua_v, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
                        break;
                }
            }
        }
    }
}

int definetrajeto2(Carro car, int mapa[MAPA_A][MAPA_L], int x, int y,int v){
    unsigned int n = 255,n1 = 255;
    mapa[x][y]--;
    //printf("definindo melhor trajeto para o carro %d\n", car.id);
    if (mapa[x][y]<1)//verifica se tem mais pra onde ir
        return 1550;//retorna numero alto
    if (car.destino.x == x && car.destino.y == y)//verifica se chegou ao destino
        return 1;
    else
        mapa[x][y]--;
        if(mapa[x+1][y] && v != 4 && x < MAPA_L)//se nao veio do leste e leste tem caminho
            n1=definetrajeto2(car,mapa,x+1,y,2);//verifica caminho para leste
            if(n > n1)
                n = n1;
        if(mapa[x-1][y] && v != 2 && x > 0)//para oeste
            n1=definetrajeto2(car,mapa,x-1,y,4);
            if (n > n1)
                n = n1;
        if(mapa[x][y-1] && v != 8 && y < MAPA_A)//para sul
            n1 = definetrajeto2(car,mapa,x,y+1,1);
            if (n > n1)
                n = n1;
        if(mapa[x][y+1] && v != 1 && y > 0)//para norte
            n1 = definetrajeto2(car,mapa,x,y-1,8);
            if (n > n1)
                n = n1;
    return n;
}

void converte_matriz(){
    int x,y,id,n;
    printf("\n");
    for(x=0;x<MAPA_A;x++){//printa a matriz
        for(y=0;y<MAPA_L;y++)
            printf("%i ", mapa[x][y]);
        printf("\n");
    }
    for(x=0;x<MAPA_A;x++){
        for(y=0;y<MAPA_L;y++){
            id = ((y)+(x)*MAPA_L)+1;
            if(id%MAPA_L){//se não estiver na borda direita
                //printf("não esta na borda direita id =%i\n",id );
                mapa2[id-1][id] = 1;}//5 tem caminho para 6
            if((id-1)%MAPA_L){//se não estiver na borda esquerda
                //printf("não esta na borda esquerda id =%i\n",id );
                mapa2[id-1][id-2] = 1;}//5 tem caminho para 4
            if(id>MAPA_L){//senão estiver na primeira linha
                //printf("não esta na primeira linha id =%i\n",id );
                mapa2[id-1][id-1-MAPA_L] = 1;}//5 tem caminho para 2
            if(id<=(MAPA_A-1)*MAPA_L){//se não estiver na ultima linha
                //printf("não esta na ultima linha id =%i\n",id );
                mapa2[id-1][id-1+MAPA_L] = 1;}//5 tem caminho para 8
        }
    }
    for(x=0;x<MAPA_A;x++){//zera as barreiras
        for(y=0;y<MAPA_L;y++){
            id = ((y)+(x)*MAPA_L)+1;//atualiza o id
            if(!mapa[x][y]){//se mapa for 0 entao cria a barreira no mapa2
                printf("zera %i\n", id);
                for(n=0;n<MAPA_L*MAPA_A;n++){
                    mapa2[id-1][n] = 0;//zera linha
                    mapa2[n][id-1] = 0;//zera coluna
                    //printf("n = %i (MAPA_L*MAPA_A)-1 = %i\n",n,((MAPA_L*MAPA_A)-1));   
                }
            }
        }
    }
    printf("\n");printf("\n");
    printf("%s\n", "   |1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|14|15|16|17|18|19|20|");
    for(x=0;x<MAPA_L*MAPA_A;x++){
            printf("%2i|", x+1);
        for(y=0;y<MAPA_A*MAPA_L;y++)
            printf("|%i ", mapa2[x][y]);
        printf("|\n");
    }
}
//USAR RECURSIVIDADE
/*
#define maxV 1000
static int lbl[maxV];
static Ponto2D parent[maxV];

 //A função DIGRAPHpath devolve 1 se existe caminho de s a t em G e devolve 0 em caso contrário. Também armazena no vetor parent uma representação de caminhos com origem s.  (Código inspirado no programa 18.3 de Sedgewick.)
int DIGRAPHpath( Digraph G, Ponto2D s, Ponto2D t) 
{ 
   Ponto2D v;
   for (v = 0; v < G->V; v++) 
      lbl[v] = 0;
   pathR( G, s);
   if (lbl[t] == 0) return 0;
   else return 1;
}
// A função pathR visita todos os vértices que podem ser atingidos a partir de v sem passar por vértices cujo rótulo lbl é 0.

void pathR( Digraph G, Ponto2D v) 
{ 
   Ponto2D w;
   lbl[v] = 1;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] == 1 && lbl[w] == 0) {
         parent[w] = v;
         pathR( G, w);
      }
}

//
Digraph DIGRAPHinit( int V) { 
   Digraph G = malloc( sizeof (struct digraph));
   G->V = V;
   G->A = 0;
   G->maxA = V;+
   G->arcs = malloc( V * sizeof (Arc));
   return G;
}

//REPRESENTAÇÃO POR VETOR DE ARCOS: Um objeto do tipo Arc representa um arco com ponta inicial v e ponta final w.
typedef struct { 
   Ponto2D v, w; 
} Arc;

// A função ARC devolve um arco com ponta inicial v e ponta final w.
Arc ARC( Ponto2D v, Ponto2D w) {
   Arc a;
   a.v = v, a.w = w;
   return a;
}

//REPRESENTAÇÃO POR VETOR DE ARCOS: A estrutura digraph representa um digrafo. O campo V contém o número de vértices e o campo A contém o número de arcos do digrafo. O campo arcs é um ponteiro para o vetor de arcos do digrafo. O campo maxA contém o número máximo de arcos que o vetor arcs comporta. *
struct digraph {
   int V; 
   int A; 
   Arc *arcs; 
   int maxA; 
};
// Um objeto do tipo Digraph contém o endereço de um digraph. *

typedef struct digraph *Digraph;

// REPRESENTAÇÃO POR VETOR DE ARCOS: A função DIGRAPHinit constrói um digrafo com V vértices e zero arcos. Também reserva espaço para até V arcos a serem inseridos futuramente. *


// REPRESENTAÇÃO POR VETOR DE ARCOS: A função DIGRAPHinsertA insere no digrafo G um (novo) arco com ponta inicial v e ponta final w. Se o arco já existe, a função não faz nada. Supõe-se que v e w são distintos e estão entre 0 e G->V-1. *

void DIGRAPHinsertA( Digraph G, Ponto2D v, Ponto2D w) { 
   int i;
   for (i = 0; i < G->A; ++i) {
      Arc a = G->arcs[i];
      if (a.v == v && a.w == w) return;
   }
   if (G->A == G->maxA) {
      G->maxA *= 2;
      G->arcs = realloc( G->arcs, G->maxA * sizeof (Arc));
   }
   G->arcs[G->A] = ARC( v, w);
   G->A++;
}
// REPRESENTAÇÃO POR VETOR DE ARCOS: A função DIGRAPHshow imprime, em uma linha, todos os arcos do digrafo G. *

void DIGRAPHshow( Digraph G) { 
   int i; 
   for (i = 0; i < G->A; i++) {
      Arc a = G->arcs[i];
      printf( "%d-%d ", a.v, a.w);
   }
   printf( "\n");
}
*/

/* REPRESENTAÇÃO POR VETOR DE ARCOS: A estrutura digraph representa um digrafo. O campo V contém o número de vértices e o campo A contém o número de arcos do digrafo. O campo arcs é um ponteiro para o vetor de arcos do digrafo. O campo maxA contém o número máximo de arcos que o vetor arcs comporta. *
struct digraph {
   int V; 
   int A; 
   Arc *arcs; 
   int maxA; 
};
typedef struct digraph *Digraph;
*/
