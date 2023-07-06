#ifndef TST_H
#define TST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node TST;

typedef struct string String;

typedef int Value;

TST *rec_insert(TST *t, String *key, Value val, int d);

TST *rec_search(TST *t, String *key, int d);

void traverseTSTAndSearch(TST *tst1, TST *tst2);

#endif