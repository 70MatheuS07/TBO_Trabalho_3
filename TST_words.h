#ifndef TST_WORDS_H
#define TST_WORDS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "TST_pages.h"

typedef struct node_words TST_words;

typedef int Value;

TST_words *CreateTST_words();
TST_words *create_node_words();

TST_words *rec_insert_words(TST_words *t, char *key, char *page, int d);
Value TST_search_StopWords(TST_words *t, char *key);
TST_words *TST_insert_words(TST_words *t, char *key, char *page);
TST_words *rec_search_words(TST_words *t, char *key, int d);
TST_pages *TST_search_words(TST_words *t, char *key);
void liberaTST_words(TST_words *root);

#endif