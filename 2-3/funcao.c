#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcao.h"

Arv *criar_raiz(Arv *raiz)
{
    return NULL;
}

Arv *quebra_no(Arv **no, char palavra[], char sobe[], Arv *filho)
{
    // printf("Quebra no\n");
    Arv *novo;
    novo = NULL;
    if (strcmp(palavra, (*no)->palavra_dois) > 0)
    {
        // printf("%s Sobe\n", (*no)->palavra_dois);
        strcpy(sobe, (*no)->palavra_dois);
        novo = cria_no(palavra, (*no)->filho_dir, filho, NULL);
    }
    else if (strcmp(palavra, (*no)->palavra_um) > 0)
    {
        strcpy(sobe, palavra);
        // printf("%s Sobe\n", palavra);
        novo = cria_no((*no)->palavra_dois, filho, (*no)->filho_dir, NULL);
    }
    else
    {
        // printf("%s Sobe\n", (*no)->palavra_um);
        // strcpy((*no)->palavra_um,sobe);
        strcpy(sobe, (*no)->palavra_um);
        novo = cria_no((*no)->palavra_dois, (*no)->filho_crt, (*no)->filho_dir, NULL);
        strcpy((*no)->palavra_um, palavra);
        (*no)->filho_crt = filho;
    }
    // printf("retornou raiz\n");
    (*no)->filho_dir = NULL;
    (*no)->num_chaves = 1;
    // strcpy((*no)->palavra_dois,NULL);
    return novo;
}

void adicionar_palavra_lista(posicao **raiz, char palavra[], int linha)
{
    if ((*raiz) == NULL)
    {
        // printf("entrou\n");
        *raiz = (posicao *)malloc(sizeof(posicao));
        // printf("alocou\n");
        (*raiz)->lugar = linha;
        (*raiz)->prox_plavra = NULL;
    }
    else
    {
        // printf("proximo\n");
        adicionar_palavra_lista(&(*raiz)->prox_plavra, palavra, linha);
    }
}

Arv *adiciona_no(Arv *raiz, char palavra[], Arv *filho_dir, int linha)
{
    // printf("Adiciona no NO\n");
    if (strcmp(palavra, raiz->palavra_um) < 0)
    {
        raiz->psc_palavra_2 = raiz->psc_palavra_1;
        strcpy(raiz->palavra_dois, raiz->palavra_um);
        strcpy(raiz->palavra_um, palavra);
        raiz->filho_dir = raiz->filho_crt;
        raiz->filho_crt = filho_dir;
    }
    else
    {
        strcpy(raiz->palavra_dois, palavra);
        raiz->filho_dir = filho_dir;
    }
    raiz->num_chaves = 2;
    return raiz;
}

Arv *eh_folha(Arv *raiz)
{
    if (raiz != NULL && raiz->filho_esq == NULL &&
        raiz->filho_crt == NULL && raiz->filho_dir == NULL)
    {
        return raiz;
    }
    return NULL;
}

Arv *cria_no(char palavra[], Arv *esquerda, Arv *centro, Arv *direita)
{
    // printf("\n\tCriar novo NO\n");
    Arv *novo;
    novo = (Arv *)malloc(sizeof(Arv));
    // novo = adicionar_info(novo, palavra, esquerda, centro, direita);
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        return NULL;
    }
    strcpy(novo->palavra_um, palavra);
    novo->psc_palavra_1 = (posicao *)malloc(sizeof(posicao));
    novo->psc_palavra_2 = (posicao *)malloc(sizeof(posicao));
    novo->psc_palavra_1 = NULL;
    novo->psc_palavra_2 = NULL;
    novo->filho_crt = centro;
    novo->filho_dir = direita;
    novo->filho_esq = esquerda;
    novo->num_chaves = 1;
    // printf("\n\tNO Criado\n");
    return novo;
}

