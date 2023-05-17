#include <stdio.h>
#include <stdlib.h>

int main()
{
    int largura, altura;
    int i, j;
    char formato[4];
    char aux[100];
    int valor_maximo;

    // Imagem original - sufixo[1]
    FILE *arq1;
    arq1 = fopen("C:/Users/alunos/Desktop/Aula-PDI/lenna.ppm", "r");
    if (arq1 == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    fscanf(arq1, "%[^\n]\n", formato);
    fscanf(arq1, "%[^\n]\n", aux);
    fscanf(arq1, "%d %d\n", &largura, &altura);
    fscanf(arq1, "%d\n", &valor_maximo);

    printf("L1: %d A1: %d\n\n", largura, altura);

    // Alocar mem�ria para a imagem
    int ***imagem = malloc(altura * sizeof(int **));
    for (i = 0; i < altura; i++)
    {
        imagem[i] = malloc(largura * sizeof(int *));
        for (j = 0; j < largura; j++)
        {
            imagem[i][j] = malloc(3 * sizeof(int));
        }
    }

    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int pixel_valor;
                fscanf(arq1, "%d\n", &pixel_valor);
                imagem[i][j][k] = pixel_valor;
            }
        }
    }

    fclose(arq1);

    // Trocar a ordem das componentes de cor RGB para GBR ou BRG
    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            int temp = imagem[i][j][0];  // Armazena o valor R temporariamente
            imagem[i][j][0] = imagem[i][j][1];  // Move o valor G para a posi��o R
            imagem[i][j][1] = imagem[i][j][2];  // Move o valor B para a posi��o G
            imagem[i][j][2] = temp;  // Move o valor tempor�rio (R) para a posi��o B
        }
    }

    // Salvar a imagem resultante em um novo arquivo
    FILE *arq2;
    arq2 = fopen("C:/Users/alunos/Desktop/Aula-PDI/lenna_misturada.ppm", "w");
    fprintf(arq2, "%s\n", formato);
    fprintf(arq2, "%d %d\n", largura, altura);
    fprintf(arq2, "%d\n", valor_maximo);
    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(arq2, "%d\n", imagem[i][j][k]);
            }
        }
    }

    // Liberar a mem�ria alocada
    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            free(imagem[i][j]);
        }
        free(imagem[i]);
    }
    free(imagem);

    fclose(arq2);

    return 0;
}

