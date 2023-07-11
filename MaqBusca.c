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
    FILE *pages;
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
        pages = fopen(Pagesindex, "r");
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
    fclose(pages);
    return Terms;
}

TST_words*MontaTST_graph(TST_words*Graph, FILE*graph_file){
    char *linha;
    char*arq_Origem;
    int qtd;
    while(1){
        linha=ler_linha(graph_file);
        if(linha==NULL){
            break;
        }
        char *token = strtok(linha, " \t"); // Delimitadores: espaço e \t
            int cont=0;
            while (token != NULL)
            {  
                if(cont==0){
                    arq_Origem=token;
                }
                else if(cont==1){
                    qtd=atoi(token);
                }
                else{
                    Graph=TST_insert_words(Graph, token, arq_Origem);
                }
                cont++;
                token = strtok(NULL, " \t");
            }
    }  
                

}

void CalculaPageRanks(tPage**pages, TST_words*Graph,int qtdTodas){
    
    int tam=0;
    for(int i=0;pages[i]!=NULL;i++){
        tam++;
    }
    double *ant=calloc(tam, sizeof(double));

    for(int i=0;i<tam;i++){
        ant[i]=getPageRank(pages[i]);
    }
    double pageRank=0.0;
    while(1){
        for(int i=0;i<tam;i++){
            pageRank=0.15/qtdTodas;
            
        }
    }


}