Arv *insere_no(Arv **raiz, char palavra[], Arv *pai, char sobe[], int linha)
{
    Arv *maior_no;
    maior_no = NULL;
    if (*raiz == NULL)
    {
        // printf("Raiz eh NULL\n");
        *raiz = cria_no(palavra, NULL, NULL, NULL);
        // printf("%d de augusto", linha);
        // printf("Palavra da raiz %s\n", (*raiz)->palavra_um);
    }
    else
    {
        if (strcmp(palavra, (*raiz)->palavra_um) == 0)
        {
            // printf("palavra igual a %s\n", (*raiz)->palavra_um);
            (*raiz)->psc_palavra_1 = NULL;
            adicionar_palavra_lista(&(*raiz)->psc_palavra_1, palavra, linha);
        }
        else if (strcmp(palavra, (*raiz)->palavra_dois) == 0)
        {
            // printf("palavra igual a %s\n", (*raiz)->palavra_dois);
            (*raiz)->psc_palavra_2 = NULL;
            adicionar_palavra_lista(&(*raiz)->psc_palavra_2, palavra, linha);
        }
        else
        {
            // printf("Nao e null\n");
            if (eh_folha(*raiz))
            {
                // printf("eh folha\n");
                if ((*raiz)->num_chaves == 1)
                {
                    *raiz = adiciona_no(*raiz, palavra, NULL, linha);
                    // printf("Palavra 1 da Raiz adicionada %s\n", (*raiz)->palavra_um);
                    // printf("Palavra 2 da Raiz adicionada %s\n", (*raiz)->palavra_dois);
                    maior_no = NULL;
                }
                else
                {
                    // printf("Eh folha e ta completo\n");
                    maior_no = quebra_no(raiz, palavra, sobe, NULL);
                    // printf("Raiz retornada %s\n", (*raiz)->palavra_um);
                    // printf("Maior no %s\n", maior_no->palavra_um);
                    if (pai == NULL)
                    {
                        // printf("Adicionando Pai\n");
                        // printf("Pai vai ser %s\n", sobe);
                        // printf("A linha de %s eh %d", sobe);
                        *raiz = cria_no(sobe, *raiz, maior_no, NULL);
                        maior_no = NULL;
                    }
                }
            }
            else
            {
                if (strcmp(palavra, (*raiz)->palavra_um) < 0)
                {
                    // printf("Vai pra esquerda\n");
                    maior_no = insere_no(&((*raiz)->filho_esq), palavra, *raiz, sobe, linha);
                }
                else if ((*raiz)->num_chaves == 1 || (*raiz)->num_chaves == 2 && (strcmp(palavra, (*raiz)->palavra_dois) < 0))
                {
                    // printf("Vai pro centro\n");
                    maior_no = insere_no((&(*raiz)->filho_crt), palavra, *raiz, sobe, linha);
                }
                else
                {
                    // printf("Vai pra direita\n");
                    maior_no = insere_no((&(*raiz)->filho_dir), palavra, *raiz, sobe, linha);
                }

                if (maior_no != NULL)
                {
                    if ((*raiz)->num_chaves == 1)
                    {
                        // printf("nao eh folha e tem 1 info\n");
                        *raiz = adiciona_no(*raiz, sobe, maior_no, linha);
                        maior_no = NULL;
                    }
                    else
                    {
                        // printf("sobrou aqui\n");
                        // printf("A sobe eh %s\n", sobe);
                        char aux[20];
                        strcpy(aux, sobe);
                        // printf("palavra aux %s\n", aux);
                        maior_no = quebra_no(raiz, aux, sobe, maior_no);
                        // printf("maioo no dados %s\n", maior_no->palavra_um);
                        if (pai == NULL)
                        {
                            // printf("Sem pai o sobe eh %s\n", sobe);
                            // printf("Palavra 1 da Raiz adicionada %s\n", (*raiz)->palavra_um);
                            // printf("Palavra 2 da Raiz adicionada %s\n", (*raiz)->palavra_dois);
                            *raiz = cria_no(sobe, *raiz, maior_no, NULL);
                            maior_no = NULL;
                        }
                    }
                }
            }
        }
    }
    // printf("retorna maior no\n");
    return maior_no;
}

void exibirNoRecursivo(Arv *no)
{
    if (no != NULL)
    {
        if (no->num_chaves > 0)
        {
            printf("Informacao 1: %s\n", no->palavra_um);
        }
        if (no->num_chaves == 2)
        {
            printf("Informacao 2: %s\n", no->palavra_dois);
        }
        printf("NUm.info %d\n", no->num_chaves);
        printf("___________________________\n");
        exibirNoRecursivo(no->filho_esq);
        exibirNoRecursivo(no->filho_crt);
        exibirNoRecursivo(no->filho_dir);
    }
}

