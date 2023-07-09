#include "MaqBusca.h"

TST_words* MontaTST_StopWords(TST_words *StopWords, FILE*Stop_file){
    char *stopword;
    while (1)
    {
        stopword = ler_linha(Stop_file);
        if (stopword == NULL)
        {
            break;
        }
        StopWords=TST_insert_words(StopWords, stopword, NULL);
        free(stopword);
    }
    return StopWords;
}

TST_words* MontaTST_Terms(TST_words *Terms, FILE *index_file, TST_words*StopWords){
    char *index;
    while (1)
    {
        index = ler_linha(index_file);
        if(index==NULL){
                break;
            }
        int tam = strlen(index) + 8;
        char *Pagesindex = malloc(sizeof(char)*tam);
        strcpy(Pagesindex, "pages/");

        strcat(Pagesindex, index);
        FILE *pages = fopen(Pagesindex, "r");
        while (1)
        {
            char *linha = ler_linha(pages);
            if(linha==NULL){
                break;
            }
            char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t

            while (token != NULL)
            {         
                if(!TST_search_StopWords(StopWords, token)){       
                Terms=TST_insert_words(Terms, token, index);
                }
                token = strtok(NULL, " \t");
                
            }
            free(linha);
            
        }
        free(index);
        free(Pagesindex);
    }
    return Terms;
}