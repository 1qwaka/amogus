#include <stdio.h>
#include <math.h>

#define ERR_IN 1
#define FLOAT_ERR 1e-6
#define or ||

int main(void)
{
    double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0;
    short rc = 0;
    int exitCode = 0;

    rc = scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
    if (rc != 6)
    {
        exitCode = ERR_IN;
    }
    else
    {
        double tmp = 0;
        double sideA = 0, sideB = 0, sideC = 0;
        short result = 0;

        sideA = sqrt((bx - cx) * (bx - cx) + (by - cy) * (by - cy));
        sideB = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));
        sideC = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));

        if (sideC > sideB)
        {
            tmp = sideB;
            sideB = sideC;
            sideC = tmp;
        }
        if (sideB > sideA)
        {
            tmp = sideA;
            sideA = sideB;
            sideB = tmp;
        }

        tmp = sideB * sideB + sideC * sideC;
        result = 2;
        if (fabs(tmp - sideA * sideA) < FLOAT_ERR)
            result = 1;
        else if (tmp > sideA * sideA)
            result = 0;


        printf("%d", result);
    }



    return exitCode;
}
