#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcao.h"
#define RED 1
#define BLACK 0

struct Posicao
{
    int lugar;
    psc *prox;
};

struct no
{
    char palavra[100];
    psc *local;
    struct no *esq;
    struct no *dir;
    int cor;
};

NO *criar_raiz(NO *raiz)
{
    return NULL;
}

// ACESSAAR A COR DE UM NÓ
int cor(NO *H)
{
    int cor;
    if (H == NULL)
    {
        cor = BLACK;
    }
    else
    {
        return H->cor;
    }
}

// TROCAR DE COR
void trocar_cor(NO **H)
{
    if (H != NULL)
    {
        (*H)->cor = !(*H)->cor;
        if ((*H)->esq != NULL)
        {
            // printf("\"%s\" troca cor\n",(*H)->palavra);
            (*H)->esq->cor = !(*H)->esq->cor;
        }
        if ((*H)->dir != NULL)
        {
            // printf("\"%s\" troca cor\n",(*H)->palavra);
            (*H)->dir->cor = !(*H)->dir->cor;
        }
    }
    // return (*H);
}
// ROTACAO ESQUERDA
NO *rotacionaEsquerda(NO *raiz)
{
    // NO *novo;
    // novo = raiz->dir;
    // raiz->dir = novo->esq;
    // novo->esq = raiz;
    // novo->cor = raiz->cor;
    // raiz->cor = RED;
    // return novo;

    NO *aux;

    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz = aux;

    raiz->cor = raiz->esq->cor;
    raiz->esq->cor = RED;
    return aux;
}
// ROTACAO DIREITA
NO *rotacionaDireita(NO *raiz)
{
    // NO *novo = raiz->esq;
    // raiz->esq = novo->dir;
    // novo->dir = raiz;
    // novo->cor = raiz->cor;
    // raiz->cor = RED;
    // return novo;
    NO *aux;

    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz = aux;

    raiz->cor = raiz->dir->cor;
    raiz->dir->cor = RED;
    return aux;
}

psc *adicionar_lista_encadeada(psc *no, char palavra_adc[], int linha)
{
    if (no == NULL)
    {
        no = (psc *)malloc(sizeof(psc));
        if (no != NULL)
        {
            // printf("Memoria alocada\n");
            no->lugar = linha;
            no->prox = NULL;
            // printf("Palavra adiconada a lista\n");
            return no;
        }
    }
    else
    {
        no->prox = adicionar_lista_encadeada(no->prox, palavra_adc, linha);
    }
    return no;
}

NO *cria_no(char palavra_adc[], int linha, int *resp)
{
    NO *novo;
    novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        *resp = 0;
        return NULL;
    }
    strcpy(novo->palavra, palavra_adc);
    novo->local = (psc *)malloc(sizeof(psc));
    novo->local->lugar = linha;
    novo->local->prox = NULL;
    novo->cor = RED;
    novo->dir = NULL;
    novo->esq = NULL;
    *resp = 1;
    return novo;
}

NO *insere_no(NO *H, char palavra_adc[], int *resp, int linha)
{
    if (H == NULL)
    {
        // printf("Adiciona\n");
        H = cria_no(palavra_adc, linha, resp);
    }
    else if (strcmp(palavra_adc, H->palavra) == 0)
    {
        // printf("Aidionando %s na lista\n", H->palavra);
        H->local = adicionar_lista_encadeada(H->local, palavra_adc, linha);
    }
    else if (strcmp(palavra_adc, H->palavra) < 0)
    {
        // printf("Passa pra esquerda\n");
        H->esq = insere_no(H->esq, palavra_adc, resp, linha);
    }
    else
    {
        // printf("Passa pra direita\n");
        H->dir = insere_no(H->dir, palavra_adc, resp, linha);
    }
    // COMPARAÇÕES
    if (cor(H->dir) == RED && cor(H->esq) == BLACK)
    {
        // printf("Rotacao Esquerda\n");
        H = rotacionaEsquerda(H);
    }
    if (cor(H->esq) == RED && cor(H->esq->esq) == RED)
    {
        // printf("Rotacao Direita\n");
        H = rotacionaDireita(H);
    }
    if ((cor(H->esq) == RED) && (cor(H->dir) == RED))
    {
        // printf("troca cor\n");
        trocar_cor(&H);
    }
    return H;
}

NO *insere_arv(NO *raiz, char palavra_adc[], int *resp, int linha)
{
    raiz = insere_no(raiz, palavra_adc, resp, linha);
    // printf("voltou aki\n");
    if (raiz != NULL)
    {
        // printf("Raiz Preta\n");
        raiz->cor = BLACK;
    }
    // MOSTRAR PASSO A PASSO
    // exibir_palavras(raiz);
    return raiz;
}

NO *ler_arquivo(NO *raiz, const char *nome_arquivo)
{
    // clock_t = inicio, fim;
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "r");
    // clock_t = inicio, fim;
    float tempo;
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return raiz;
    }
    char linha[1000];
    char *token;
    int linha_atual = 1;
    clock_t inicio, fim;
    inicio = clock();
    // inicio = clock();
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        token = strtok(linha, " ");
        while (token != NULL)
        {
            int resp;
            // raiz = insere_no(raiz, token, &resp, linha_atual);
            // printf("_______________________\n");
            token[strcspn(token, "\n")] = '\0';
            raiz = insere_arv(raiz, token, &resp, linha_atual);
            token = strtok(NULL, " ");
        }
        linha_atual++;
        // printf("leitura concluida\n");
    }
    // fim = clock();
    fim = clock();
    tempo = (float)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    printf("tempo de insercao em milessegundos: %.2f\n", tempo);
    fclose(arquivo);
    return raiz;
}

