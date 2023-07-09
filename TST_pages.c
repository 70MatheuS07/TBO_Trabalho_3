#include "TST_pages.h"

struct node_pages
{
    Value val;
    unsigned char c;
    TST_pages *l, *m, *r;
};


TST_pages *CreateTST_pages()
{
    return NULL;
}

TST_pages *create_node_pages()
{
    TST_pages *newNode = malloc(sizeof(TST_pages));
    newNode->val = 0;
    newNode->l = NULL;
    newNode->m = NULL;
    newNode->r = NULL;
    return newNode;
}

TST_pages *rec_insert_pages(TST_pages *t, char *key, Value val, int d)
{
    unsigned char c = key[d];
    if (t == NULL)
    {
        t = create_node_pages();
        t->c = c;
    }
    if (c < t->c)
    {
        t->l = rec_insert_pages(t->l, key, val, d);
    }
    else if (c > t->c)
    {
        t->r = rec_insert_pages(t->r, key, val, d);
    }
    else if (d < strlen(key) - 1)
    {
        t->m = rec_insert_pages(t->m, key, val, d + 1);
    }
    else
    {
        t->val = val;
    }
    return t;
}
TST_pages *TST_insert_pages(TST_pages *t, char *key, Value val)
{
    return rec_insert_pages(t, key, val, 0);
}

TST_pages *rec_search_pages(TST_pages *t, char *key, int d)
{
    if (t == NULL)
    {
        return NULL;
    }
    unsigned char c = key[d];
    if (c < t->c)
    {
        return rec_search_pages(t->l, key, d);
    }
    else if (c > t->c)
    {
        return rec_search_pages(t->r, key, d);
    }
    else if (d < strlen(key) - 1)
    {
        return rec_search_pages(t->m, key, d + 1);
    }
    else
    {
        return t;
    }
}

Value TST_search(TST_pages *t, char *key)
{
    t = rec_search_pages(t, key, 0);
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        return t->val;
    }
}

TST_pages *TST_intersection(TST_pages *t1, TST_pages *t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL; // Se alguma das TSTs for nula, retorna uma TST vazia
    }

    TST_pages *result = CreateTST_pages(); // Cria uma nova TST para armazenar a interseção

    // Percorre as TSTs simultaneamente
    if (t1->c < t2->c) {
        // Se o caractere atual em t1 é menor que o caractere atual em t2,
        // busca a interseção nas subárvores à esquerda
        result = TST_intersection(t1->l, t2);
    } else if (t1->c > t2->c) {
        // Se o caractere atual em t1 é maior que o caractere atual em t2,
        // busca a interseção nas subárvores à direita
        result = TST_intersection(t1, t2->r);
    } else {
        // Se os caracteres atuais em t1 e t2 são iguais,
        // adiciona o caractere à TST resultante e busca a interseção nas subárvores do meio
        result = create_node_pages();
        result->c = t1->c;
        result->m = TST_intersection(t1->m, t2->m);
    }

    return result;
}

void collectStrings(TST_pages *t, char *prefix, char **strings, int index)
{
    if (t == NULL) {
        return;
    }

    collectStrings(t->l, prefix, strings, index);

    prefix[index] = t->c;
    prefix[index + 1] = '\0'; // Adiciona o caractere nulo para indicar o fim da string
    strings[index] = strdup(prefix);

    collectStrings(t->m, prefix, strings, index + 1);
    collectStrings(t->r, prefix, strings, index);

    prefix[index] = '\0';
}