Com base no relatório fornecido, aqui está o conteúdo sugerido para o arquivo `README.md` do seu repositório GitHub:

---

# Implementação de Árvores Rubro-Negra e 2-3 em C

Este projeto tem como objetivo implementar e testar duas estruturas de dados: **Árvore Rubro-Negra** e **Árvore 2-3**. O projeto permite realizar operações de inserção, remoção e busca em ambas as estruturas, medindo o desempenho das operações e comparando os tempos de execução.

## Funcionalidades

O programa permite:

- **Inserir** palavras em ambas as árvores.
- **Buscar** uma palavra específica nas árvores.
- **Remover** palavras de ambas as árvores.
- **Exibir** as palavras armazenadas em ordem alfabética.
- **Ler um arquivo** de texto e inserir suas palavras automaticamente nas árvores.
- **Medição de tempo** de execução para operações de busca, comparando as árvores Rubro-Negra e 2-3.

## Estruturas de Dados Utilizadas

### Árvores Rubro-Negra

A árvore Rubro-Negra é uma árvore binária de busca balanceada com complexidade de tempo de O(log n) para operações de busca, inserção e remoção. Cada nó possui uma cor (vermelho ou preto) que ajuda a manter o balanceamento da árvore.

### Árvores 2-3

A árvore 2-3 é uma árvore de busca balanceada em que cada nó interno pode ter 2 ou 3 filhos, o que mantém a altura mínima possível, proporcionando eficiência nas operações de busca, inserção e remoção.

## Como Funciona

O código implementa funções para manipulação das árvores, tais como:

### Funções Principais

- **main()**: Controla o fluxo do programa, com um menu interativo para escolher operações como inserir, buscar, remover e exibir palavras.
- **insere_arv()**: Adiciona uma nova palavra à árvore, mantendo a estrutura balanceada.
- **buscar_palavra()**: Busca uma palavra específica na árvore e exibe a linha do arquivo em que foi encontrada.
- **excluir_palavra()**: Remove uma palavra da árvore, se encontrada.
- **exibir_palavras()**: Exibe todas as palavras armazenadas na árvore em ordem alfabética.
- **ler_arquivo()**: Lê um arquivo de texto e insere automaticamente as palavras na árvore.

### Funções Auxiliares

- **rotacionaEsquerda()** e **rotacionaDireita()**: Funções de rotação utilizadas na árvore Rubro-Negra para manter o balanceamento após operações de inserção ou remoção.
- **trocar_cor()**: Altera a cor dos nós da árvore Rubro-Negra durante as operações de balanceamento.
- **cria_no()**: Cria um novo nó para ser inserido na árvore.

## Comparação de Desempenho

Durante o desenvolvimento, foi realizada uma comparação de desempenho entre as árvores Rubro-Negra e 2-3, utilizando um arquivo de texto com **8645 palavras**. A palavra "you" foi buscada 20 vezes em ambas as estruturas, e os tempos de execução foram medidos.

### Resultados:

- **Árvore 2-3**: Tempo médio de busca: **0.310205 ms**
- **Árvore Rubro-Negra**: Tempo médio de busca: **0.74109 ms**

Os resultados indicam que a **Árvore 2-3** foi mais eficiente na busca, enquanto a **Árvore Rubro-Negra** tem um desempenho equilibrado em inserções e remoções frequentes.

## Requisitos

Para compilar e executar o código, é necessário:

- **Compilador C** (gcc ou outro compatível)
- Sistema operacional Windows ou Linux
  - Para Windows, a biblioteca `windows.h` é usada para medições de tempo.
  - Para Linux, a biblioteca `time.h` é utilizada.

## Conclusão

O projeto demonstra o uso eficiente de árvores balanceadas em C e proporciona uma comparação clara de desempenho entre a **Árvore Rubro-Negra** e a **Árvore 2-3**. A árvore 2-3 mostrou-se mais eficiente em operações de busca, enquanto a Rubro-Negra se destaca em cenários com inserções e remoções constantes.

---

Isso fornecerá aos usuários do seu repositório uma visão clara de como o projeto funciona, suas funcionalidades e como executar o código.
