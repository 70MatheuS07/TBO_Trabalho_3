#ifndef TST_PAGES_H
#define TST_PAGES_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node_pages TST_pages;

typedef struct string String;

typedef int Value;



TST_pages* CreateTST_pages();
TST_pages*create_node_pages();
TST_pages *rec_insert_pages(TST_pages *t, String *key, Value val, int d);
TST_pages* TST_insert_pages(TST_pages* t, String* key , Value val) ;
TST_pages *rec_search_pages(TST_pages *t, String *key, int d);

void traverseTSTAndSearch(TST_pages *tst1, TST_pages *tst2);
#endif