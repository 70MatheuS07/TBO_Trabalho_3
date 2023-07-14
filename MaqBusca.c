#include "MaqBusca.h"

TST_words *MontaTST_StopWords(TST_words *StopWords, FILE *Stop_file)
{
    char *stopword;
    while (1)
    {
        stopword = ler_linha(Stop_file);
        if (stopword == NULL)
        {
            break;
        }
        StopWords = TST_insert_words(StopWords, stopword, NULL);
        free(stopword);
    }
    return StopWords;
}

TST_words *MontaTST_Terms(TST_words *Terms, FILE *index_file, TST_words *StopWords)
{
    char *index;
    FILE *pages;
    while (1)
    {
        index = ler_linha(index_file);
        if (index == NULL)
        {
            break;
        }
        int tam = strlen(index) + 8;
        char *Pagesindex = malloc(sizeof(char) * tam);
        strcpy(Pagesindex, "pages/");

        strcat(Pagesindex, index);
        pages = fopen(Pagesindex, "r");
        while (1)
        {
            char *linha = ler_linha(pages);
            if (linha == NULL)
            {
                break;
            }
            char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t

            while (token != NULL)
            {
                if (!TST_search_StopWords(StopWords, token))
                {
                    Terms = TST_insert_words(Terms, token, index);
                }
                token = strtok(NULL, " \t");
            }
            free(linha);
        }
        free(index);
        free(Pagesindex);
    }
    fclose(pages);
    return Terms;
}
// acho que vou retirar, tentar fazer com outra estrutura
TST_words *MontaTST_graph(TST_words *Graph, FILE *graph_file)
{
    char *linha;
    char *arq_Origem;
    int qtd;
    while (1)
    {
        linha = ler_linha(graph_file);
        if (linha == NULL)
        {
            break;
        }
        char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t
        int cont = 0;
        while (token != NULL)
        {
            if (cont == 0)
            {
                arq_Origem = token;
            }
            else if (cont == 1)
            {
                qtd = atoi(token);
            }
            else
            {
                Graph = TST_insert_words(Graph, token, arq_Origem);
            }
            cont++;
            token = strtok(NULL, " \t");
        }
    }
}

void MontaGrafo(tPage **Graph, FILE *graph_file, int tam)
{
    char *linha;
    char *arq_Origem;
    int qtd, cont = 0;
    double pagerank;

    for (int i = 0;; i++)
    {
        linha = ler_linha(graph_file);
        if (linha == NULL)
        {
            break;
        }
        char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t
        while (token != NULL)
        {
            if (cont == 0)
            {
                arq_Origem = token;
            }
            else if (cont == 1)
            {
                qtd = atoi(token);
            }
            else
            {
                break;
            }
            pagerank = (1 / (double)tam);
            Graph[i] = CriaPagina(arq_Origem, pagerank, qtd, CriaLista());
            cont++;
            token = strtok(NULL, " \t");
        }
        free(linha);
        cont = 0;
    }
    fclose(graph_file);
    fopen("graph.txt", "r");
    int pos;
    for (int j = 0;; j++)
    {
        linha = ler_linha(graph_file);
        if (linha == NULL)
        {
            break;
        }
        char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t
        cont = 0;
        while (token != NULL)
        {
            if (cont == 0)
            {
                arq_Origem = token;
            }
            else if (cont == 1)
            {
                qtd = atoi(token);
            }
            else
            {

                for (int i = 0; i < tam; i++)
                {
                    if (strcmp(getNomePage(Graph[i]), token) == 0)
                    {
                        pos = j;
                        InsereNaLista(pos, getLista(Graph[i]));
                    }
                }
            }
            cont++;
            token = strtok(NULL, " \t");
        }
        cont = 0;
        free(linha);
    }
}
/**
void CalculaPageRanks(char **pages, tPage **Graph, int tamvet)
{

    int tam = 0;
    for (int i = 0; pages[i] != NULL; i++)
    {
        tam = i;
    }
    double *atual = calloc(tam, sizeof(double));
    int *map = calloc(tam, sizeof(int));

    // mapeia os termos no vetor principal
    int pos;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tamvet; j++)
        {
            if (strcmp(pages[i], getNomePage(j)) == 0)
            {
                pos = j;
                break;
            }
        }
        map[i] = pos;
        setPageRank(1 / tamvet, Graph[map[i]]);
    }
    // calcula o pagerank de fato
    double pagerank;
    double somatorio = 0;
    tPage *pagAtual;
    int finaliza = 0;
    while (1)
    {
        for (int i = 0; i < tam; i++)
        {
            pagAtual = Graph[map[i]];
            tCelula *p = RetornaPrimeiro(pagAtual);
            if (getQtd(p) == 0)
            {
                pagerank = (0.15 / tamvet) + 0.85 * getPageRank(pagAtual);
            }
            else
            {
                pagerank = (0.15 / tamvet);
            }
            while (p != NULL)
            {
                somatorio += getPageRank(Graph[getpos(p)]);
                p = RetornaProx(p);
            }
            pagerank += 0.85 * somatorio;
            atual[i] = pagerank;
        }

        for (int i = 0; i < tam; i++)
        {
            if ((getPageRank(Graph[map[i]]) - atual[i]) < pow(10, -6))
            {
                break;
                finaliza = 1;
            }
        }
        if (finaliza)
        {
            break;
        }

    }
}*/

