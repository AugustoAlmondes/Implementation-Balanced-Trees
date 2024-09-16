typedef struct arvore Arv;
typedef struct Posicao posicao;

struct Posicao
{
    int lugar;
    posicao *prox_plavra;
};

struct arvore
{
    char palavra_um[20], palavra_dois[20];
    posicao *psc_palavra_1, *psc_palavra_2;
    struct arvore *filho_esq;
    struct arvore *filho_crt;
    struct arvore *filho_dir;
    int num_chaves;
};
void opcoes(int *opcao);

Arv *ler_arquivo(Arv *raiz, const char *nome_arquivo);
void exibirNoRecursivo(Arv *no);
void buscar_palavra_exibir(Arv *raiz, char palavra[], int *result);
Arv *insere_no(Arv **raiz, char palavra[], Arv *pai, char sobe[], int linha);

Arv *criar_raiz(Arv *raiz);
Arv *cria_no(char palavra[], Arv *esquerda, Arv *centro, Arv *direita);
Arv *eh_folha(Arv *raiz);
Arv *adiciona_no(Arv *raiz, char palavra[], Arv *filho_dir, int linha);
void adicionar_palavra_lista(posicao **raiz, char palavra[], int linha);
Arv *quebra_no(Arv **no, char palavra[], char sobe[], Arv *filho);
void verificar_repeticao(Arv *raiz, char palavra[], int *result);
void exibir_linhas(posicao *raiz);
void buscar_para_adicionar(Arv **raiz, char palavra[], int linha);

void Redistribui(Arv **raiz, Arv **pai);
void remover23(Arv **pai, Arv **raiz, char palavra[]);
void MaiorInfoRemoveEsq(Arv **raiz, Arv **PaiMaior, Arv **MaiorInfoRemove, int LocalInfo);