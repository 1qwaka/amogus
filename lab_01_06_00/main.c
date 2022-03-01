#include <stdio.h>
#include <math.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6
#define OR ||

short triangle_type(double ax, double ay, double bx, double by, double cx, double cy);

int main(void)
{
    double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0;
    short rc = 0;
    int exit_code = 0;

    rc = scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
    if (rc != 6)
    {
        exit_code = ERR_IN;
    }
    else if (fabs(ax / bx - ay / by ) < FLOAT_ERR && fabs(bx / cx - by / cy) < FLOAT_ERR)
    {
        exit_code = ERR_DATA;
    }
    else
    {
        short result = triangle_type(ax, ay, bx, by, cx, cy);
        printf("%d", result);
    }

    return exit_code;
}


short triangle_type(double ax, double ay, double bx, double by, double cx, double cy)
{
    double tmp = 0;
    double side_a = 0, side_b = 0, side_c = 0;
    short result = 0;

    side_a = sqrt((bx - cx) * (bx - cx) + (by - cy) * (by - cy));
    side_b = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));
    side_c = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));

    if (side_c > side_b)
    {
        tmp = side_b;
        side_b = side_c;
        side_c = tmp;
    }
    if (side_b > side_a)
    {
        tmp = side_a;
        side_a = side_b;
        side_b = tmp;
    }

    tmp = side_b * side_b + side_c * side_c;
    // тупоугольный по умолчанию
    result = 2;

    if (fabs(tmp - side_a * side_a) < FLOAT_ERR)
        result = 1;
    else if (tmp > side_a * side_a)
        result = 0;

    return result;
}
