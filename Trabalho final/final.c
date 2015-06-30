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
void debug(){
    return;
}

#include "final.h"

int teste= 0;
int restart = 1;

int dx   = 0;
int dy   = 0;

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

int mapa[18][24]={{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
                  { 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
                  { 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                  { 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                  { 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}};


char nome_arquivo[NUM_CARS][30]={{ "arquivos/Novo.png"},{ "arquivos/Fusca.png"},{ "arquivos/Vermelho.png"},{ "arquivos/Viper.png"},{ "arquivos/Vermelho2.png"}};

//*int mapa[MAPA_A][MAPA_L];
Semaforo Semaforos[MAPA_A][MAPA_L];//matriz de Semaforos
clock_t begin, end;

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
    al_clear_to_color(al_map_rgb(200, 100, 255));

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
    for(i=0;i<NUM_CARS;i++){//cria diferentes tipos de carros
        Sprite_car[i] = al_load_bitmap(nome_arquivo[i%NUM_CARS]);
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

    al_set_target_bitmap(Sprite_rua_h);
    al_clear_to_color(al_map_rgb(50, 255, 50));
    al_draw_filled_rectangle(0,(SPRITE_A - RUA_L)/2,SPRITE_L,SPRITE_A - (SPRITE_A - RUA_L)/2 ,al_map_rgb(50, 50, 50));

    al_set_target_bitmap(Sprite_T);
    al_draw_bitmap(Sprite_cruz, 0,0,0);
    al_draw_filled_rectangle(0,0,(SPRITE_L - RUA_L)/2,SPRITE_A ,al_map_rgb(50, 255, 50));

    al_set_target_bitmap(Sprite_L);
    al_draw_bitmap(Sprite_T, 0,0,0);
    al_draw_filled_rectangle(0,SPRITE_A - (SPRITE_A - RUA_L)/2,SPRITE_L,SPRITE_A ,al_map_rgb(50, 255, 50));

    // Alocamos o background 
    background = al_create_bitmap(LARGURA_TELA,ALTURA_TELA);
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
    //*gera uma mapa aleatório
    /*for(i=0;i<MAPA_A;i++){
        for(j=0;j<MAPA_L;j++){
            if (i%2 && (j == 0 || j == MAPA_L-1))
                mapa[i][j] = 0;//rand() % 2 || rand() % 2;
            else
                mapa[i][j] = 1;
        }
    }*/
    
    // Colorimos o bitmap os botoes
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

/*Desaloca os recursos utilizados na aplicação*/
void fechajanela(){
    int i;
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(Sprite_T);
    al_destroy_bitmap(Sprite_L);
    al_destroy_bitmap(Sprite_rua_h);
    al_destroy_bitmap(Sprite_rua_v);
    al_destroy_bitmap(Sprite_cruz);
    al_destroy_bitmap(background);
    for(i = 0;i<NUM_CARS;i++)
        al_destroy_bitmap(Sprite_car[i]);






	printf("Janela fechada\n");
}

void exibir_texto_centralizado(char msg[20]) {
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_text(font, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, msg);
}

void atualiza_tela(bool *pause,int mapa[MAPA_A][MAPA_L],Carro* car, int n) {
    char msg[6];
    int i;//*,j;
    al_set_target_bitmap(background);

    draw_map(background,mapa);                                         //desenha o mapa na janela
    if(!*pause)
        sprintf(msg, "%.1f", 1/((double) (end - begin) / CLOCKS_PER_SEC));   //converte o FPS para uma string
    else 
        strcpy(msg,"Pause");
    al_set_target_bitmap(al_get_backbuffer(janela));
    al_clear_to_color(al_map_rgb(50, 255, 50));                         //pinta o fundo da janela de verde
    al_draw_bitmap(background, dx, dy, 0);                              //desenha o background na janela

    /*desenha os carros*/
    for (i=0;i<n;i++){
        al_draw_scaled_rotated_bitmap(*(Sprite_car+i%NUM_CARS),al_get_bitmap_width(*(Sprite_car+i%NUM_CARS))/2,
        al_get_bitmap_height(*(Sprite_car+i%NUM_CARS))/2,car[i].loc.x+dx,
        car[i].loc.y+dy,RUA_L/250.,RUA_L/250.,car[i].ang,0);
    }

    //*desenha os semaforos*/
    /*
    for (i=0;i<MAPA_A;i++){
        for (j=0;j<MAPA_L;j++){
            if(Semaforos[i][j].on){                   //se posição (x,y) semaforo
                //printf("Semaforo [%i][%i] = %i\n",i,j,Semaforos[i][j].on);
                al_draw_rectangle(DESLOC + j*SPRITE_L + dx + (SPRITE_A - RUA_L)/2,DESLOC + (i+1./2)*SPRITE_A + dy + - RUA_L/2,DESLOC + j*SPRITE_L + dx + RUA_L/2  + SPRITE_A/2,DESLOC + i*SPRITE_A + dy + RUA_L/2 + SPRITE_A/2, al_map_rgb(255, 0, 00),0);
                //al_draw_bitmap(Sprite_rua_h, DESLOC + j*SPRITE_L,DESLOC + i*SPRITE_A, 0);
            }
        }
    }
    */
    al_draw_bitmap(botao_sair, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - BOTAO_A -DESLOC, 0);                               //desenha o botao sair
    al_draw_bitmap(botao_salvar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 2*BOTAO_A -DESLOC, 0);                             //desenha o botao salvar
    al_draw_bitmap(botao_criar, LARGURA_TELA - BOTAO_L,
        ALTURA_TELA - 3*BOTAO_A -DESLOC, 0);                             //desenha o botao criar
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0,&msg[0]);    //escreve o FPS ou pausado///* problema nessa função
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
    
    if (!strcmp(tipo,"Carro")){
        *c = (Carro*) malloc(n*sizeof(Carro));                           //cria vetor de n elementos do tipo Carro
        if (*c == NULL){
            printf("%s\n", "Espaço insuficiente");
            return 0;
        }
    }
    else{
        printf("%s\n", "Arquivo em formato não esperado\n");
        return 0;
    }
    if (*c==NULL ) {
            printf("Espaço insuficiente!");
            return 0;
    }
    
    for(i = n-1;i>=0;i--){
        fscanf(fp,"%i %i\n",&inicio,&dest);
        (*c+i)->id = i;
        if (inicio < MAPA_A*MAPA_L - 1)//para não colocar o carro fora do mapa
            (*c+i)->inicio = inicio;
        else
            (*c+i)->inicio = 0;

        if (dest<MAPA_A*MAPA_L - 1)//para não colocar o carro fora do mapa
            (*c+i)->dest = dest;
        else 
            (*c+i)->dest = 0;
        printf("(*c+%i)->loc.y = %.2f\n, (*c+%i)->loc.x = %.2f\n",i,(*c+i)->loc.y,i,(*c+i)->loc.x );
        (*c+i)->velo = 0;
        (*c+i)->path_num = inicio;
    }
    bolha_gen(n,(void*) *c,sizeof(Carro),compara_loc);                   //organiza elementos do vetor pela localizacao
    return n;
}

/*cria um arquivo com o vetor de carros*/
void CriaArq(Carro *c,int i,char nomedoarquivo[]){
    printf("Arquivo Salvo\n");
    FILE *fp;
    fp = fopen(nomedoarquivo,"w");
    fprintf(fp, "%s %i\n", "Carro",i);
    i--;
    for(;i>=0;i--){
        fprintf(fp,"%d %d\n",c[i].inicio,c[i].dest);
    }                     
}

int simulacao(Carro *car,int n){
    
    int i;
    int sair =0;
    int salvar = 0;
    bool pause = 0;
    bool criar;
    Digraph dig;
    //*Vertex w;
    dig = DIGRAPHinit(MAPA_L*MAPA_A);
    if(dig == NULL) return 0;//se a criacao do digrafo falhou
    converte_mapa(mapa,dig);
    //*dig = DIGRAPHrand1(MAPA_A*MAPA_L,MAPA_L*MAPA_A*MAPA_L);
    for(i=0;i<n;i++){
        if(definetrajeto(dig,car+i)){//*
           /* //for (w = (car+i)->inicio; w != (car+i)->dest; w = (car+i)->path[w])
                printf( "%d-", w);
                printf( ">%d\n", car[i].dest);
        */}
        else
            printf("%i não tem caminho para %i\n",car[i].inicio,car[i].dest);
    }
    //*DIGRAPHshow( dig);
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
                    dx-= 10;
                    printf("%s\n", "KEY");
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT){  //se apertado botao esquerda
                    dx+=10;
                    printf("%s\n", "KEY <-");
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_UP){     //se apertado botao cima
                    dy+=10;
                    printf("%s\n", "KEY");
                }
                 else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN){  //se apertado botao baixo
                    dy-=10;
                    printf("%s\n", "KEY");
                }
            }
            if (evento.type == ALLEGRO_EVENT_KEY_CHAR  || evento.keyboard.repeat) {
                printf("%c\n", evento.keyboard.unichar);
                if (evento.keyboard.repeat)
                    printf("%s\n", "Repetido");
                switch(evento.keyboard.unichar){                         //tratamento para as letras
                    case 't':
                    case 'T':
                       teste = !teste;
                        printf("Teste = %i\n", teste);
                        break;
                    case 'p':
                    case 'P':
                        pause = !pause;
                        break;
                    case 'r':
                    case 'R':
                        restart = 1;
                        break;
                    case 'c':
                    case 'C':
                        criar =1;
                        break;
                    case 'd':
                    case 'D':
                        
                        break;
                    case 'a':
                    case 'A':
                        
                    case 'w':
                    case 'W':
                        
                        break;
                    case 's':
                    case 'S':
                        
                        break;
                    default:
                        break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){            //se evento foi um click
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
        if (!pause)
            mov_car(car,n);   
        while(((double) (end - begin) / CLOCKS_PER_SEC)<(1./FPS) && !pause){    //define FPS maxima   
            end = clock();  
        }
        atualiza_tela(&pause,mapa,car,n);                                       //atualiza a tela
    }
    free(car);
    free(*(dig->adj));
    free(dig);
    return salvar;
}

/*Gera um Pop-up*/
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

/*Desenha o mapa*/
void draw_map(ALLEGRO_BITMAP *bmp,int mapa[MAPA_A][MAPA_L]){
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

/*organiza o vetor*/
void bolha_gen (int n, void* v, int tam, int(*cmp)(const void*,const void*)) {
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

/*compara a localização de dois carros*/
int compara_loc(const void* p1, const void* p2) {
    Carro *s1 = (Carro*) p1;                               //converte ponteiro para tipo carro
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

/*troca duas posicoes de memoria*/
void troca (void* a, void* b, int tam){
    char* v1 = (char*) a;
    char* v2 = (char*) b;
    int i;
    for (i=0; i<tam; i++) {                                                     //loop para troca dependendo do tamanho
        char temp = v1[i];
        v1[i] = v2[i];
        v2[i] = temp;
    }
}
/*converte uma matriz de mapa para uma matriz de adjacencia  e gera a matriz de semaforos*/
void converte_mapa(int mapa[MAPA_A][MAPA_L],Digraph dig){ 
    int x,y,id,n;
    printf("\n");
    for(x=0;x<MAPA_A;x++){
        for(y=0;y<MAPA_L;y++){
            if (mapa[x][y]){
                n = 0;                                      //n conta o numero de ruas para avaliar a necessidade de semaforo
                id = ((y)+(x)*MAPA_L)+1;                    //cria o id da posição, começa em 1
                if(id%MAPA_L){         //se não estiver na borda direita e for ímpar
                    dig->adj[id-1][id] = 1;                 //N tem caminho para N+1
                    n ++;
                }
                if((id-1)%MAPA_L){                          //se não estiver na borda esquerda e for par
                    dig->adj[id-1][id-2] = 1;               //N tem caminho para N1
                    n ++;
                }
                if(id>MAPA_L && id%2){                              //senão estiver na primeira linha
                    dig->adj[id-1][id-1-MAPA_L] = 1;        //N tem caminho para linha de cima
                    n ++;
                }
                if(id<=(MAPA_A-1)*MAPA_L){                  //se não estiver na ultima linha
                    dig->adj[id-1][id-1+MAPA_L] = 1;        //N tem caminho para linha de baixo
                    n ++;
                }
                if(n >=3)
                    Semaforos[x][y].on =1;
                else
                    Semaforos[x][y].on =0;
            }
        }
    }
    for(x=0;x<MAPA_A;x++){                              //zera as barreiras(0 na matriz do mapa)
        for(y=0;y<MAPA_L;y++){
            id = ((y)+(x)*MAPA_L)+1;                    //atualiza o id
            if(!mapa[x][y]){                            //se mapa for 0 entao cria a barreira na matriaz de adjacencia
                printf("zera %i\n", id);                //informa linha/coluna zerada
                for(n=0;n<MAPA_L*MAPA_A;n++){
                    dig->adj[id-1][n] = 0;                 //zera linha
                    dig->adj[n][id-1] = 0;                 //zera coluna
                }
            }
        }
    }
}

/*Imprime a matriz de adjacencia do digrafo*/
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
    if (G == NULL){
        printf("%s\n", "Espaço insuficiente");
        return NULL;
    }
    G->V = V; 
    G->A = 0;
    G->adj = MATRIXint( V, V, 0);
    if (G->adj == NULL)
        return NULL;
    return G;
}

int **MATRIXint( int r, int c, int val){ 
    Vertex i, j;
    int **m = malloc( r * sizeof (int *));
    if (*m == NULL){
        printf("%s\n", "Espaço insuficiente");
        return NULL;
    }
    for (i = 0; i < r; i++){
        m[i] = malloc( c * sizeof (int));
        if (m[i] == NULL){
            printf("%s\n", "Espaço insuficiente");
            return NULL;
        }
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j] = val;
    return m;
}

/*Gera um digrafo aleatório*/
Digraph DIGRAPHrand1( int V, int A){ 
    Vertex v, w;
    Digraph G = DIGRAPHinit( V);
    if (G == NULL) return NULL;
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

/*Insere um arco ao digrafo*/
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w){ 
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1; 
        G->A++;
    }
}

/*Define o tajeto a ser tracado pelo carro*/
int definetrajeto( Digraph G, Carro *car){
    Vertex v;
    int lbl[MAPA_L*MAPA_A+1];
    //*printf("G->V = %i\n", G->V);
    for (v = 0; v < G->V; v++)
        lbl[v] = 0;
    pathR( G, car->dest,car->path,lbl);
    if (lbl[car->inicio] == 0) return 0;
    else return 1;
}

void pathR( Digraph G, Vertex v,int *parent,int *lbl){
    Vertex w;
    lbl[v] = 1;
    for (w = 0; w < G->V; w++){
        if (G->adj[v][w] == 1 && lbl[w] == 0) {
            parent[w] = v;
            pathR( G, w,parent,lbl);
        }
    }
}

/*faz a movimentação dos carros*/
void mov_car(Carro *car,int n){
    int i;
    float posx,posy;
    int  pathx,pathy;
    for (i=0;i<n;i++){
        posx =  ((car[i].loc.x - DESLOC)/SPRITE_L)-1./2;
        posy =  ((car[i].loc.y -DESLOC)/SPRITE_A) - 1./2;
        pathy = car[i].path[car[i].path_num]/MAPA_L;
        pathx = car[i].path[car[i].path_num]%MAPA_L;
        //printf("posx = %.1f, posy = %.1f\n",posx,posy );
        if (((int)posx + (int)posy*MAPA_L) == car[i].dest){//se chegou no destino
            //printf("%i == %i",(int)(posx + posy*MAPA_L),car[i].dest );
            printf("Carro %i Chegou ao destino->%i\n",i,car[i].dest);
            car[i].ang = 3*M_PI/2;
            car[i].velo = 0;
            car[i].loc.y = MAPA_A*SPRITE_A+50;
            car[i].loc.x = 100+30*i;
        } else
        if (posx ==  pathx && posy == pathy){//esta na esquina certa
            car[i].path_num = car[i].path[car[i].path_num];
            //printf("%s[%i]\n", "prox ->",car[i].path[(car[i].path_num)]);
            car[i].velo = 0;
        }
        if (posy == pathy){
            if(pathx == posx+1){//leste
                car[i].ang = 0;
                car[i].velo = 1;//rand()%2+1;
                //*printf("%s->%i\n", "Leste",car[i].path[car[i].path_num]);
            }else if(pathx == posx-1){//oeste
                //*printf("%s->%i\n", "Oeste",car[i].path[car[i].path_num]);
                car[i].ang =  M_PI;
                car[i].velo = 1;//rand()%2+1;
            }
        }else
        if (posx == pathx){
            debug();
            if(pathy == posy-1){//norte
                //*printf("%s->%i\n", "Norte",car[i].path[car[i].path_num]);
                car[i].ang =  3*M_PI/2;
                car[i].velo = 1;//rand()%2+1;
            }else if(pathy == posy+1){//sul
                //*printf("%s->%i\n", "Sul",car[i].path[car[i].path_num]);
                car[i].ang =  M_PI/2;
                car[i].velo = 1;//rand()%2+1;
            }
        }
        car[i].loc.x += car[i].velo*cos(car[i].ang);
        car[i].loc.y += car[i].velo*sin(car[i].ang);

    }
    if (restart == 1){
        for (i=0;i<n;i++){
            car[i].loc.x = (car[i].inicio%MAPA_L)*SPRITE_L + SPRITE_L/2 + DESLOC;
            car[i].loc.y = (car[i].inicio/MAPA_L)*SPRITE_A + SPRITE_A/2 + DESLOC;
            car[i].velo  = 0;
            car[i].ang   = 0;
            restart      = 0;
            car[i].path_num = car[i].inicio;
        }
        //*return;
    }
}

int ta_perto(Carro *car,int n,int c,int d){//se os pontos estiverem proximos em x retorna 1, se em y retorna 2, se não retorna 0
    int i;
    for(i=0;i<n;i++){
        if((car[c].loc.y == car[i].loc.y))
            if(((car[c].loc.x - d*car[i].loc.x)<= 2*RUA_L) && (i !=c))
                return 1;
        if((car[c].loc.x == car[i].loc.x))
            if (((car[c].loc.y - d*car[i].loc.y)<= 2*RUA_L) && (i !=c))
                return 2;
    }
    return 0;
}