void CalculaPageRanks(tPage **Graph, int tamvet)
{
    int tam = 0;
    double *atual = calloc(tamvet, sizeof(double));

    // mapeia os termos no vetor principal
    int pos;

    // calcula o pagerank de fato
    double pagerank;
    double somatorio = 0;
    tPage *pagAtual;
    while (1)
    {
        for (int i = 0; i < tamvet; i++)
        {
            pagAtual = Graph[i];
            tCelula *p = RetornaPrimeiro(getLista(pagAtual));
            if (getQtd(pagAtual) == 0)
            {
                pagerank = (0.15 / tamvet) + 0.85 * getPageRank(pagAtual);
            }
            else
            {
                pagerank = (0.15 / tamvet);
            }
            while (p != NULL)
            {
                somatorio += getPageRank(Graph[getpos(p)]) / (double)getQtd(Graph[getpos(p)]);
                p = RetornaProx(p);
            }
            pagerank += 0.85 * somatorio;
            atual[i] = pagerank;
            somatorio = 0;
        }
        double E = 0.0;
        for (int i = 0; i < tamvet; i++)
        {
            double diff = fabs(atual[i] - getPageRank(Graph[i]));
            E += diff;
            setPageRank(atual[i], Graph[i]);
        }
        if (E < pow(10, -6))
        {
            break;
        }
    }
}

void OrdenaEImprimeSaida(tPage**Grafo, tPage**pages, int tamvet, char*search){
    int i;

    for (i = 0; pages[i] != NULL; i++)
    {
        for(int j=0;j<tamvet;j++){
            if(strcmp(getNomePage(pages[i]),getNomePage(Grafo[j]))==0){
                setPageRank(getPageRank(Grafo[j]),pages[i]);
                break;
            }
        }
    }
    qsort(pages,i, sizeof(tPage*), PagesCmp);

    printf("search:%s\n", search);
    printf("pages:");
    for(i = 0; pages[i] != NULL; i++){
        if(pages[i+1]==NULL){
            printf("%s", getNomePage(pages[i]));
        }
        else{
            printf("%s ", getNomePage(pages[i]));
        }
    }
    printf("\npr:");
    for(i = 0; pages[i] != NULL; i++){
        if(pages[i+1]==NULL){
            printf("%lf", getPageRank(pages[i]));
        }
        else{
            printf("%lf ", getPageRank(pages[i]));
        }
    }
    printf("\n");
}


int PagesCmp(const void*page1, const void*page2){
    tPage *A1 = *(tPage**)page1;
    tPage *A2 = *(tPage**)page2;
    if(getPageRank(A1)<getPageRank(A2)){
        return 1;
    }
    else if(getPageRank(A1)>getPageRank(A2)){
        return -1;
    }

    return strcmp(getNomePage(A1), getNomePage(A2));   
}
