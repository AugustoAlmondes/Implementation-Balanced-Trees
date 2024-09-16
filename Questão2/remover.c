#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

void MaiorInfoRemoveEsq(Arv **raiz, Arv **PaiMaior, Arv **MaiorInfoRemove, int LocalInfo)
{
    if (MaiorInfoRemove != NULL)
    {
        if ((*MaiorInfoRemove)->filho_esq == NULL)
        {
            char aux[20];
            if (LocalInfo == 1)
            {
                // aux = (*raiz)->info1;
                strcpy(aux, (*raiz)->palavra_um);

                if ((*MaiorInfoRemove)->num_chaves == 2)
                {
                    // (*raiz)->info1 = (*MaiorInfoRemove)->info2;
                    strcpy((*raiz)->palavra_um, (*MaiorInfoRemove)->palavra_dois);
                    // (*MaiorInfoRemove)->info2 = aux;
                    strcpy((*MaiorInfoRemove)->palavra_dois, aux);
                }
                else
                {
                    // (*raiz)->info1 = (*MaiorInfoRemove)->info1;
                    strcpy((*raiz)->palavra_um, (*MaiorInfoRemove)->palavra_um);
                    // (*MaiorInfoRemove)->info1 = aux;
                    strcpy((*MaiorInfoRemove)->palavra_um, aux);
                }
            }
            else if (LocalInfo == 2)
            {
                // aux = (*raiz)->info2;
                strcpy(aux, (*raiz)->palavra_dois);

                if ((*MaiorInfoRemove)->num_chaves == 2)
                {
                    // (*raiz)->info2 = (*MaiorInfoRemove)->info2;
                    strcpy((*raiz)->palavra_dois, (*MaiorInfoRemove)->palavra_dois);
                    // (*MaiorInfoRemove)->info2 = aux;
                    strcpy((*MaiorInfoRemove)->palavra_dois, aux);
                }
                else
                {
                    // (*raiz)->info2 = (*MaiorInfoRemove)->info1;
                    strcpy((*raiz)->palavra_dois, (*MaiorInfoRemove)->palavra_um);
                    // (*MaiorInfoRemove)->info1 = aux;
                    strcpy((*MaiorInfoRemove)->palavra_um, aux);
                }
            }

            remover23(&(*PaiMaior), &(*MaiorInfoRemove), aux);
        }
        else
        {
            if ((*MaiorInfoRemove)->num_chaves == 2)
            {
                MaiorInfoRemoveEsq(&(*raiz), &(*MaiorInfoRemove), &((*MaiorInfoRemove)->filho_dir), LocalInfo);
            }
            else if ((*MaiorInfoRemove)->num_chaves == 1)
            {
                MaiorInfoRemoveEsq(&(*raiz), &(*MaiorInfoRemove), &((*MaiorInfoRemove)->filho_crt), LocalInfo);
            }
        }
    }
    Redistribui(&(*MaiorInfoRemove), &(*PaiMaior));
}

void remover23(Arv **pai, Arv **raiz, char palavra[])
{
    if (*raiz != NULL)
    {
        if (strcmp(palavra, (*raiz)->palavra_um))
        {
            if (eh_folha(*raiz))
            {
                if ((*raiz)->num_chaves == 2)
                {
                    // (*raiz)->info1 = (*raiz)->info2;
                    strcpy((*raiz)->palavra_um, (*raiz)->palavra_dois);
                    (*raiz)->num_chaves = 1;
                }
                else if ((*raiz)->num_chaves == 1)
                {
                    (*raiz)->num_chaves = 0;
                }
            }
            else
            {
                Arv **MaiorInfoRemove = &((*raiz)->filho_esq);
                Arv **PaiMaior = raiz;
                MaiorInfoRemoveEsq(&(*raiz), PaiMaior, MaiorInfoRemove, 1);
            }
        }
        else if ((*raiz)->num_chaves == 2 && strcmp((*raiz)->palavra_dois, palavra) == 0)
        {
            if (eh_folha(*raiz))
            {
                (*raiz)->num_chaves = 1;
            }
            else
            {
                Arv **MaiorInfoRemove = &((*raiz)->filho_crt);
                Arv **PaiMaior = raiz;
                MaiorInfoRemoveEsq(&(*raiz), &(*PaiMaior),&(*MaiorInfoRemove), 2);
            }
        }
        else if (strcmp(palavra, (*raiz)->palavra_um) < 0)
        {
            remover23(&(*raiz), &((*raiz)->filho_esq), palavra);
        }
        else if ((*raiz)->num_chaves == 1 ||
                 (*raiz)->num_chaves == 2 &&
                     strcmp(palavra, (*raiz)->palavra_dois) < 0)
        {
            remover23(&(*raiz), &((*raiz)->filho_crt), palavra);
        }
        else
        {
            remover23(&(*raiz), &((*raiz)->filho_dir), palavra);
        }
    }
    Redistribui(&(*raiz),&(*pai));
}

