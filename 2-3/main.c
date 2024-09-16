#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcao.h"

int main()
{
    Arv *raiz;
    raiz = criar_raiz(raiz);
    char palavra_busca[20], palavra_adc[20],
        aux[20], nome_arquivo[100];

    int escolha, linha, opcao_5,
        opcao_3, opcao, opcao_4;

    double tempo, tempo_w;

    clock_t inicio, fim;
    LARGE_INTEGER inicio_w, fim_w, frequencia;

    escolha = -1;
    while (escolha != 6)
    {
        opcao = 0;
        opcao_3 = 0;
        opcao_4 = 0;
        opcao_5 = 0;
        printf("\n---------------------\n"
               "         MENU        \n"
               "---------------------\n");
        printf("\n---------------------\n"
               "1. Ler arquivo\n"
               "2. Exibir Arvore\n"
               "3. Buscar Palavra\n"
               "4. Remove Palavra\n"
               "5. Adicionar Palavra\n"
               "6. Sair\n"
               "---------------------\n"
               "Digite a opcao desejada: ");
        scanf("%d", &escolha);
        switch (escolha)
        {
            //--------------------------------------------------//
        case 1:
            printf("\n---------------------\n"
                   "     LER ARQUIVO     \n"
                   "---------------------\n");
            printf("\nDeseja realziar a leitura de um arquivo .txt?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                printf("\n\tLer arquivo\n");
                printf("Digite o nome do arquivo: ");
                scanf(" %[^\n]s", nome_arquivo);
                // raiz = ler_arquivo(raiz, "texto.txt");
                raiz = ler_arquivo(raiz, nome_arquivo);
            }
            break;
            //--------------------------------------------------//
        case 2:
            printf("\n---------------------\n"
                   "    EXIBIR ARVORE    \n"
                   "---------------------\n");
            printf("\nDeseja realziar a exibicao da Arvore?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                printf("\n\tExibindo Arvore 2-3:\n");
                exibirNoRecursivo(raiz);
            }
            break;
            //--------------------------------------------------//
        case 3:
            printf("\n---------------------\n"
                   "   BUSCAR PALAVRA    \n"
                   "---------------------\n");
            printf("\nDeseja buscar uma palavra para exibir?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                while (opcao_3 != 2)
                {
                    printf("\n\tBuscar Palavra\n");
                    printf("Digite a palavra que deseja buscar: ");

                    scanf(" %[^\n]s", palavra_busca);
                    int result = 0;

                    QueryPerformanceFrequency(&frequencia);
                    
                    QueryPerformanceCounter(&inicio_w);
                    inicio = clock();

                    buscar_palavra_exibir(raiz, palavra_busca, &result);

                    QueryPerformanceCounter(&fim_w);
                    fim = clock();

                    tempo_w = (double)(fim_w.QuadPart - inicio_w.QuadPart) * 1000.0 / frequencia.QuadPart;
                    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

                    if (result == 0)
                    {
                        printf("\nESSA PALAVRA NAO FOI ENCONTRADA\n");
                    }

                    printf("\ntempo de busca em milessegundos (clock): %.5lf\n", tempo);
                    printf("\ntempo de busca em milessegundos (windows): %.5lf\n", tempo_w);

                    printf("\nDeseja buscar outra palavra?\n");
                    opcoes(&opcao_3);
                }
            }
            break;
            //--------------------------------------------------//
        case 4:
            printf("\n---------------------\n"
                   "   REMOVER PALAVRA   \n"
                   "---------------------\n");
            printf("\nDeseja remover uma palavra?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                while (opcao_4 != 2)
                {
                    printf("Digite uma palavra que deseja remover: ");
                    char palavra_remover[20];
                    scanf(" %s", palavra_remover);
                    remover23(NULL, &raiz, palavra_remover);

                    printf("\nDeseja remover outra palavra?\n");
                    opcoes(&opcao_4);
                }
            }
            break;
            //--------------------------------------------------//
        case 5:
            printf("\n---------------------\n"
                   "  ADICIONAR PALAVRA  \n"
                   "---------------------\n");
            printf("\nDeseja adicionar uma palavra?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                while (opcao_5 != 2)
                {
                    printf("Digite a palavra que deseja adicionar: ");
                    scanf(" %s", palavra_adc);
                    printf("Digite a linha da palavra: ");
                    scanf(" %d", &linha);
                    insere_no(&raiz, palavra_adc, NULL, aux, linha);

                    printf("\nDeseja adicioanr outra palavra?\n");
                    opcoes(&opcao_5);
                }
            }
            break;
            //--------------------------------------------------//
        case 6:
            printf("\n---------------------\n"
                   "      FINALIZAR      \n"
                   "---------------------\n");
            printf("\nDeseja Finalizar o programa?\n");
            opcoes(&opcao);
            if (opcao == 1)
            {
                printf("\n\tFINALIZADO\n");
            }
            else
            {
                escolha = -1;
            }
            break;
            //--------------------------------------------------//
        default:
            printf("\nOpção inválida. Por favor, tente novamente.\n");
        }
    }
}