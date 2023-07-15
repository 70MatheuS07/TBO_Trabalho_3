#ifndef PAGE_H
#define PAGE_H
#include "lista.h"
typedef struct page tPage;

tPage *CriaPagina(char *nome, double PageRank, int qtd, tLista *lista);
char *getNomePage(tPage *p);
double getPageRank(tPage *p);
tLista *getLista(tPage *p);
int getQtd(tPage *p);
void setPageRank(double pagerank, tPage *page);
void liberaMatrizPage(tPage **page, int qtd);
void limpaPageResult(tPage **result, int qtd);

#endif