void Redistribui(Arv **raiz, Arv **pai)
{
    if (*raiz != NULL)
        if ((*raiz)->num_chaves == 0)
        {
            if (pai != NULL)
            {
                if ((*raiz) == ((*pai)->filho_dir))
                {
                    if ((*pai)->filho_crt->num_chaves == 2)
                    {
                        // (*raiz)->info1 = (*pai)->info1;
                        strcpy((*raiz)->palavra_um, (*pai)->palavra_dois);
                        (*raiz)->num_chaves = 1;
                        // (*pai)->info2 = (*pai)->filho_crt->info2;
                        strcpy((*pai)->palavra_dois, (*pai)->filho_crt->palavra_dois);
                        (*pai)->filho_crt->num_chaves = 1;
                        (*raiz)->filho_esq = (*pai)->filho_crt->filho_dir;
                        (*pai)->filho_crt->filho_dir = NULL;
                    }
                    else if ((*pai)->filho_crt->num_chaves == 1)
                    {
                        // (*raiz)->info2 = (*pai)->info2;
                        strcpy((*raiz)->palavra_dois, (*pai)->palavra_dois);
                        (*raiz)->filho_dir = (*raiz)->filho_crt;
                        // (*raiz)->info1 = (*pai)->filho_crt->info1;
                        strcpy((*raiz)->palavra_um, (*pai)->filho_crt->palavra_um);
                        (*raiz)->num_chaves = 2;
                        (*pai)->num_chaves = 1;
                        (*raiz)->filho_crt = (*pai)->filho_crt->filho_crt;
                        (*raiz)->filho_esq = (*pai)->filho_crt->filho_esq;
                        free((*pai)->filho_crt);
                        (*pai)->filho_crt = (*raiz);
                        (*pai)->filho_dir = NULL;
                    }
                }
                else if ((*raiz) == (*pai)->filho_crt)
                {
                    if ((*pai)->filho_esq->num_chaves == 2)
                    {
                        // (*raiz)->info1 = (*pai)->info1;
                        strcpy((*raiz)->palavra_um, (*pai)->palavra_um);
                        (*raiz)->num_chaves = 1;
                        // (*pai)->info1 = (*pai)->filho_esq->info2;
                        strcpy((*pai)->palavra_um, (*pai)->filho_esq->palavra_dois);
                        (*pai)->filho_esq->num_chaves = 1;
                        (*raiz)->filho_esq = (*pai)->filho_esq->filho_dir;
                        (*pai)->filho_esq->filho_dir = NULL;
                    }
                    else if ((*pai)->filho_esq->num_chaves == 1)
                    {
                        if ((*pai)->num_chaves == 2)
                        {
                            // (*raiz)->info2 = (*pai)->info1;
                            strcpy((*raiz)->palavra_dois, (*pai)->palavra_um);
                            // (*raiz)->info1 = (*pai)->filho_esq->info1;
                            strcpy((*raiz)->palavra_um, (*pai)->filho_esq->palavra_um);
                            (*raiz)->num_chaves = 2;
                            (*raiz)->filho_dir = (*raiz)->filho_crt;
                            (*raiz)->filho_crt = (*pai)->filho_esq->filho_crt;
                            (*raiz)->filho_esq = (*pai)->filho_esq->filho_esq;
                            free((*pai)->filho_esq);
                            (*pai)->filho_esq = (*raiz);
                            // (*pai)->info1 = (*pai)->info2;
                            strcpy((*pai)->palavra_um, (*pai)->palavra_dois);
                            (*pai)->num_chaves = 1;
                            (*pai)->filho_crt = (*pai)->filho_dir;
                            (*pai)->filho_dir = NULL;
                        }
                        else if ((*pai)->num_chaves == 1)
                        {
                            // (*raiz)->info2 = (*pai)->info1;
                            strcpy((*raiz)->palavra_dois, (*pai)->palavra_um);
                            // (*raiz)->info1 = (*pai)->filho_esq->info1;
                            strcpy((*raiz)->palavra_um, (*pai)->filho_esq->palavra_um);
                            (*raiz)->num_chaves = 2;
                            (*pai)->num_chaves = 0;
                            (*raiz)->filho_dir = (*raiz)->filho_crt;
                            (*raiz)->filho_crt = (*pai)->filho_esq->filho_crt;
                            (*raiz)->filho_esq = (*pai)->filho_esq->filho_esq;
                            free((*pai)->filho_esq);
                            (*pai)->filho_esq = NULL;
                        }
                    }
                }
                else if ((*raiz) == (*pai)->filho_esq)
                {
                    if ((*pai)->filho_crt->num_chaves == 2)
                    {
                        // (*raiz)->info1 = (*pai)->info1;
                        strcpy((*raiz)->palavra_um, (*pai)->palavra_um);
                        (*raiz)->num_chaves = 1;
                        // (*pai)->info1 = (*pai)->filho_crt->info1;
                        strcpy((*raiz)->palavra_um, (*pai)->palavra_um);
                        (*pai)->filho_crt->num_chaves = 1;
                        // (*pai)->filho_crt->info1 = (*pai)->filho_crt->info2;
                        strcpy((*pai)->filho_crt->palavra_um, (*pai)->filho_crt->palavra_dois);
                        (*raiz)->filho_esq = (*raiz)->filho_crt;
                        (*raiz)->filho_crt = (*pai)->filho_crt->filho_esq;
                        (*pai)->filho_crt->filho_esq = (*pai)->filho_crt->filho_crt;
                        (*pai)->filho_crt->filho_crt = (*pai)->filho_crt->filho_dir;
                        (*pai)->filho_crt->filho_dir = NULL;
                    }
                    else if ((*pai)->filho_crt->num_chaves == 1)
                    {
                        if ((*pai)->num_chaves == 2)
                        {
                            // (*raiz)->info1 = (*pai)->info1;
                            strcpy((*raiz)->palavra_um, (*pai)->palavra_um);
                            // (*raiz)->info2 = (*pai)->filho_crt->info1;
                            strcpy((*raiz)->palavra_dois, (*pai)->filho_crt->palavra_um);
                            (*raiz)->num_chaves = 2;
                            (*raiz)->filho_esq = (*raiz)->filho_crt;
                            (*raiz)->filho_crt = (*pai)->filho_crt->filho_esq;
                            (*raiz)->filho_dir = (*pai)->filho_crt->filho_crt;
                            // (*pai)->info1 = (*pai)->info2;
                            strcpy((*pai)->palavra_um, (*pai)->palavra_dois);
                            (*pai)->num_chaves = 1;
                            free((*pai)->filho_crt);
                            (*pai)->filho_crt = (*pai)->filho_dir;
                            (*pai)->filho_dir = NULL;
                        }
                        else if ((*pai)->num_chaves == 1)
                        {
                            // (*raiz)->info1 = (*pai)->info1;
                            strcpy((*raiz)->palavra_um, (*pai)->palavra_um);
                            (*raiz)->filho_esq = (*raiz)->filho_crt;
                            // (*raiz)->info2 = (*pai)->filho_crt->info1;
                            strcpy((*raiz)->palavra_dois, (*pai)->filho_crt->palavra_um);
                            (*raiz)->filho_crt = (*pai)->filho_crt->filho_esq;
                            (*raiz)->filho_dir = (*pai)->filho_crt->filho_crt;
                            (*pai)->num_chaves = 0;
                            (*raiz)->num_chaves = 2;
                            free((*pai)->filho_crt);
                            (*pai)->filho_crt = (*raiz);
                            (*pai)->filho_esq = NULL;
                        }
                    }
                }
            }
            else if (pai == NULL)
            {
                (*raiz) = (*raiz)->filho_crt;
            }
            else if (eh_folha(*raiz) && pai == NULL)
            {
                free(*raiz);
                *raiz = NULL;
            }
        }
}