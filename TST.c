#include "TST.h"

struct node
{
    Value val;
    unsigned char c;
    TST *l, *m, *r;
};

struct string
{
    char *c;
    int len;
};

TST *rec_insert(TST *t, String *key, Value val, int d)
{
    unsigned char c = key->c[d];
    if (t == NULL)
    {
        t = create_node();
        t->c = c;
    }
    if (c < t->c)
    {
        t->l = rec_insert(t->l, key, val, d);
    }
    else if (c > t->c)
    {
        t->r = rec_insert(t->r, key, val, d);
    }
    else if (d < key->len - 1)
    {
        t->m = rec_insert(t->m, key, val, d + 1);
    }
    else
    {
        t->val = val;
    }
    return t;
}

TST *rec_search(TST *t, String *key, int d)
{
    if (t == NULL)
    {
        return NULL;
    }
    unsigned char c = key->c[d];
    if (c < t->c)
    {
        return rec_search(t->l, key, d);
    }
    else if (c > t->c)
    {
        return rec_search(t->r, key, d);
    }
    else if (d < key->len - 1)
    {
        return rec_search(t->m, key, d + 1);
    }
    else
    {
        return t;
    }
}

void traverseTSTAndSearch(TST *tst1, TST *tst2)
{
    if (tst1 == NULL)
        return;

    // Verifica se a palavra atual na TST1 é uma palavra válida
    if (tst1->val != NULL)
    {
        // Cria uma struct string para armazenar a palavra atual
        struct string word;
        word.c = malloc((tst1->val->length + 1) * sizeof(char));
        strcpy(word.c, tst1->val->word);
        word.len = tst1->val->length;

        // Realiza a busca na TST2 usando a palavra
        TST *result = rec_search(tst2, &word, 0);

        // Verifica se a palavra foi encontrada na TST2
        if (result != NULL)
        {
            // Faça o que desejar com a palavra encontrada
            // ...
        }

        free(word.c);
    }

    // Recursivamente percorre as subárvores esquerda, meio e direita
    traverseTSTAndSearch(tst1->l, tst2);
    traverseTSTAndSearch(tst1->m, tst2);
    traverseTSTAndSearch(tst1->r, tst2);
}
