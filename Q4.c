#include <stdio.h>

int getValidDays()
{
    int d;

    do
    {
        printf("Enter festival days (1-7): ");
        scanf("%d", &d);

        if(d < 1 || d > 7)
            printf("Invalid days! Try again.\n");

    } while(d < 1 || d > 7);

    return d;
}

float calculateDailySales(int dn)
{
    int n, i;
    float amt, tot = 0, hi = 0;

    printf("\nDay %d\n", dn);
    printf("Enter number of orders: ");
    scanf("%d", &n);

    while(n < 1)
    {
        printf("Enter at least 1 order: ");
        scanf("%d", &n);
    }

    for(i = 1; i <= n; i++)
    {
        printf("Enter order %d amount: ", i);
        scanf("%f", &amt);

        while(amt <= 0)
        {
            printf("Enter a positive amount: ");
            scanf("%f", &amt);
        }

        tot = tot + amt;

        if(i == 1 || amt > hi)
            hi = amt;
    }

    printf("Total Sales: Rs. %.2f\n", tot);
    printf("Average Order: Rs. %.2f\n", tot / n);
    printf("Highest Order: Rs. %.2f\n", hi);

    return tot;
}

int findHighestSalesDay(float ds[], int nd)
{
    int i, d = 1;
    float hi = ds[0];

    for(i = 1; i < nd; i++)
    {
        if(ds[i] > hi)
        {
            hi = ds[i];
            d = i + 1;
        }
    }

    return d;
}

void displayBarChart(float ds[], int nd)
{
    int i, j;

    printf("\nDaily Sales Bar Chart\n");

    for(i = 0; i < nd; i++)
    {
        printf("Day %d: ", i + 1);

        for(j = 1; j <= ds[i] / 100; j++)
            printf("*");

        printf("\n");
    }
}

int main()
{
    float ds[7], tot = 0;
    int d, i, hd;

    d = getValidDays();

    for(i = 0; i < d; i++)
    {
        ds[i] = calculateDailySales(i + 1);
        tot = tot + ds[i];
    }

    hd = findHighestSalesDay(ds, d);

    printf("\nTotal Festival Sales: Rs. %.2f\n", tot);
    printf("Highest Sales Day: %d\n", hd);
    printf("Highest Daily Sales: Rs. %.2f\n", ds[hd - 1]);

    displayBarChart(ds, d);

    return 0;
}
