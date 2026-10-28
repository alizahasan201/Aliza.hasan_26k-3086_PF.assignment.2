#include <stdio.h>

int sumDivisors(int n);

int main()
{
    int n,a, b, sumA, sumB;
    int pairs = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for (a = 1; a <= n; a++)
    {
        sumA = sumDivisors(a);
        b = sumA;

        if (b > a && b <= n)
        {
            sumB = sumDivisors(b);

            if (sumB == a)
            {
                printf("(%d, %d)\n", a, b);
                pairs++;
            }
        }
    }

    if (pairs == 0)
        printf("No amicable pairs found.\n");
    else
        printf("Total pairs: %d\n", pairs);

    return 0;
}

int sumDivisors(int n)
{
    int i;
    int sum = 0;

    for (i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
            sum = sum + i;
    }

    return sum;
}