void exibir_lista_encadeada(psc *lista)
{
    if (lista != NULL)
    {
        printf("%d ", lista->lugar);
        exibir_lista_encadeada(lista->prox);
    }
}

void exibir_palavras(NO *raiz)
{
    if (raiz != NULL)
    {
        printf("Palavra: %s\n", raiz->palavra);
        printf("Linhas: ");
        exibir_lista_encadeada(raiz->local);
        printf("\n");
        if (raiz->cor == 1)
        {
            printf("cor RED\n");
        }
        else
        {
            printf("cor BLACK\n");
        }
        printf("\n\n");
        exibir_palavras(raiz->esq);
        exibir_palavras(raiz->dir);
    }
}

void exibir_lista(psc *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->lugar);
        exibir_lista(raiz->prox);
    }
}

void exibir_no(NO *raiz, char palavra[], int *achou)
{

    NO *aux = buscar_palavra(raiz, palavra, achou);
    if (*achou != 0)
    {
        printf("Linha(s): ");
        exibir_lista(aux->local);
    }
}

NO *buscar_palavra(NO *raiz, char palavra_busca[], int *achou)
{
    if (raiz != NULL)
    {
        if (strcmp(raiz->palavra, palavra_busca) == 0)
        {
            // printf("Palavra encontrada\n");
            *achou = 1;
        }
        else if (strcmp(palavra_busca, raiz->palavra) < 0)
        {
            raiz = buscar_palavra(raiz->esq, palavra_busca, achou);
        }
        else
        {
            raiz = buscar_palavra(raiz->dir, palavra_busca, achou);
        }
    }
    return raiz;
}

NO *balancear(NO *raiz)
{
    if (cor(raiz->dir) == RED)
    {
        raiz = rotacionaEsquerda(raiz);
    }

    if (raiz->esq != NULL && cor(raiz->dir) == RED &&
        cor(raiz->esq->esq) == RED)
    {
        raiz = rotacionaDireita(raiz);
    }

    if (cor(raiz->esq) == RED && cor(raiz->dir) == RED)
    {
        trocar_cor(&raiz);
    }

    return raiz;
}

NO *move2DirRED(NO *raiz)
{
    trocar_cor(&raiz);
    if (cor(raiz->esq->esq) == RED)
    {
        raiz = rotacionaDireita(raiz);
    }
    trocar_cor(&raiz);
    return raiz;
}

NO *move2EsqRED(NO *raiz)
{
    // printf("Mover esquerda\n");
    trocar_cor(&raiz);
    if (cor(raiz->dir->esq) == RED)
    {
        raiz->dir = rotacionaDireita(raiz->dir);
    }
    raiz = rotacionaEsquerda(raiz);
    trocar_cor(&raiz);
    return raiz;
}

NO *procurar_menor(NO *atual)
{
    NO *no1 = atual;
    NO *no2 = atual->esq;

    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

NO *remover_menor(NO *raiz)
{
    if (raiz->esq == NULL)
    {
        free(raiz);
        return NULL;
    }
    if (cor(raiz->esq) == BLACK && cor(raiz->esq->esq) == BLACK)
    {
        raiz = move2EsqRED(raiz);
    }
    raiz->esq = remover_menor(raiz->esq);
    return balancear(raiz);
}

void limpar_lista(psc **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->prox != NULL)
        {
            limpar_lista(&(*raiz)->prox);
        }
        free(raiz);
    }
}

NO *remover_NO(NO *raiz, char palavra_excluir[])
{
    // printf("Comecou a remover o no\n\n");
    if (strcmp(palavra_excluir, raiz->palavra) < 0)
    {
        if (cor(raiz->esq) == BLACK && cor(raiz->esq->esq))
        {
            raiz = move2EsqRED(raiz);
        }
        raiz->esq = remover_NO(raiz->esq, palavra_excluir);
    }
    else
    {
        if (cor(raiz->esq) == RED)
        {
            raiz = rotacionaDireita(raiz);
        }
        if (strcmp(palavra_excluir, raiz->palavra) == 0 && raiz->dir == NULL)
        {
            free(raiz);
            return NULL;
        }
        if (cor(raiz->dir) == BLACK && cor(raiz->dir->esq) == BLACK)
        {
            raiz = move2DirRED(raiz);
        }
        if (strcmp(palavra_excluir, raiz->palavra) == 0)
        {
            NO *aux;
            aux = procurar_menor(raiz->dir);
            strcpy(raiz->palavra, aux->palavra);
            raiz->dir = remover_menor(raiz->dir);
        }
        else
        {
            raiz->dir = remover_NO(raiz->dir, palavra_excluir);
        }
    }
}

NO *excluir_palavra(NO *raiz, char palavra_excluir[], int *achou)
{
    NO *aux = buscar_palavra(raiz, palavra_excluir, achou);
    if (aux != NULL)
    {
        printf("No encontrada\n");
        if (strcmp(aux->palavra, palavra_excluir) == 0)
        {
            printf("Limpando lista\n");
            limpar_lista(&raiz->local);
            if (raiz->local == NULL)
            {
                printf("\nLista de palavras limpa\n");
            }
        }
        NO *H = raiz;
        raiz = remover_NO(H, palavra_excluir);
        if (raiz != NULL)
        {
            raiz->cor = BLACK;
        }
    }
    else
    {
        printf("\nEssa palavra nao existe\n");
    }
    return raiz;
}