void exibir_linhas(posicao *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->lugar);
        exibir_linhas(raiz->prox_plavra);
    }
}

void buscar_palavra_exibir(Arv *raiz, char palavra[], int *result)
{
    if (raiz != NULL)
    {
        if (strcmp(palavra, raiz->palavra_um) == 0)
        {
            // printf("Palavra: %s\n", palavra);
            // printf("Linha: ");
            exibir_linhas(raiz->psc_palavra_1);
            *result = 1;
        }
        if (strcmp(palavra, raiz->palavra_dois) == 0)
        {
            // printf("Palavra: %s\n", palavra);
            // printf("Linha: ");
            exibir_linhas(raiz->psc_palavra_2);
        }
        buscar_palavra_exibir(raiz->filho_esq, palavra, result);
        buscar_palavra_exibir(raiz->filho_crt, palavra, result);
        buscar_palavra_exibir(raiz->filho_dir, palavra, result);
    }
}

void verificar_repeticao(Arv *raiz, char palavra[], int *result)
{
    if (raiz != NULL)
    {
        if (strcmp(palavra, raiz->palavra_um) == 0)
        {
            *result = 1;
        }
        else if (strcmp(palavra, raiz->palavra_dois) == 0)
        {
            *result = 1;
        }
        else if (strcmp(palavra, raiz->palavra_um) < 0)
        {
            verificar_repeticao(raiz->filho_esq, palavra, result);
        }
        else if (strcmp(palavra, raiz->palavra_dois) < 0)
        {
            verificar_repeticao(raiz->filho_crt, palavra, result);
        }
        else if (strcmp(palavra, raiz->palavra_dois) > 0)
        {
            verificar_repeticao(raiz->filho_dir, palavra, result);
        }
    }
}

Arv *ler_arquivo(Arv *raiz, const char *nome_arquivo)
{
    Arv *aux;
    FILE *arquivo;
    // clock_t = inicio, fim;
    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return raiz;
    }

    char linha[1000];
    char *token;
    int linha_atual = 1;
    char sobe[20];
    clock_t  inicio, fim;
    inicio = clock();
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        token = strtok(linha, " ");
        while (token != NULL)
        {
            int resp;
            token[strcspn(token, "\n")] = '\0';
            // printf("\ninserir %s\n", token);
            int result = 0;
            verificar_repeticao(raiz, token, &result);
            if (result == 0)
            {
                insere_no(&raiz, token, NULL, sobe, linha_atual);
            }
            else
            {
                buscar_para_adicionar(&raiz, token, linha_atual);
            }
            token = strtok(NULL, " ");
        }
        linha_atual++;
    }
    fim = clock();
    fclose(arquivo);
    double tempo = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de insercao em milessegundos: %.2lf", tempo);
    printf("\nLeitura feita com sucesso\n");
    return raiz;
}

void buscar_para_adicionar(Arv **raiz, char palavra[], int linha)
{
    if ((*raiz) != NULL)
    {
        if (strcmp(palavra, (*raiz)->palavra_um) == 0)
        {
            adicionar_palavra_lista(&((*raiz))->psc_palavra_1, palavra, linha);
        }
        else if (strcmp(palavra, (*raiz)->palavra_dois) == 0)
        {
            adicionar_palavra_lista(&((*raiz))->psc_palavra_2, palavra, linha);
        }
        else if (strcmp(palavra, (*raiz)->palavra_um) < 0)
        {
            buscar_para_adicionar(&(*raiz)->filho_esq, palavra, linha);
        }
        else if (strcmp(palavra, (*raiz)->palavra_dois) < 0)
        {
            buscar_para_adicionar(&((*raiz)->filho_crt), palavra, linha);
        }
        else if (strcmp(palavra, (*raiz)->palavra_dois) > 0)
        {
            buscar_para_adicionar(&((*raiz)->filho_dir), palavra, linha);
        }
    }
}

void opcoes(int *opcao)
{
    printf("\n"
           "1 - Sim\n"
           "2 - Nao\n"
           "opcao: ");
    scanf("%d", opcao);

    if (*opcao != 1 && *opcao != 2)
    {
        *opcao = 0;
        printf("Essa opcao nao existe\n");
        opcoes(opcao);
    }
}