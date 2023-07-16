#include "TST_words.h"
#include "TST_pages.h"
struct node_words
{
    Value stp_wrd;
    TST_pages *pages;
    unsigned char c;
    TST_words *l, *m, *r;
};

TST_words *CreateTST_words()
{
    return NULL;
}

TST_words *create_node_words()
{
    TST_words *newNode = malloc(sizeof(TST_words));
    newNode->pages = CreateTST_pages(NULL);
    newNode->r = CreateTST_words();
    newNode->l = CreateTST_words();
    newNode->m = CreateTST_words();
    return newNode;
}

TST_words *rec_insert_words(TST_words *t, char *key, char *page, int d)
{
    unsigned char c = tolower(key[d]);
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
    else if (d < strlen(key) - 1)
    {
        t->m = rec_insert_words(t->m, key, page, d + 1);
    }
    else
    {
        if (page == NULL)
        {
            t->stp_wrd = 1;
        }
        if (page != NULL)
        {
            t->stp_wrd = 0;
            t->pages = TST_insert_pages(t->pages, page, 1);
        }
    }
    return t;
}

TST_words *TST_insert_words(TST_words *t, char *key, char *page)
{
    return rec_insert_words(t, key, page, 0);
}

TST_words *rec_search_words(TST_words *t, char *key, int d)
{
    if (t == NULL)
    {
        return NULL;
    }
    unsigned char c = tolower(key[d]); // Converte o caractere para minúsculo antes da comparação
    if (c < t->c)
    {
        return rec_search_words(t->l, key, d);
    }
    else if (c > t->c)
    {
        return rec_search_words(t->r, key, d);
    }
    else if (d < strlen(key) - 1)
    {
        return rec_search_words(t->m, key, d + 1);
    }
    else
    {
        if(t->pages!=NULL||t->stp_wrd==1){
            return t;
        }
        else{
            return NULL;
        }
     
    }
}

TST_pages *TST_search_words(TST_words *t, char *key)
{
    t = rec_search_words(t, key, 0);
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        return t->pages;
    }
}

Value TST_search_StopWords(TST_words *t, char *key)
{
    t = rec_search_words(t, key, 0);
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

TST_words *liberaTST_words(TST_words *root)
{
    if (root != NULL)
    {
        liberaTST_words(root->l);
        liberaTST_words(root->m);
        liberaTST_words(root->r);

        liberaTST_Pages(root->pages);
        free(root);
    }

    return NULL;
}