typedef struct Posicao psc;
typedef struct no NO;

int cor(NO *H);
void trocar_cor(NO **H);
NO *rotacionaEsquerda(NO *raiz);
NO *rotacionaDireita(NO *raiz);
psc *adicionar_lista_encadeada(psc *no, char palavra_adc[], int linha);
NO *insere_no(NO *H, char palavra_adc[], int *resp, int linha);
void exibir_lista_encadeada(psc *lista);
void exibir_lista(psc *raiz);
NO *buscar_palavra(NO *raiz, char palavra_busca[], int *achou);
NO *remover_NO(NO *raiz, char palavra_excluir[]);

NO *insere_arv(NO *raiz, char palavra_adc[], int *resp, int linha);
NO *excluir_palavra(NO *raiz, char palavra_excluir[], int *achou);
NO *criar_raiz(NO *raiz);
NO *ler_arquivo(NO *raiz, const char *nome_arquivo);
void exibir_palavras(NO *raiz);
void exibir_no(NO *raiz, char palavra[], int *achou);