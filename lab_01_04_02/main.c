#include <stdio.h>
#include <math.h>

int main(void)
{
    double seconds = 0.0;
    int hours = 0, minutes = 0, int_secs = 0;
    scanf("%lf", &seconds);
    hours = seconds / 3600;
    minutes = ((int)seconds % 3600) / 60;
    int_secs = (int)seconds % 60;

    printf("%d %d %d", hours, minutes, int_secs);

    return 0;
}
