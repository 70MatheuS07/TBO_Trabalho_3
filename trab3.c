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
    int tamdir=strlen(argv[1])+15;
    char*diretorio=calloc(tamdir,sizeof(char));
    strcpy(diretorio, argv[1]);
    char*index_string=calloc(tamdir,sizeof(char));
    strcpy(index_string, strcat(diretorio, "/index.txt"));
    strcpy(diretorio, argv[1]);

    char*graph_string=calloc(tamdir,sizeof(char));
    strcpy(graph_string, strcat(diretorio, "/graph.txt"));
    strcpy(diretorio, argv[1]);

    char*stop_string=calloc(tamdir,sizeof(char));
    strcpy(stop_string, strcat(diretorio, "/stopwords.txt"));
    strcpy(diretorio, argv[1]);


    char*pages_string=calloc(tamdir,sizeof(char));
    pages_string=strcpy(pages_string, strcat(diretorio, "/pages/"));
    strcpy(diretorio, argv[1]);
    int qtdlinhas = 0;


    qtdlinhas = ContaLinhasArquivoBuffer(index_string);
    tPage **result = calloc(qtdlinhas + 1, sizeof(tPage *));

    FILE *Graph_file = fopen(graph_string, "r");
    tPage **grafo = calloc(qtdlinhas, sizeof(tPage *));
    MontaGrafo(grafo, Graph_file, qtdlinhas, graph_string);
    CalculaPageRanks(grafo, qtdlinhas);

    TST_words *StopWords = CreateTST_words();
    FILE *Stop_file = fopen(stop_string, "r");
    StopWords = MontaTST_StopWords(StopWords, Stop_file);
    fclose(Stop_file);

    FILE *index_file = fopen(index_string, "r");
    TST_words *Terms = CreateTST_words();
    Terms = MontaTST_Terms(Terms, index_file, StopWords,pages_string);
    fclose(index_file);

    liberaTST_words(StopWords);

    char palavra_search[1000];
    char lixo;
    int cont = 0;
    TST_pages *IntercPages = NULL, *ant = NULL;
    char *linha, *linhaPesquisa;
    int value = 1;
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
        if (IntercPages != ant)
            liberaTST_Pages(IntercPages);
        free(linha);
        free(linhaPesquisa);

        limpaPageResult(result, qtdlinhas);
        value++;
    }

    liberaMatrizPage(result, qtdlinhas);
    liberaMatrizPage(grafo, qtdlinhas);
    liberaTST_words(Terms);
    free(stop_string);
    free(graph_string);
    free(index_string);
    free(pages_string);
    free(diretorio);

    return 0;
}