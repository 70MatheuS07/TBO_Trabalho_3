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
    TST_pages *newNode = malloc(1 * sizeof(TST_pages));
    newNode->val = 0;
    newNode->c='\0';
    newNode->l = NULL;
    newNode->m = NULL;
    newNode->r = NULL;
    return newNode;
}

/**
 * @brief 
 * 
 * @param t 
 * @param key 
 * @param val 
 * @param d 
 * @return TST_pages* 
 */
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

Value TST_search_pages(TST_pages *t, char *key)
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

TST_pages *TST_intersect_pages(TST_pages *t1, TST_pages *t2, TST_pages *t3, char *prefix, int d)
{
    if (t1 == NULL)
        return t3; // Se a primeira árvore é vazia, retorna a terceira árvore

    t3 = TST_intersect_pages(t1->l, t2, t3, prefix, d); // Percorre a subárvore esquerda

    prefix[d] = t1->c; // Adiciona o caractere do nó atual ao prefixo
    if (t1->val == 1)  // Se o nó atual tem valor 1, significa que é o final de uma string
    {
        prefix[d + 1] = '\0';                  // Termina a string com um caractere nulo
        if (TST_search_pages(t2, prefix) == 1) // Verifica se a string também está na segunda árvore com valor 1
        {
            t3 = TST_insert_pages(t3, prefix, 1); // Insere a string na terceira árvore com valor 1
        }
    }
    t3 = TST_intersect_pages(t1->m, t2, t3, prefix, d + 1); // Percorre a subárvore do meio
    t3 = TST_intersect_pages(t1->r, t2, t3, prefix, d);     // Percorre a subárvore direita
    return t3;                                              // Retorna a terceira árvore
}

// Função que cria um buffer para armazenar o prefixo e chama a função recursiva
TST_pages *TST_intersection(TST_pages *t1, TST_pages *t2)
{
    char *buffer = calloc(500, sizeof(char));

    // Cria um buffer para armazenar o prefixo das strings
    TST_pages *result = TST_intersect_pages(t1, t2, NULL, buffer, 0); // Chama a função recursiva com uma terceira árvore vazia

    free(buffer);
    return result;
}

void collectWords(TST_pages *t, char *buffer, int depth, tPage **words, int *count, int tam)
{
    if (t == NULL)
    {
        return;
    }

    // Percorre as subárvores esquerda, meio e direita
    collectWords(t->l, buffer, depth, words, count, tam);

    // Armazena o caractere atual no buffer
    buffer[depth] = t->c;

    // Se chegou ao final da palavra (nó com valor não nulo), adiciona a palavra ao vetor
    if (t->val != 0)
    {
        buffer[depth + 1] = '\0';                         // Adiciona o terminador nulo
        words[*count] = CriaPagina(buffer, 0.0, 0, NULL); // Copia a palavra para o vetor
        (*count)++;
    }

    // Percorre a subárvore do meio
    collectWords(t->m, buffer, depth + 1, words, count, tam);

    // Percorre a subárvore direita
    collectWords(t->r, buffer, depth, words, count, tam);
}

// Função principal para obter as palavras presentes na TST em um vetor
tPage **getTSTWords(TST_pages *t, int *wordCount, int tam, tPage **words)
{

    int count = 0;
    char *buffer = calloc(1000, sizeof(char));
    collectWords(t, buffer, 0, words, &count, tam);
    free(buffer);
    *wordCount = count; // Atualiza o número de palavras
    return words;
}

TST_pages *liberaTST_Pages(TST_pages *tst_page)
{
    if (tst_page != NULL)
    {
        liberaTST_Pages(tst_page->l);
        liberaTST_Pages(tst_page->m);
        liberaTST_Pages(tst_page->r);

        free(tst_page);
    }

    return NULL;
}