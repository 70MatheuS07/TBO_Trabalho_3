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

/**
 * @brief Salva page rank.
 *
 * @param pagerank
 * @param page
 */
void setPageRank(double pagerank, tPage *page)
{
    page->PageRank = pagerank;
}

/**
 * @brief Libera memória da page.
 *
 * @param page
 * @param qtd
 */
void liberaMatrizPage(tPage **page, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        if (page[i] == NULL)
        {
            break;
        }
        if (page[i]->nome != NULL)
        {
            free(page[i]->nome);
            page[i]->nome = NULL;
        }

        if (page[i]->lista != NULL)
        {
            LiberaLista(page[i]->lista);
            page[i]->lista == NULL;
        }

        if (page[i] != NULL)
        {
            free(page[i]);
            page[i] = NULL;
        }
    }

    if (page != NULL)
    {
        free(page);
        page = NULL;
    }
}

void limpaPageResult(tPage **result, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        if (result[i] == NULL)
        {
            break;
        }
        if (result[i]->nome != NULL)
        {
            free(result[i]->nome);
            result[i]->nome = NULL;
        }

        if (result[i]->lista != NULL)
        {
            LiberaLista(result[i]->lista);
        }

        if (result[i] != NULL)
        {
            free(result[i]);
            result[i] = NULL;
        }
    }
}