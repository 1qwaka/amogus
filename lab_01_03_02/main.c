#include <stdio.h>
#include <math.h>

double count_resistance(double r1, double r2, double r3);

int main(void)
{
    double r1, r2, r3, r;
    scanf("%lf%lf%lf", &r1, &r2, &r3);
    r = count_resistance(r1, r2, r3);
    printf("%.6lf", r);

    return 0;
}

double count_resistance(double r1, double r2, double r3)
{
    return 1 / (1 / r1 + 1 / r2 + 1 / r3);
}