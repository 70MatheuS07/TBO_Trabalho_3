#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"
#define MINIMUM_SIZE 32

char *ler_linha(FILE *fp)
{
    int tam = MINIMUM_SIZE;
    int qtd;
    char *linha = calloc(MINIMUM_SIZE, sizeof(*linha));
    char *linhartn = calloc(MINIMUM_SIZE, sizeof(*linhartn));
    while (1)
    {
        if (feof(fp))
        {
            break;
        }
        fgets(linha, MINIMUM_SIZE, fp);
        linhartn = strcat(linhartn, linha);
        qtd = strlen(linhartn) - 1;
        if (linhartn[qtd] == '\n')
        {
            linhartn[qtd] = '\0';
            free(linha);
            return linhartn;
        }
        if (feof(fp))
        {
            free(linha);
            return linhartn;
        }
        tam = tam +50;
        linhartn = realloc(linhartn, tam);
    }
    free(linha);
    free(linhartn);
    return NULL;
}

int ContaLinhasArquivoBuffer(char *arq_entrada)
{
  FILE *f;
  char buffer[BLOCK_SIZE];
  int i = 0;

  f = fopen(arq_entrada, "r");

  while (fgets(buffer, BLOCK_SIZE, f) != NULL)
  {
    char *pos = strchr(buffer, '\n');
    while (pos != NULL)
    {
      i++;
      pos = strchr(pos + 1, '\n');
    }
  }

  fclose(f);
  return i;
}