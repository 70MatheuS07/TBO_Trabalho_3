#include "TST_words.h"
#include "TST_pages.h"
struct node_words
{
    Value val;
    TST_pages* pages;
    unsigned char c;
    TST_words *l, *m, *r;
};

struct string
{
    char *c;
    int len;
};

TST_words* CreateTST(){
    return NULL;
}

TST_words *create_node(){
    TST_words *new=malloc(sizeof(TST_words));
    new->r=CreateTST();
    new->l=CreateTST();
    new->m=CreateTST();
}

TST_words *rec_insert_words(TST_words *t, String *key,String *page, Value val, int d)
{
    unsigned char c = key->c[d];
    if (t == NULL)
    {
        t = create_node();
        t->c = c;
        t->pages=rec_insert_pages(t->pages, page, )
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

TST_words *rec_search_words(TST_words *t, String *key, int d)
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

void traverseTSTAndSearch(TST_words *tst1, TST_words *tst2)
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
        TST_words *result = rec_search(tst2, &word, 0);

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
