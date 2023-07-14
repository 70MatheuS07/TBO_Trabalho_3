#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page.h"
struct page
{
    char *nome;
    double PageRank;
    int qtd;
    tLista *lista;
};

tPage *CriaPagina(char *nome, double PageRank, int qtd, tLista *lista)
{
    tPage *page = malloc(sizeof(tPage));
    page->nome = strdup(nome);
    page->PageRank = PageRank;
    page->qtd = qtd;
    page->lista = lista;
    return page;
}

char *getNomePage(tPage *p)
{
    return p->nome;
}

double getPageRank(tPage *p)
{
    return p->PageRank;
}

tLista *getLista(tPage *p)
{
    return p->lista;
}

int getQtd(tPage *p)
{
    return p->qtd;
}

void setPageRank(double pagerank, tPage *page)
{
    page->PageRank = pagerank;
}

void liberaMatrizPage(tPage **page)
{
    for (int i = 0; page[i] != NULL; i++)
    {
        if (page[i]->nome != NULL)
        {
            free(page[i]->nome);
        }

        if (page[i]->lista != NULL)
        {
            LiberaLista(page[i]->lista);
        }

        if (page[i] != NULL)
        {
            free(page[i]);
        }
    }

    free(page);
}

void limpaPageResult(tPage **result)
{
    for (int i = 0; result[i] != NULL; i++)
    {
        free(result[i]->nome);
        result[i]->nome = NULL;
        free(result[i]);
        result[i] = NULL;
    }
}