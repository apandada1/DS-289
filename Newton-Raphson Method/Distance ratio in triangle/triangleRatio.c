#include "triangleRatio.h"
#include "jacobian.h"
#include <cblas.h>
#include <math.h>
#include <stdio.h>
#include "NewtonRaphson.h"

typedef struct _TRIANGLE {
	double xA;
	double xB;
	double xC;
	double yA;
	double yB;
	double yC;
	double ratA;
	double ratB;
	double ratC;
} TRIANGLE;

void fn(double *x, int m, void *ud, double *s_out)
{
	TRIANGLE *triangle;
	triangle = (TRIANGLE *)ud;
	s_out[0] = (triangle->ratB * findDistance(triangle->xA,x[0],triangle->yA,x[1])) - (triangle->ratA * findDistance(triangle->xB,x[0],triangle->yB,x[1])); //b*AP - a*BP = 0
	s_out[1] = (triangle->ratC * findDistance(triangle->xA,x[0],triangle->yA,x[1])) - (triangle->ratA * findDistance(triangle->xC,x[0],triangle->yC,x[1])); //c*AP - a*CP = 0
}

double findDistance(double xA, double xB, double yA, double yB)
{
	return hypot((xA - xB),(yA - yB));
}

void triangleRatio(double xA, double xB, double xC, double yA, double yB, double yC, double ratA, double ratB, double ratC)
{
	double x[2];
	x[0] = (xA + xB + xC)/3;//initial guess
	x[1] = (yA + yB + yC)/3;
	printf("x.init = %lf  y.init = %lf\n", x[0], x[1]);
	int n = 2, iter = 100;
	double ws[4];

	double h = 1e-8;

	TRIANGLE tri;
	tri.xA = xA;
	tri.xB = xB;
	tri.xC = xC;
	tri.yA = yA;
	tri.yB = yB;
	tri.yC = yC;
	tri.ratA = ratA;
	tri.ratB = ratB;
	tri.ratC = ratC;

	NewtonRaphson(x,fn,h,n,ws,iter,&tri);

	printf("A(%lf,%lf)\t", tri.xA, tri.yA);
	printf("B(%lf,%lf)\t", tri.xB, tri.yB);
	printf("C(%lf,%lf)\n\n", tri.xC, tri.yC);

	printf("solution point P(%lf,%lf)\n",x[0],x[1]);

	double AP = findDistance(xA,x[0],yA,x[1]), BP = findDistance(xB,x[0],yB,x[1]), CP = findDistance(xC,x[0],yC,x[1]);
	printf("AP = %lf, BP = %lf, CP = %lf\n", AP, BP, CP);
	printf("AP/ratA = %lf, BP/ratB = %lf, CP/ratC = %lf\n", (AP/ratA), (BP/ratB), (CP/ratC));

}