#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Instrucción de compilación -> gcc bruteForce.c -o bruteForce -lm
*/

typedef struct 
{
    int x, y;
}Point;

float distance(Point P1, Point P2)
{
    return sqrt(
                    (P1.x - P2.x) * (P1.x - P2.x) + 
                    (P1.y - P2.y) * (P1.y - P2.y) 
                );
}

float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for(int i = 0; i < n; ++i)
        for(int j = i+1; j < n; ++j)
            if(distance(P[i], P[j]) < min)
                min = distance(P[i], P[j]);
    return min;
}

int main(int argc, char* argv[])
{
    Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);
    printf("The smallest distance is %f \n", bruteForce(P, n));
    return 0;
}