#include <stdio.h>
#include <math.h>

int get_hours(double seconds);

int get_minutes(double seconds);

int get_seconds(double seconds);

int main(void)
{
    double seconds = 0.0;
    int hours = 0, minutes = 0, int_secs = 0;

    scanf("%lf", &seconds);

    hours = get_hours(seconds);
    minutes = get_minutes(seconds);
    int_secs = get_seconds(seconds);

    printf("%d %d %d", hours, minutes, int_secs);

    return 0;
}


int get_hours(double seconds)
{
    return seconds / 3600;
}

int get_minutes(double seconds)
{
    return ((int)seconds % 3600) / 60
}

int get_seconds(double seconds)
{
    return (int)seconds % 60;
}
