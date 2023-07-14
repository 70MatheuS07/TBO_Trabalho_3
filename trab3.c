#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TST_pages.h"
#include "TST_words.h"
#include "Arquivo.h"
#include "MaqBusca.h"
#include "page.h"
int main(int argc, char *argv[])
{

    int qtdlinhas = 0;
    qtdlinhas = ContaLinhasArquivoBuffer("index.txt") + 1;
    tPage **result = calloc(qtdlinhas, sizeof(tPage *));

    FILE *Graph_file = fopen("graph.txt", "r");
    tPage **grafo = calloc(qtdlinhas, sizeof(tPage *));
    MontaGrafo(grafo, Graph_file, qtdlinhas);
    CalculaPageRanks(grafo, qtdlinhas);

    TST_words *StopWords = CreateTST_words();
    FILE *Stop_file = fopen("stopwords.txt", "r");

    StopWords = MontaTST_StopWords(StopWords, Stop_file);

    fclose(Stop_file);

    FILE *index_file = fopen("index.txt", "r");
    TST_words *Terms = CreateTST_words();

    Terms = MontaTST_Terms(Terms, index_file, StopWords);
    char palavra_search[1000];
    char lixo;
    int cont = 0;
    TST_pages *IntercPages, *ant;
    char*linha, *linhaPesquisa;
    while (1){
    linha=ler_linha(stdin);

    if(linha==NULL){
        break;
    }
    int tamlinha=strlen(linha);
    linhaPesquisa=calloc(tamlinha+1, sizeof(char));
    strcpy(linhaPesquisa, linha);
    char *token = strtok(linha, " ");
        while (token!=NULL)
        {
            if (cont == 0)
            {
                ant = TST_search_words(Terms, token);
                IntercPages = ant;
                cont++;
            }
            else
            {
                ant = TST_search_words(Terms, token);
                IntercPages = TST_intersection(ant, IntercPages);
            }
            token = strtok(NULL, " ");
        }
    cont=0;
    int contPalavras = 0;
    result = getTSTWords(IntercPages, &contPalavras, qtdlinhas, result);
    OrdenaEImprimeSaida(grafo,result, qtdlinhas, linhaPesquisa);
    free(linha);
    free(linhaPesquisa);
    for(int i=0;result[i]!=NULL;i++){
        free(result[i]);
        result[i]=NULL;
    }
    }

    return 0;
}

/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    char character;
    bool isEndOfWord;
    struct Node* left;
    struct Node* mid;
    struct Node* right;
};

struct Node* newNode(char character) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->character = character;
    node->isEndOfWord = false;
    node->left = NULL;
    node->mid = NULL;
    node->right = NULL;
    return node;
}

void insert(struct Node** root, char* word) {
    if (*root == NULL) {
        *root = newNode(*word);
    }

    if (*word < (*root)->character) {
        insert(&((*root)->left), word);
    } else if (*word > (*root)->character) {
        insert(&((*root)->right), word);
    } else {
        if (*(word + 1)) {
            insert(&((*root)->mid), word + 1);
        } else {
            (*root)->isEndOfWord = true;
        }
    }
}

bool search(struct Node* root, char* word) {
    if (root == NULL) {
        return false;
    }

    if (*word < root->character) {
        return search(root->left, word);
    } else if (*word > root->character) {
        return search(root->right, word);
    } else {
        if (*(word + 1) == '\0') {
            return root->isEndOfWord;
        }
        return search(root->mid, word + 1);
    }
}

void traverseTSTUtil(struct Node* root, char* buffer, int depth) {
    if (root) {
        traverseTSTUtil(root->left, buffer, depth);

        buffer[depth] = root->character;
        if (root->isEndOfWord) {
            buffer[depth + 1] = '\0';
            printf("%s\n", buffer);
        }

        traverseTSTUtil(root->mid, buffer, depth + 1);

        traverseTSTUtil(root->right, buffer, depth);
    }
}

void traverseTST(struct Node* root) {
    char buffer[100];
    traverseTSTUtil(root, buffer, 0);
}

void compareTSTs(struct Node* root1, struct Node* root2) {
    if (root1 == NULL) {
        return;
    }

    compareTSTs(root1->left, root2);

    char buffer[100];
    traverseTSTUtil(root1->mid, buffer, 0);
    bool foundInTST2 = search(root2, buffer);
    printf("Word: %s, Found in TST2: %s\n", buffer, foundInTST2 ? "Yes" : "No");

    compareTSTs(root1->mid, root2);
    compareTSTs(root1->right, root2);
}

int main() {
    struct Node* root1 = NULL;
    insert(&root1, "car");
    insert(&root1, "cat");
    insert(&root1, "cart");
    insert(&root1, "dog");
    insert(&root1, "dogs");

    struct Node* root2 = NULL;
    insert(&root2, "cat");
    insert(&root2, "dog");
    insert(&root2, "elephant");

    compareTSTs(root1, root2);

    return 0;
}
*/