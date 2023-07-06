#ifndef TST_WORDS_H
#define TST_WORDS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node_words TST_words;

typedef struct string String;

typedef int Value;

TST_words *rec_insert_words(TST_words *t, String *key,String *page, Value val, int d);

TST_words *rec_search_words(TST_words *t, String *key, int d);

void traverseTSTAndSearch(TST_words *tst1, TST_words *tst2);

#endif