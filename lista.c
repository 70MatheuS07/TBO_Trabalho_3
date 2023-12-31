#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct celula
{
    int pos;
    tCelula *prox;
};

struct lista
{
    tCelula *ini;
    tCelula *fim;
};

tLista *CriaLista()
{
    tLista *lista = malloc(sizeof(tLista));
    lista->ini = NULL;
    lista->fim = NULL;
    return lista;
}

void InsereNaLista(int pos, tLista *lista)
{
    tCelula *nova = malloc(sizeof(tCelula));
    nova->prox = NULL;
    nova->pos = pos;
    if (lista->ini == NULL)
    {
        lista->ini = nova;
        lista->fim = nova;
        lista->fim->prox = NULL;
    }
    else
    {
        lista->fim->prox = nova;
        lista->fim = nova;
        lista->fim->prox = NULL;
    }
}

tCelula *RetornaProx(tCelula *p)
{
    return p->prox;
}
tCelula *RetornaPrimeiro(tLista *lista)
{
    return lista->ini;
}
void LiberaLista(tLista *lista)
{
    tCelula *atual = lista->ini;
    while (atual != NULL)
    {
        tCelula *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(lista);
}

int getpos(tCelula *celula)
{
    return celula->pos;
}