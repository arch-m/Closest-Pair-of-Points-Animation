#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ClosestPair.h"

/*
    Instrucción de compilación: gcc ClosestPairMerge.c -o ClosestPair -lm
*/

/*
    struct X {
        int a;
        int b;
    }
    struct X foo = { 0, 1 }; // a = 0, b = 1

*/

int main()
{
    float distance = 0;
    Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);
	Point result[2] = { 0,0 };
    distance = getClosest(P, result, n);
    printf("The smallest distance is %f \n", distance);
    return 0;
}

/*
    Cálculo de la distancia entre dos puntos. La llamada "Distancia Euclidianas"
*/
float Distance(Point point1, Point point2)
{                                                                                                                                                                                                                                           
	float distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	return distance;
}

/*
    Merge Sort recursivo
*/
void mergeSort(Point points[], int s, int e,char z)
{
	if (s < e)
	{
		int mid = (s + e) / 2;
		mergeSort(points, s, mid, z);
		mergeSort(points, mid + 1, e, z);
		merge(points, s, e, mid, z);
		return;
	}
}

/*
    Algoritmo de mezcla
    Contempla las dos mezclas necesarias, según sea alguno de los
    casos siguientes:
        ->  Ordena de acuerdo a la coordenada 'x', para la búsqueda
            dentro de las mitades izquierda y derecha de la menor
            distancia euclidiana entre puntos

        ->  Ordena de acuerdo a la coordenada 'y', para la búsqueda
            dentro de los puntos comprendidos dentro de la "franja"
    
    Se distingue entre ambos ordenamientos con base en el 5to 
    parámetro de entrada 
*/
void merge(Point points[], int left, int right, int middle, char coord)// s -> left ||  e -> right || mid -> middle || z -> 
{
	int lengthLeft = middle - left + 1;
	int lengthRight = right - middle;
	int i = 0, j = 0, k = left;

	Point *AL = (Point*)malloc(sizeof(Point)*lengthRight);
	Point *AR = (Point*)malloc(sizeof(Point)*lengthLeft);

	for (i = left; i <= middle; i++)
	{
		AL[i - left] = points[i];
	}

	for (j = middle + 1; j <= right; j++)
	{
		AR[j - middle - 1] = points[j];
	}

	switch (coord)
	{
	    case 'x':
		    i = 0; j = 0;
		    while (i < lengthLeft && j < lengthRight)
		    {
			    if (AL[i].x < AR[j].x)
			    {
	    			points[k++] = AL[i++];
    			}
		    	else 
                    points[k++] = AR[j++];
		    }
		    
            while (i < lengthLeft)
		    {
			    points[k++] = AL[i++];
		    }
		    while (j < lengthRight)
		    {
			    points[k++] = AR[j++];
		    }
		    break;

	    case 'y':
		    i = 0; j = 0;
    		while (i < lengthLeft &&j < lengthRight)
	    	{
		    	if (AL[i].y < AR[j].y)
			    {
				    points[k++] = AL[i++];
			    }
			    else
                    points[k++] = AR[j++];
		    }
		    while (i < lengthLeft)
		    {
			    points[k++] = AL[i++];
		    }
		    while (j < lengthRight)
		    {
			    points[k++] = AR[j++];
		    }
		    break;
	    default:
		    free(AL);
		    free(AR);
		    break;
	}
	return;
}

/*
    Con base en el punto medio calculado y el tamaño del arreglo de puntos,
    se parte por mitad el arreglo de puntos y se generan los arreglos de
    puntos para la mitad derecha e izquierda
*/
void divideByMid(int mid, Point points[], Point pointsL[], Point pointsR[], int n)
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (points[i].x > mid) 
		{
			pointsR[j++] = points[i];
		}
		else 
        {
			pointsL[k++] = points[i];
		}
	}
	return;
}

 /*
    Se calcula la distancia de los puntos que están incluidos dentro de 
    las mitades obtenidas de la función divideByMid. Es decir, se utiliza
    para la primera división que se realiza del arreglo original de 
    puntos. Se retornará entonces la distancia mínima obtenida al interior
    de ambas mitades
*/
float getClosestInSides(Point points[], int pointsLength)
{
	float distance;
	if (pointsLength < 2)
	{
		distance = FLT_MAX;
	}
	else if (pointsLength == 2)
	{
		distance = Distance(points[0], points[1]);
	}
	else
	{
		Point *pointsL = (Point*)malloc(sizeof(Point)*(pointsLength));
		Point *pointsR = (Point*)malloc(sizeof(Point)*(pointsLength));
		for (int i = 0; i < pointsLength; i++)
		{
			if (i < pointsLength / 2)
			{
				pointsL[i].x = 0;
				pointsL[i].y = 0;
			}
			else
			{
				pointsR[i - pointsLength / 2].x = 0;
				pointsR[i - pointsLength / 2].y = 0;
			}
		}

		mergeSort(points, 0, pointsLength - 1, 'x');
		divideByMid(points[pointsLength/2].x, points, pointsL, pointsR, pointsLength);

		float distance_L = getClosestInSides(pointsL, pointsLength / 2);
		float distance_R = getClosestInSides(pointsR, pointsLength - pointsLength / 2);

		if (distance_L > distance_R)
		{
			distance = distance_L;
		}
		else 
            distance = distance_R;

		free(pointsR);
		free(pointsL);
	}
	return distance;
}

/*
    Se calcula la distancia de los puntos comprendidos en la franja, es decir,
    de cálcula la distancia mínima que puede encontrarse en las mitades, con
    ayuda de la función getClosestInSides(). Se ordenan los puntos del 
    arreglo con base en la coordenada 'y'. Finalmente, según los puntos que
    puedan encontrarse en la franja, se calculan las distancias (únicamente)
    7 elementos (como se observa en la línea 244)
*/
float getClosest(Point points[], Point result[2], int pointsLength)
{
	float distance = getClosestInSides(points, pointsLength);
	int pointsCenterLength = -1;

	mergeSort(points, 0, pointsLength - 1, 'y');
	Point * pointsCenter = (Point *)malloc(sizeof(Point)*pointsLength);

	for (int i = 0; i < pointsLength; i++)
	{
		if (fabs(points[i].x - points[pointsLength/2].x) < distance)
		{
			pointsCenter[++pointsCenterLength] = points[i];
		}
	}
	for (int i = 0; i < pointsCenterLength; i++)
	{
		for (int j = i + 1; j <= i + 7 && j < pointsCenterLength; j++)
		{
			if (Distance(pointsCenter[i], pointsCenter[j]) < distance)
			{
				distance = Distance(pointsCenter[i], pointsCenter[j]);
				result[0] = pointsCenter[i];
				result[1] = pointsCenter[j];
			}
		}
	}
	free(pointsCenter);
	return distance;
}
