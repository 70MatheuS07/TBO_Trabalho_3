#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page.h"
struct page{
    char *nome;
    double PageRank;
};


tPage *CriaPagina(char*nome, double PageRank){
    tPage* page =malloc (sizeof (tPage));
    page->nome = strdup(nome);
    page->PageRank = PageRank;
    return page;
}

char*getNomePage(tPage*p){
    return p->nome;
}

double getPageRank(tPage * p){
    return p->PageRank;
}