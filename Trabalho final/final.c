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

int teste= 0;
int dx   = 0;
int dy   = 0;
int dir[25];


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
ALLEGRO_BITMAP *Sprite_car[NUM_CARS];

//ALLEGRO_BITMAP *Sprite_car2  = NULL;
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

char nome_arquivo[3][30]={{ "arquivos/Novo.png"},{ "arquivos/Fusca.png"},{ "arquivos/Vermelho.png"}};

int mapa[MAPA_A][MAPA_L];
static int lbl[1000];
static Vertex parent[100];
int mapa2[MAPA_A*MAPA_L][MAPA_A*MAPA_L];//matriz de adjacencia

bool inicializar(){
    int i,j;
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
    for(i=0;i<NUM_CARS;i++){
        Sprite_car[i] = al_load_bitmap(nome_arquivo[i%NUM_CARS]);//nome_arquivo[i]);
        if (!Sprite_car[i]) {
            printf("Falha ao criar Sprite_car[%i].\n",i);
            return false;
        }
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
    for(i=0;i<MAPA_A;i++){
        for(j=0;j<MAPA_L;j++){
           mapa[i][j] = 1;//rand() % 2;
        }
    }

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

void atualiza_tela(bool *pause,int mapa[MAPA_A][MAPA_L],Carro* car, int n) {
    char msg[5];
    int i;
    al_set_target_bitmap(background);

        draw_map(background,mapa);                                       //desenha o mapa na janela
    sprintf(msg, "%.1f", 1/((double) (end - begin) / CLOCKS_PER_SEC));   //converte o FPS para uma string
    al_set_target_bitmap(al_get_backbuffer(janela));
    al_clear_to_color(al_map_rgb(50, 255, 50));                          //pinta o fundo da janela de verde
    al_draw_bitmap(background, /*dx*/0, /*dy*/0, 0);                     //desenha o background na janela
    

    /*desenha os carros*/
    for (i=0;i<n;i++){
        al_draw_scaled_rotated_bitmap(*(Sprite_car+i%NUM_CARS),al_get_bitmap_width(*(Sprite_car+i%NUM_CARS))/2,
        al_get_bitmap_height(*(Sprite_car+i%NUM_CARS))/2,car[i].loc.x/*+al_get_bitmap_width(*(Sprite_car+i%NUM_CARS))/2*/,
        car[i].loc.y/*+al_get_bitmap_height(*(Sprite_car+i%NUM_CARS))/2*/,0.25,0.25,dir[i]*M_PI/2,0);
    }

    al_draw_bitmap(botao_sair, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - BOTAO_A -DESLOC, 0);                               //desenha o botao sair
    al_draw_bitmap(botao_salvar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 2*BOTAO_A -DESLOC, 0);                             //desenha o botao salvar
    al_draw_bitmap(botao_criar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 3*BOTAO_A -DESLOC, 0);                             //desenha o botao criar
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0 , *pause== 0?msg:"Pausado");//escreve o FPS ou pausado
    al_flip_display();                                                   //atualiza janela
}

int leituraArq(Carro **c, char nomedoarquivo[]) {
    char tipo[10];
    int i,n,inicio,dest;
    FILE *fp;
    fp = fopen(nomedoarquivo,"r");                                       //abre arquivo para leitura
    if (fp==NULL){
        printf("Arquivo não localizado.\n");
        return 0;
    }
    printf("Arquivo aberto com sucesso.\n");
    fscanf(fp,"%s %i\n",tipo,&n);
    
    if (!strcmp(tipo,"Carro"))
        *c = (Carro*) malloc(n*sizeof(Carro));                           //cria vetor de n elementos do tipo Carro
    else{
        printf("%s\n", "Arquivo em formato não esperado\n");
        return 0;
    }
    if (*c==NULL ) {
            printf("Espaço insuficiente!");
            return 0;
    }
    
    for(i = n-1;i>=0;i--){
        fscanf(fp,"%d %d\n",&inicio,&dest);
        (*c+i)->id = i;
        (*c+i)->inicio = inicio;
        (*c+i)->destino = dest;
        (*c+i)->loc.y = ((inicio-1)/MAPA_L)*SPRITE_A + SPRITE_A/2 + DESLOC;
        (*c+i)->loc.x = ((inicio-1)%MAPA_L)*SPRITE_L + SPRITE_L/2 + DESLOC;
        (*c+i)->velocidade.x = 0;
        (*c+i)->velocidade.y = 0;
    }
    bolha_gen(n,(void*) *c,sizeof(Carro),compara_loc);                   //organiza elementos do vetor pela localizacao
    return n;
}

void CriaArq(Carro *c,int i,char nomedoarquivo[]){
    printf("Arquivo Salvo\n");
    FILE *fp;
    fp = fopen(nomedoarquivo,"w");
    fprintf(fp, "%s %i\n", "Carro",i);
    i--;
    for(;i>=0;i--){
        fprintf(fp,"%d %d\n",c[i].inicio,c[i].destino);
    }                     //cria um arquivo com os carros
}

int simulacao(Carro *car,int n){
    int i;
    int sair =0;
    int salvar = 0;
    bool pause = 0;
    bool criar;
    Digraph dig;
    Vertex w;
    dig = DIGRAPHinit(MAPA_L*MAPA_A);
    converte_mapa(mapa,dig->adj);
    for(i=0;i<n;i++){
        definetrajeto(dig,car+i);
/*
            for (w = (car+i)->destino; w != (car+i)->inicio; w = (car+i)->path[w])
               printf( "%d-", w);
            printf( "%d\n", car[i].inicio);
*/
    }
    DIGRAPHshow( dig);
    while(!sair){                                                        //loop da simulação
        begin = clock();
        while (!al_is_event_queue_empty(fila_eventos)) {                 //loop para tratamento de eventos
             al_wait_for_event(fila_eventos, &evento);                   //atualiza evento pendente
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN || evento.keyboard.repeat){
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){      //se apertado esc
                        sair = 1;
                    printf("%s\n", "KEY");
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT){  //se apertado botao direita
                    dir[teste] = 0;
                    //dx +=10;
                    car[teste].loc.x +=5;
                    printf("%s\n", "KEY");
                    printf("loc.x = %i\n", car[teste].loc.x);
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT){  //se apertado botao esquerda
                    dir[teste] = 2;
                    //dx -=10;
                    car[teste].loc.x -=5;
                    printf("%s\n", "KEY <-");
                    printf("loc.x = %i\n", car[teste].loc.x);
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP){     //se apertado botao cima
                    dir[teste] = 3;
                    //dy +=10;
                    car[teste].loc.y -=5;
                    printf("%s\n", "KEY");
                    printf("loc.y = %i\n", car[teste].loc.y);
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN){  //se apertado botao baixo
                    dir[teste] = 1;
                    //dy -=10;
                    car[teste].loc.y +=5;
                    printf("%s\n", "KEY");
                    printf("loc.y = %i\n", car[teste].loc.y);
                }
            }
            if (evento.type == ALLEGRO_EVENT_KEY_CHAR  || evento.keyboard.repeat) {
                printf("%c\n", evento.keyboard.unichar);
                if (evento.keyboard.repeat)
                    printf("%s\n", "Repetido");
                switch(evento.keyboard.unichar){                         //tratamento para as letras
                    case 't':
                    case 'T':
                        if(teste < 25)
                            teste+=1;
                        else teste = 0;
                        printf("Teste = %i\n", teste);
                        break;
                    case 'p':
                    case 'P':
                        pause = !pause;
                        break;
                    case 'q':
                    case 'Q':
                        //printf("Define trajeto %i.\n",definetrajeto(car[0], mapa, car[0].inicio.x,car[0].inicio.y,0));
                        /*printf("Salvar e sair.\n");
                        salvar = 1;
                        sair =1;*/
                        break;
                    case 'c':
                    case 'C':
                        criar =1;
                        break;
                    case 'd':
                    case 'D':
                        dir[1] = 0;
                        car[1].loc.x +=10;
                        break;
                    case 'a':
                    case 'A':
                        dir[1] = 2;
                        car[1].loc.x -=10;
                        break;
                    case 'w':
                    case 'W':
                        dir[1] = 3;
                        car[1].loc.y -=10;
                        break;
                    case 's':
                    case 'S':
                        dir[1] = 1;
                        car[1].loc.y +=10;
                        break;
                    default:
                        break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {            //se evento foi um click
                if (evento.mouse.x >= LARGURA_TELA - BOTAO_L){
                    if(evento.mouse.y <= ALTURA_TELA -DESLOC && evento.mouse.y >= ALTURA_TELA - BOTAO_A -DESLOC) //se o click foi sobre o botão sair
                        sair = 1;
                    if(evento.mouse.y <= ALTURA_TELA - BOTAO_A -DESLOC && evento.mouse.y >= ALTURA_TELA - 2*BOTAO_A -DESLOC){//se o click foi sobre o botão salvar
                        salvar = 1;
                        sair   = 1;
                    }
                    if(evento.mouse.y <= ALTURA_TELA - 2*BOTAO_A -DESLOC && evento.mouse.y >= ALTURA_TELA - 3*BOTAO_A -DESLOC)//se o click foi sobre o botão criar
                       criar = 1;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)                 //se evento foi fechar a janela
                sair = 1;
        }
        if (criar){
            printf("Criar\n");
            criar = 0;
        }
        while(((double) (end - begin) / CLOCKS_PER_SEC)<(1./FPS) && !pause){    //define FPS maxima   
            end = clock();  
        }
        atualiza_tela(&pause,mapa,car,n);                                         //atualiza a tela
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

void draw_map(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]){                    //funcao que desenha o mapa na tela
    int i,j,n=0;
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgb(50, 255, 50));                                     //pinta o fundo de verde
    for (i=0;i<MAPA_A;i++){
        for (j=0;j<MAPA_L;j++){
            if(mapa[i][j]){                                                         //se a posição (x,y) tem rua
                n = 0;
                if(j>0)                                                             //define quais ruas vizinhas
                    n += 1 * mapa[i][j-1];
                if(i>0)
                    n += 2 * mapa[i-1][j];
                if(i<MAPA_A-1)
                    n += 4 * mapa[i+1][j];
                if(j<MAPA_L-1)
                    n += 8 * mapa[i][j+1];
                switch(n){
                    case 0:
                        break;                                                                   //caso não tenha ruas vizinhas
                    case 1:
                    case 8:
                    case 9:
                        al_draw_bitmap(Sprite_rua_h, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);//desenha rua horizontal
                        break;
                    case 2:
                    case 4:
                    case 6:
                        al_draw_bitmap(Sprite_rua_v, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);//desenha rua vertical
                        break;
                    case 15:
                        al_draw_bitmap(Sprite_cruz, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);//desenha um cruzamento
                        break;
                    case 7:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2,DESLOC + j*SPRITE_L+SPRITE_L/2,
                        DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);                            //desenha uma rua em T com 180 graus
                        break;
                    case 11:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2,DESLOC + j*SPRITE_L+SPRITE_L/2,
                            DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);                        //desenha uma rua em T com 270 graus
                        break;
                    case 13:
                        al_draw_rotated_bitmap(Sprite_T,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,
                            DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);                        //desenha uma rua em T com 90 graus
                        break;
                    case 14:
                        al_draw_bitmap(Sprite_T, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);   //desenha uma rua em T
                        break;
                    case 3:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,
                            DESLOC + i*SPRITE_A+SPRITE_A/2,3*M_PI/2, 0);                        //desenha uma rua em L com 270 graus
                        break;
                    case 5:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,
                            DESLOC + i*SPRITE_A+SPRITE_A/2,2*M_PI/2, 0);                        //desenha uma rua em L com 180 graus
                        break;
                    case 10:
                        al_draw_bitmap(Sprite_L, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);   //desenha uma rua em L
                        break;
                    case 12:
                        al_draw_rotated_bitmap(Sprite_L,SPRITE_L/2,SPRITE_A/2, DESLOC + j*SPRITE_L+SPRITE_L/2,
                            DESLOC + i*SPRITE_A+SPRITE_A/2,1*M_PI/2, 0);                        //desenha uma rua em L com 90 graus
                        break;
                    default:
                        printf("%s\n", "Erro ao desenhar mapa");                                //informa se houver erro
                        break;
                }
            }
        }
    }
}

