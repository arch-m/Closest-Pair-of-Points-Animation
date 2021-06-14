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
void writeFile(int size, int *arrayNumbers, Point *points, float *relations, int combinations);
int combination(int **table, int n, int k);
void bruteForce(Point *P, int size, int combinations, float *temp);



void writeFile(int size, int *arrayNumbers, Point *points, float *relations, int combinations)
{
    FILE *filePtr;
    char path [] = "Files/";
    char fileName [20];
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
    fputs("\t\"Points:\" [", filePtr);
    
    getNumbers(size, arrayNumbers);
    setPoints(size, arrayNumbers, points);
    
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

    /*
        Se obtienen relaciones
    */
    bruteForce(points, size, combinations, relations);
    for(int i = 0; i < combinations; i++)
       printf("Relations: %f\n", relations[i]);
    /*
        Parte para imprimir las relaciones
    */
    fputs("\n\t\"Relations:\" [\n", filePtr);
    fputs("\t\t{\n", filePtr);
    //printf("p_1: ");
    fputs("\t\t\t\"P_1\": \"", filePtr);
    for(int i = 0, j = size - 1, count  = 0, n=2; i < combinations; i++, count++)
    {
        
        if(j == count)
        {
            //printf("\n");
            //printf("p_%d: ", n);
            
            fputs("\n", filePtr);
            fprintf(filePtr, "\t\t\t\"P_%d\": \"", n);
            j--;
            n++;
            count = 0;
        }  
        if(count ==  j - 1)
        {
            fprintf(filePtr, "%0.3f\" ,", relations[i]);
            //count;
        }
        else
        {
            fprintf(filePtr, "%0.3f,", relations[i]);
        }
        

        
        //printf("%f, ",relations[i]);

    }
    //fputs("\t\t\t\"p_1\",\n", filePtr);
    //fputs("\t\t\t\"p_2\",\n", filePtr);

    /*
        Formato constante
    */
    fputs("\n\t\t}\n", filePtr);
    fputs("\t]\n", filePtr);
    fputs("}", filePtr);

    //free(arrayOfNumbers);
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

void setPoints(int size, int *arrayNumbers, Point *points)
{
    for(int i = 0, count  = 0; i < 2 * size; count++)
    {
        points[count].x = arrayNumbers[i];
        points[count].y = arrayNumbers[i+1];
        //printf("Array points. x: %d, y:%d\n", arrayNumbers[i], arrayNumbers[i+1]);
        printf("Points. x: %d, y:%d\n", points[count].x, points[count].y);
        //count++;
        i+=2;
        //printf("i: %d\n", i);
     
        if(count + 1  == size) break;
    }
}

float distance(Point P1, Point P2)
{
    return sqrt(
                    (P1.x - P2.x) * (P1.x - P2.x) + 
                    (P1.y - P2.y) * (P1.y - P2.y) 
                );
}

void bruteForce(Point *P, int size, int combinations, float *temp)
{

    for(int i = 0, count = 0; i < combinations; i++)
        for(int j = i+1; j < size; j++, count++) 
            temp[count] = distance(P[i], P[j]);

    /*
    for(int m = 0; m < combinations; m++)
            printf("temp: %f\n", temp[m]);

    */
            //if(distance(P[i], P[j]) < min)
               // min = distance(P[i], P[j]);
    //return temp;
    //free(M);
    //free(temp);
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
    Point *points = malloc(size * sizeof(Point));

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
    float *temp = malloc(combinations * sizeof(float));
   /*
    Next part
   */
    writeFile(size , array, points, temp, combinations);
    free(array);
    free(points);
    free(M);
    free(temp);
    return 0;
}