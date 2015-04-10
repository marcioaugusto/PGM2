#ifdef testegeo
struct geo* inicgeo(void);
void inseregeo(struct geo ** lista,double x1,double y1,double x2, double y2,int r, int g, int b, double thickness);
void imprimegeo(struct geo *lista);
void liberageo (struct geo* l);
double calcarea (struct geo* l);
void desenha(struct geo* l,double tempo,bool i);
bool inicializar();
void fechajanela();
#endif
#ifdef testelista
Lista* insere (Lista* l, int i);
void insere2 (Lista** l, int i);
void leituraarq(Lista **l, char nomedoarquivo[]);
Lista* inicializa (void);
void imprime (Lista* l);
void imprime2 (Lista* l);
int vazia (Lista* l);
Lista* busca (Lista* l, int v);
Lista* retira (Lista* l, int v);
void retira2 (Lista** l, int v);
void libera (Lista* l);
void insereord(Lista** l, int i);
#endif
