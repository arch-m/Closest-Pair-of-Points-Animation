#ifndef _CLOSESTPAIR_H_
#define _CLOSESTPAIR_H_

typedef struct Point
{
	int x;
	int y;
}Point;


void setPoints(Point points[], int pointsLength);
float Distance(Point point1, Point point2);
void sort(Point points[], int s, int e, char z);
void merge(Point points[], int s, int e, int mid, char z);
void divideByMid(int mid, Point points[], Point pointsL[], Point pointsR[], int n);
float getClosestInSides(Point points[], int pointsLength);
float getClosest(Point points[], Point result[2], int pointsLength);

#endif
