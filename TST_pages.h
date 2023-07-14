#ifndef TST_PAGES_H
#define TST_PAGES_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page.h"

typedef struct node_pages TST_pages;


typedef int Value;



TST_pages* CreateTST_pages();
TST_pages*create_node_pages();
TST_pages *rec_insert_pages(TST_pages *t, char *key, Value val, int d);
TST_pages* TST_insert_pages(TST_pages* t, char* key , Value val) ;
TST_pages *rec_search_pages(TST_pages *t, char *key, int d);
Value TST_search_pages(TST_pages *t, char *key);
TST_pages *TST_intersection(TST_pages *t1, TST_pages *t2);
TST_pages *TST_intersect_pages(TST_pages *t1, TST_pages *t2, TST_pages *t3, char *prefix, int d);
void collectWords(TST_pages *t, char *buffer, int depth, char**words, int *count, int tam);
char **getTSTWords(TST_pages *t, int *wordCount, int tam, char**words);
#endif