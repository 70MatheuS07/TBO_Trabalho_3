#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *file_a = fopen("a.txt", "r");
    FILE *file_b = fopen("b.txt", "r");
    FILE *file_c = fopen("c.txt", "w");

    char *string = calloc(1000, sizeof(char));
    char *a_1 = calloc(1000, sizeof(char));
    char *a_2 = calloc(1000, sizeof(char));
    char *b_1 = calloc(1000, sizeof(char));
    char *b_2 = calloc(1000, sizeof(char));

    while (fscanf(file_a, "%s %s\n", a_1, a_2) != EOF)
    {
        fscanf(file_b, "%s %s\n", b_1, b_2);

        if (strcmp(a_1, b_1) != 0)
        {
            // imprime invertido
            fprintf(file_c, "%s %s\n", a_2, a_1);
        }
        else
        {
            fprintf(file_c, "%s %s\n", a_1, a_2);
        }
    }

    fclose(file_a);
    fclose(file_b);
    fclose(file_c);

    return 0;
}