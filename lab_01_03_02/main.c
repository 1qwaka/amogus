#include <stdio.h>
#include <math.h>

int main(void)
{
    double r1, r2, r3, r;
    scanf("%lf%lf%lf", &r1, &r2, &r3);
    r = 1 / (1 / r1 + 1 / r2 + 1 / r3);
    printf("%.6lf", r);

    return 0;
}
