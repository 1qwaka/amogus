#include <stdio.h>
#include <math.h>

int main(void)
{
    double ax, ay, bx, by, cx, cy;
    double p;
    scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);

    p = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)) +
            sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy)) +
            sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by));
    printf("%.6lf", p);

    return 0;
}
