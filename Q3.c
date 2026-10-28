#include <stdio.h>

void inputReadings(float t[][50], int s, int h)
{
    int i, j;

    for(i = 0; i < s; i++)
    {
        printf("\nSensor %d:\n", i + 1);

        for(j = 0; j < h; j++)
        {
            printf("Hour %d: ", j + 1);
            scanf("%f", &t[i][j]);
        }
    }
}

void analyzeSensor(float r[], int h, float *tot, float *avg,
                   float *hi, float *lo, int *cr, int *wr, int *st)
{
    int i, c = 0;

    *tot = 0;
    *cr = 0;
    *wr = 0;
    *st = 0;
    *hi = r[0];
    *lo = r[0];

    for(i = 0; i < h; i++)
    {
        *tot = *tot + r[i];

        if(r[i] > *hi)
            *hi = r[i];

        if(r[i] < *lo)
            *lo = r[i];

        if(r[i] >= 40)
            (*cr)++;

        if(r[i] >= 35 && r[i] <= 39)
            (*wr)++;

        if(r[i] >= 35)
        {
            c++;

            if(c > *st)
                *st = c;
        }
        else
            c = 0;
    }

    *avg = *tot / h;
}

int highestAverage(float t[][50], int s, int h)
{
    int i, j, hs = 0;
    float tot, avg, ha = 0;

    for(i = 0; i < s; i++)
    {
        tot = 0;

        for(j = 0; j < h; j++)
            tot = tot + t[i][j];

        avg = tot / h;

        if(i == 0 || avg > ha)
        {
            ha = avg;
            hs = i;
        }
    }

    return hs;
}

int main()
{
    float t[20][50];
    float tot, avg, hi, lo, ha = 0;
    int s, h, i, j, cr, wr, st, hs;

    printf("Enter number of sensors: ");
    scanf("%d", &s);

    printf("Enter number of readings: ");
    scanf("%d", &h);

    if(s < 1 || s > 20 || h < 1 || h > 50)
    {
        printf("Invalid input!");
        return 0;
    }

    inputReadings(t, s, h);

    for(i = 0; i < s; i++)
    {
        analyzeSensor(t[i], h, &tot, &avg, &hi, &lo, &cr, &wr, &st);

        printf("\nSensor %d Report\n", i + 1);
        printf("Total: %.2f\n", tot);
        printf("Average: %.2f\n", avg);
        printf("Highest: %.2f\n", hi);
        printf("Lowest: %.2f\n", lo);
        printf("Critical Readings: %d\n", cr);
        printf("Warning Readings: %d\n", wr);
        printf("Longest Streak: %d\n", st);
    }

    hs = highestAverage(t, s, h);

    for(j = 0; j < h; j++)
        ha = ha + t[hs][j];

    ha = ha / h;

    printf("\nSensor with Highest Average: %d\n", hs + 1);
    printf("Highest Average: %.2f\n", ha);

    return 0;
}
