/*****************************************************
*
* Desenvolvedor: Marcio Antonio Augusto
* E-mail: marcioantonioaugusto@hotmail.com
*
* Engenharia Eletrônica
* Programação de Computadores II
* IFSC - Semestre 2015/
*
* Simulador de tráfego
*
******************************************************/

#include "final.h"
 
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;
const int BOTAO_A = 50;
const int BOTAO_L = 100;
const int desloc =  10;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *botao_salvar = NULL;
ALLEGRO_BITMAP *botao_sair = NULL;
ALLEGRO_BITMAP *botao_criar = NULL;

ALLEGRO_EVENT evento;

char* definetrajeto(Carro car, Mapa map){
	printf("definindo melhor trajeto para o carro %d\n", car.id);
    return NULL;
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

    if (!al_init_ttf_addon())
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
    //exibir_texto_centralizado("Seja bem vindo ao simulador de tráfego.");
    //al_flip_display();
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
	  fprintf(stderr, "Falha ao inicializar o mouse.\n");
	  al_destroy_display(janela);
	  return false;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
	  fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
	  al_destroy_display(janela);
	  return false;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
	  fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
	  al_destroy_display(janela);
	  return false;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse e do teclado
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    // Alocamos o background 
    background = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
    if (!background) {
        fprintf(stderr, "Falha ao criar background.\n");
        al_destroy_bitmap(background);
        al_destroy_display(janela);
        return false;
    }
    background = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);

    // Alocamos o botão para fechar a aplicação
    botao_sair  = al_create_bitmap(BOTAO_L, BOTAO_A);
    botao_criar = al_create_bitmap(BOTAO_L, BOTAO_A);
    botao_salvar = al_create_bitmap(BOTAO_L, BOTAO_A);
    if (!botao_sair || !botao_criar || !botao_salvar) {
        fprintf(stderr, "Falha ao criar botoes.\n");
        al_destroy_bitmap(botao_sair);
        al_destroy_bitmap(botao_criar);
        al_destroy_bitmap(botao_salvar);
        al_destroy_display(janela);
        return false;
    }
    al_set_target_bitmap(background);
    al_clear_to_color(al_map_rgb(0, 0, 255));

    // Colorimos o bitmap do botão de sair
    al_set_target_bitmap(botao_sair);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,0),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Sair");
    al_set_target_bitmap(botao_criar);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,0),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Criar");
    al_set_target_bitmap(botao_salvar);
    al_clear_to_color(al_map_rgb(0, 255, 0));
    al_draw_rectangle(0,0, BOTAO_L, BOTAO_A, al_map_rgb(0,0,0),10);
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTAO_L / 2,
                 (BOTAO_A - al_get_font_ascent(font)) / 2,
                 ALLEGRO_ALIGN_CENTRE, "Salvar");

    return true;
}

void fechajanela(){
    /*Desaloca os recursos utilizados na aplicação*/
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
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
        sprintf(msg, "%.1f", 1/((double) (end - begin) / CLOCKS_PER_SEC));
       // msg = (char[10])((double) (end - begin) / CLOCKS_PER_SEC);
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_bitmap(botao_sair, LARGURA_TELA - BOTAO_L,
            ALTURA_TELA - BOTAO_A -desloc, 0);
        al_draw_bitmap(botao_salvar, LARGURA_TELA - BOTAO_L,
            ALTURA_TELA - 2*BOTAO_A -desloc, 0);
        al_draw_bitmap(botao_criar, LARGURA_TELA - BOTAO_L,
            ALTURA_TELA - 3*BOTAO_A -desloc, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0 , *pause== 0?msg:"Pausado");
        //printf("FPS = %.2f\n",1/((double) (end - begin) / CLOCKS_PER_SEC));
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
        (*c+i)->id=    i;
        (*c+i)->inicio.x = x1;
        (*c+i)->inicio.y = y1;
        (*c+i)->destino.x = x2;
        (*c+i)->destino.y = y2;
    }
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

int simulacao(){
    int sair =0;
    int salvar = 0;
    bool pause = 0;
    bool criar;
    int mapa[4][4];
    while(!sair){//loop da simulação
        begin = clock();
        while (!al_is_event_queue_empty(fila_eventos)) {
             al_wait_for_event(fila_eventos, &evento);
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        sair = 1;
                    printf("%s\n", "KEY");
                }
            }
            else if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                //puts("char");
                printf("%c\n", evento.keyboard.unichar);
                switch(evento.keyboard.unichar){
                    case 'p':
                    case 'P':
                        //printf("Pause.\n");
                        pause = !pause;
                        break;
                    case 's':
                    case 'S':
                        printf("Salvar e sair.\n");
                        salvar = 1;
                        sair =1;
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
                    if(evento.mouse.y <= ALTURA_TELA -desloc && evento.mouse.y >= ALTURA_TELA - BOTAO_A -desloc) //se o click foi sobre o botão sair
                        sair = 1;
                    if(evento.mouse.y <= ALTURA_TELA - BOTAO_A -desloc && evento.mouse.y >= ALTURA_TELA - 2*BOTAO_A -desloc){
                        salvar = 1;
                        sair   = 1;
                    }
                    if(evento.mouse.y <= ALTURA_TELA - 2*BOTAO_A -desloc && evento.mouse.y >= ALTURA_TELA - 3*BOTAO_A -desloc)
                       criar = 1;
                }
            }
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
