#include <stdio.h>
int main()
{
    int seats[50][50];
    int rows, cols, i, j, k, fr_row, tot_fr, fo_row, fo_start, middle, dist, side, r, count;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
	printf("Enter number of seats in each row: ");
    scanf("%d", &cols);

    printf("Enter seating status (0 = free, 1 = booked):\n");

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &seats[i][j]);
        }
    }

    printf("\n    ");

    for (j = 0; j < cols; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (i = 0; i < rows; i++)
    {
        printf("R%d  ", i);

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }

        printf("\n");
    }

    tot_fr = 0;

    printf("\nFree seats per row: ");

    for (i = 0; i < rows; i++)
    {
        fr_row = 0;

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                fr_row++;
        }

        printf("%d ", fr_row);
        tot_fr = tot_fr + fr_row;
    }

    printf("   Total free: %d\n", tot_fr);

    printf("\nEnter number of customers in group: ");
    scanf("%d", &k);

    while (k <= 0 || k > cols)
    {
        printf("Invalid group size! Enter between 1 and %d: ", cols);
        scanf("%d", &k);
    }

    middle = rows / 2;
    fo_row = -1;
    fo_start = -1;

    for (dist = 0; dist < rows && fo_row == -1; dist++)
    {
        for (side = 0; side < 2 && fo_row == -1; side++)
        {
            if (side == 0)
                r = middle - dist;
            else
                r = middle + dist;

            if (dist == 0 && side == 1)
                continue;

            if (r < 0 || r >= rows)
                continue;

            count = 0;

            for (j = 0; j < cols; j++)
            {
                if (seats[r][j] == 0)
                    count++;
                else
                    count = 0;

                if (count == k)
                {
                    fo_row = r;
                    fo_start = j - k + 1;
                    break;
                }
            }
        }
    }

    if (fo_row == -1)
    {
        printf("\nSorry! No row has %d seats together. Seating plan not changed.\n", k);
    }
    else
    {
        for (j = fo_start; j < fo_start + k; j++)
        {
            seats[fo_row][j] = 1;
        }

        printf("\nGroup of %d seated in row %d, seats %d to %d\n",
               k, fo_row, fo_start, fo_start + k - 1);

        printf("\n    ");

        for (j = 0; j < cols; j++)
        {
            printf("%d ", j);
        }

        printf("\n");

        for (i = 0; i < rows; i++)
        {
            printf("R%d  ", i);

            for (j = 0; j < cols; j++)
            {
                if (seats[i][j] == 0)
                    printf("_ ");
                else
                    printf("X ");
            }

            printf("\n");
        }

        printf("\nRemaining free seats: %d\n", tot_fr - k);
    }

    return 0;
}
