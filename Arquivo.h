#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdlib.h>
#include <stdio.h>
#define BLOCK_SIZE 4096 // Tamanho do bloco em bytes
char *ler_linha(FILE *fp);
int ContaLinhasArquivoBuffer(char *arq_entrada);
#endif
