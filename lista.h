#ifndef LISTA_H
#define LISTA_H


typedef struct celula tCelula;
typedef struct lista tLista;


tLista* CriaLista();

void InsereNaLista(int pos, tLista*lista);
void LiberaLista(tLista *lista);
tCelula* RetornaProx(tCelula*p);
tCelula* RetornaPrimeiro(tLista *lista);
int getpos(tCelula*celula);

#endif