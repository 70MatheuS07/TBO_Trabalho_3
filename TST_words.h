#ifndef TST_WORDS_H
#define TST_WORDS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node_words TST_words;

typedef struct string String;

typedef int Value;



TST_words* CreateTST_words();
TST_words *create_node_words();

TST_words *rec_insert_words(TST_words *t, String *key,String *page, int d);

TST_words* TST_insert_words(TST_words* t, String* key , Value val) ;
TST_words *rec_search_words(TST_words *t, String *key, int d);
TST_pages* TST_search_words(TST_words* t, String* key);

#endif