#ifndef PAGE_H
#define PAGE_H

typedef struct page tPage;

tPage *CriaPagina(char*nome, double PageRank);
char*getNomePage(tPage*p);
double getPageRank(tPage * p);
#endif