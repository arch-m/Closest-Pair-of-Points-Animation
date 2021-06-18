#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int x, y;
}Point;

void getNumbers(int size, int *numbers);
void setPoints(int size, int *arrayNumbers, Point *points);
void writeFile(int size, int *arrayNumbers, int combinations);
int combination(int **table, int n, int k);
void bruteForce(Point *P, int size, int combinations, float *temp);

void writeFile(int size, int *arrayNumbers, int combinations)
{
    FILE *filePtr;
    char path [] = "Files/";
    char fileName [26];
    char numberOfPoints[3];

    sprintf(numberOfPoints, "%d", size);
    strcat(fileName, numberOfPoints);
    strcat(fileName, "-generate.json");
    strcat(path, fileName);

    filePtr = fopen(path, "w");
    
    if(filePtr == NULL)
    {
        printf("No se ha podido crear el archivo.\n");
        exit(EXIT_FAILURE);
    }

    /*
        Para imprimir encabezado
    */
    fputs("{\n", filePtr);
    /*
        Parte para imprimir los números
    */
    fputs("\t\"points\": [", filePtr);
    
    getNumbers(size, arrayNumbers);
    //setPoints(size, arrayNumbers, points);
    
    for(int i = 0, count  = 0; i < 2 * size; )
    {
        fprintf(filePtr, "\"%d,%d\",", arrayNumbers[i], arrayNumbers[i+1]);
        count++;
        i+=2;
     
        if(count + 1  == size)
        {
            fprintf(filePtr, "\"%d,%d\"],", arrayNumbers[i], arrayNumbers[i+1]);
            break;
        }
    }

    fputs("\n\t\"relations\": [\n", filePtr);
    //fputs("\t\t{\n", filePtr);
    printf("combination F: %d\n", combinations);
    for(int i = 1, count = 0, j = 1, n = 1, k = 1; n < combinations;n++, j++)
    {
        
        printf("i: %d, count: %d\n", i, count);
        if(size - k == 1)    
        {
            fputs("\t\t{\n", filePtr);
            fprintf(filePtr, "\t\t\t\"p_1\": \"%d,%d\",\n", arrayNumbers[count], arrayNumbers[count+1]);  
            fprintf(filePtr, "\t\t\t\"p_2\": \"%d,%d\"\n", arrayNumbers[count + i + 1], arrayNumbers[count + i + 2]);  
            fputs("\t\t}\n", filePtr);
            break;
            
        } 
        else 
        {
            fputs("\t\t{\n", filePtr);
        fprintf(filePtr, "\t\t\t\"p_1\": \"%d,%d\",\n", arrayNumbers[count], arrayNumbers[count+1]);  
        fprintf(filePtr, "\t\t\t\"p_2\": \"%d,%d\"\n", arrayNumbers[count + i + 1], arrayNumbers[count + i + 2]);  
        fputs("\t\t},\n", filePtr);
        } 
        
        
       
        printf("i: %d, j: %d, condition: %d\n", i, j, size - k);
        if(j == size - k && size - k >1)  
        {
            j=1;
            k++;
            //i = 1;
            count+=2;
            i = 1;
        }
        else 
             i+=2;            
    }

    /*
        Formato constante
    */
    fputs("\t]\n", filePtr);
    fputs("}", filePtr);

    fclose(filePtr);

    printf("\nSe ha creado el archivo con %d numeros\n", size);

}

void getNumbers(int size, int *numbers)
{
    FILE *myFile;
    myFile = fopen("files/numbers.txt", "rt");
    int number, cont = 0;

    if(myFile == NULL)
    {
        perror("Error al intentar leer el archivo");
    }
    
    else
    {
        while( fscanf(myFile, "%d   \n", &number) > 0 && cont < 2* size) 
        {
            numbers[cont] = number;
            cont++;
        }        
    }
}

/*
    Sous la forme (nCk)
    DP -> Top botom
*/
int combination(int **table, int n, int k)
{
    if(table[n][k] != -1)
        return table[n][k];
    if(k==0 || k==n)
    {
        table[n][k] = 1;
        return table[n][k];
    }
    else if(k>0 && k<n)
    {
        if(table[n-1][k-1] == -1)   
            table[n-1][k-1] = combination(table, n-1, k-1);
        if(table[n-1][k] == -1)
            table[n-1][k] = combination(table, n-1, k);

        table[n][k] = table[n-1][k-1] + table[n-1][k];
        return table[n][k];
    }
    else    
    {
        table[n][k] = 0;
        return table[n][k];
    }
}

int main(void)
{
    int size = 10;
    int *array = malloc(2 * size * sizeof(int));

   /*
        To calculate possible combinations between points
    */
    int k = 2;
    int **M;
    M = malloc((size+1) * sizeof(int *));
    for(int i = 0; i < size+1; i++)
        M[i] = malloc((k+1) * sizeof(int));

    for(int i = 0; i <= size; i++)
        for(int j = 0; j <= k; j++)
            M[i][j] = -1;
    int combinations = combination(M, size, k);
    printf("main combinations: %d\n", combinations);

   /*
    Next part
   */
    writeFile(size , array, combinations);
    free(array);
    free(M);
    return 0;
}