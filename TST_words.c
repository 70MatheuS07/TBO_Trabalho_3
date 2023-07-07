#include "TST_words.h"
#include "TST_pages.h"
struct node_words
{
    Value qtd;
    TST_pages *pages;
    unsigned char c;
    TST_words *l, *m, *r;
};

struct string
{
    char *c;
    int len;
};

TST_words *CreateTST_words()
{
    return NULL;
}

TST_words *create_node_words()
{
    TST_words *new = malloc(sizeof(TST_words));
    new->r = CreateTST_words();
    new->l = CreateTST_words();
    new->m = CreateTST_words();
    return new;
}

TST_words *rec_insert_words(TST_words *t, String *key, String *page, int d)
{
    unsigned char c = key->c[d];
    if (t == NULL)
    {
        t = create_node_words();
        t->c = c;
    }
    if (c < t->c)
    {
        t->l = rec_insert_words(t->l, key, page, d);
    }
    else if (c > t->c)
    {
        t->r = rec_insert_words(t->r, key, page, d);
    }
    else if (d < key->len - 1)
    {
        t->m = rec_insert_words(t->m, key, page, d + 1);
    }
    else
    {
        if (t->pages == NULL)
        {
            t->qtd = 0;
        }
        t->pages = TST_insert_pages(t->pages, page, 1);
        t->qtd++;
    }
    return t;
}

TST_words *TST_insert_words(TST_words *t, String *key, Value val)
{
    return rec_insert(t, key, val, 0);
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

TST_pages *TST_search_words(TST_words *t, String *key)
{
    t = rec_search(t, key, 0);
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        return t->pages;
    }
}