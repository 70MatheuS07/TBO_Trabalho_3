#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TST_pages.h"
#include "TST_words.h"
#include "Arquivo.h"
#include "MaqBusca.h"
#include "page.h"
int main(int argc, char *argv[])
{
    int qtdlinhas = 0;
    qtdlinhas = ContaLinhasArquivoBuffer("index.txt") + 1;
    tPage **result = calloc(qtdlinhas, sizeof(tPage *));

    FILE *Graph_file = fopen("graph.txt", "r");
    tPage **grafo = calloc(qtdlinhas, sizeof(tPage *));
    MontaGrafo(grafo, Graph_file, qtdlinhas);
    CalculaPageRanks(grafo, qtdlinhas);

    TST_words *StopWords = CreateTST_words();
    FILE *Stop_file = fopen("stopwords.txt", "r");
    StopWords = MontaTST_StopWords(StopWords, Stop_file);
    fclose(Stop_file);

    FILE *index_file = fopen("index.txt", "r");
    TST_words *Terms = CreateTST_words();
    Terms = MontaTST_Terms(Terms, index_file, StopWords);
    fclose(index_file);

    liberaTST_words(StopWords);

    char palavra_search[1000];
    char lixo;
    int cont = 0;
    TST_pages *IntercPages, *ant;
    char *linha, *linhaPesquisa;
    while (1)
    {
        linha = ler_linha(stdin);

        if (linha == NULL)
        {
            break;
        }
        int tamlinha = strlen(linha);
        linhaPesquisa = calloc(tamlinha + 1, sizeof(char));
        strcpy(linhaPesquisa, linha);
        char *token = strtok(linha, " ");
        while (token != NULL)
        {
            if (cont == 0)
            {
                ant = TST_search_words(Terms, token);
                IntercPages = ant;
                cont++;
            }
            else
            {
                ant = TST_search_words(Terms, token);
                IntercPages = TST_intersection(ant, IntercPages);
            }
            token = strtok(NULL, " ");
        }
        cont = 0;
        int contPalavras = 0;
        result = getTSTWords(IntercPages, &contPalavras, qtdlinhas, result);
        OrdenaEImprimeSaida(grafo, result, qtdlinhas, linhaPesquisa);
        free(linha);
        free(linhaPesquisa);

        limpaPageResult(result);
    }

    liberaMatrizPage(result);
    liberaMatrizPage(grafo);
    liberaTST_words(Terms);

    return 0;
}