void bolha_gen (int n, void* v, int tam, int(*cmp)(const void*,const void*)) {  //organiza vetor
    int i, j;
    void* p1;
    void* p2;
    for (i=n-1; i>0; i--) {
        int fez_troca = 0;
        for (j=0; j<i; j++) {                                                                   //loop para correr o vetor
            p1 = acessa(v,j,tam);                                                               
            p2 = acessa(v,j+1,tam);
            if (cmp(p1,p2)) {                                                                   //compara
                troca(p1,p2,tam);                                                               //troca
                fez_troca = 1;                                                                  //flag para informar que houve troca
            }
        }
        if (fez_troca == 0)                                                                     //se nao houve troca
            return;

    }
}

int compara_loc(const void* p1, const void* p2) {                               //compara localizacao
    Carro *s1 = (Carro*) p1;                                                    //converte ponteiro para tipo carro
    Carro *s2 = (Carro*) p2;
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

void* acessa (void* v, int i, int tam) {                                        //acessa vetor
    char* t = (char*)v;
    t += tam*i;
    return (void*)t;
}

void troca (void* a, void* b, int tam){                                         //troca duas posicoes de memoria
    char* v1 = (char*) a;
    char* v2 = (char*) b;
    int i;
    for (i=0; i<tam; i++) {                                                     //loop para troca dependendo do tamanho
        char temp = v1[i];
        v1[i] = v2[i];
        v2[i] = temp;
    }
}

void converte_mapa(int mapa[MAPA_A][MAPA_L],int **adj){ //converte uma matriz de mapa para uma matriz de adjacencia
    int x,y,id,n;
    printf("\n");
    for(x=0;x<MAPA_A;x++){
        for(y=0;y<MAPA_L;y++){
            id = ((y)+(x)*MAPA_L)+1;
            if(id%MAPA_L){                              //se não estiver na borda direita
                adj[id-1][id] = 1;}                   //N tem caminho para N+1
            if((id-1)%MAPA_L){                          //se não estiver na borda esquerda
                adj[id-1][id-2] = 1;}                 //N tem caminho para N+1
            if(id>MAPA_L){                              //senão estiver na primeira linha
                adj[id-1][id-1-MAPA_L] = 1;}          //N tem caminho para linha de cima
            if(id<=(MAPA_A-1)*MAPA_L){                  //se não estiver na ultima linha
                adj[id-1][id-1+MAPA_L] = 1;}          //N tem caminho para linha de baixo
        }
    }
    for(x=0;x<MAPA_A;x++){                              //zera as barreiras(0 na matriz do mapa)
        for(y=0;y<MAPA_L;y++){
            id = ((y)+(x)*MAPA_L)+1;                    //atualiza o id
            if(!mapa[x][y]){                            //se mapa for 0 entao cria a barreira no mapa2
                printf("zera %i\n", id);                //informa linha/coluna zerada
                for(n=0;n<MAPA_L*MAPA_A;n++){
                    adj[id-1][n] = 0;                 //zera linha
                    adj[n][id-1] = 0;                 //zera coluna
                }
            }
        }
    }
}

void DIGRAPHshow( Digraph G) { 
    Vertex v, w; 
    for (v = 0; v < G->V; v++) {
        printf( "%2d:", v);
        for (w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1) 
                printf( " %2d", w);
        printf( "\n");
    }
}

Digraph DIGRAPHinit( int V) { 
    Digraph G = malloc( sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = MATRIXint( V, V, 0);
    return G;
}

int **MATRIXint( int r, int c, int val){ 
    Vertex i, j;
    int **m = malloc( r * sizeof (int *));
    for (i = 0; i < r; i++)
        m[i] = malloc( c * sizeof (int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j] = val;
    return m;
}

Digraph DIGRAPHrand1( int V, int A){ 
    Vertex v, w;
    Digraph G = DIGRAPHinit( V);
    while (G->A < A) {
        v = randV( G);
        w = randV( G);
        if (v != w) 
            DIGRAPHinsertA( G, v, w);
   }
   return G;
}

Vertex randV( Digraph G){ 
    double r;
    r = rand( ) / (RAND_MAX + 1.0);
    return r * G->V;
}

void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w){ 
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1; 
        G->A++;
    }
}

int definetrajeto( Digraph G, Carro *car){//s posicao inicial, t posicao final
    Vertex v;
    for (v = 0; v < G->V; v++) 
        lbl[v] = 0;
    pathR( G, car->inicio);
    if (lbl[car->destino] == 0) return 0;
    else return 1;
}

void pathR( Digraph G, Vertex v){
    Vertex w;
    lbl[v] = 1;
    for (w = 0; w < G->V; w++){
        if (G->adj[v][w] == 1 && lbl[w] == 0) {
            parent[w] = v;
            pathR( G, w);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_map2(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]){
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
