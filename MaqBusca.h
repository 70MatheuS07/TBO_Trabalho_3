#ifndef MAQBUSCA_H
#define MAQBUSCA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TST_pages.h"
#include "TST_words.h"
#include "Arquivo.h"


TST_words* MontaTST_StopWords(TST_words *StopWords, FILE*Stop_file);
TST_words* MontaTST_Terms(TST_words *Terms, FILE *index_file, TST_words*StopWords);

#endif