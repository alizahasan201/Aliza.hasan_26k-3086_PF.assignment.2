#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("\n===== LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

void registerMember(char nm[], int *id, int *tp)
{
    int t;

    printf("Enter name: ");
    scanf(" %49[^\n]", nm);

    printf("Enter student ID: ");
    scanf("%d", id);

    printf("Enter type (1 Student, 2 Faculty): ");
    scanf("%d", &t);

    while(t != 1 && t != 2)
    {
        printf("Enter 1 or 2: ");
        scanf("%d", &t);
    }

    *tp = t;

    printf("Member registered!\n");
}

void displayBooks(int bid[], char bt[][50], int cp[], int n)
{
    int i;

    printf("\nID\tBook Title\t\tCopies\n");

    for(i = 0; i < n; i++)
        printf("%d\t%-20s\t%d\n", bid[i], bt[i], cp[i]);
}

void borrowBook(int bid[], char bt[][50], int cp[], int n,
                int bb[], int *bc, int tp)
{
    int id, d, i, f = -1;

    if(*bc >= 3)
    {
        printf("You can borrow only 3 books!\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    for(i = 0; i < n; i++)
    {
        if(bid[i] == id)
        {
            f = i;
            break;
        }
    }

    if(f == -1)
        printf("Invalid book ID!\n");

    else if(cp[f] == 0)
        printf("Book not available!\n");

    else
    {
        printf("Enter borrowing days: ");
        scanf("%d", &d);

        while(d <= 0)
        {
            printf("Enter positive days: ");
            scanf("%d", &d);
        }

        bb[*bc] = id;
        (*bc)++;
        cp[f]--;

        printf("Book borrowed: %s\n", bt[f]);

        if(tp == 1 && d > 14)
            printf("Student limit is 14 days.\n");

        else if(tp == 2 && d > 30)
            printf("Faculty limit is 30 days.\n");
    }
}

float returnBook(int bid[], int cp[], int n, int bb[],
                 int *bc, int tp, float *tf)
{
    int id, d, i, j, f = -1, b = -1, lim;
    float fine = 0, pay = 0;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for(i = 0; i < n; i++)
    {
        if(bid[i] == id)
        {
            f = i;
            break;
        }
    }

    for(i = 0; i < *bc; i++)
    {
        if(bb[i] == id)
        {
            b = i;
            break;
        }
    }

    if(f == -1 || b == -1)
    {
        printf("Invalid ID or book not borrowed!\n");
        return 0;
    }

    printf("Enter actual days kept: ");
    scanf("%d", &d);

    while(d <= 0)
    {
        printf("Enter positive days: ");
        scanf("%d", &d);
    }

    if(tp == 1)
        lim = 14;
    else
        lim = 30;

    if(d > lim)
    {
        if(tp == 1)
            fine = (d - lim) * 20;
        else
            fine = (d - lim) * 10;
    }

    pay = fine;

    if(fine > 0)
    {
        printf("Fine before waiver: Rs. %.2f\n", fine);
        printf("Enter membership code: ");
        scanf("%19s", code);

        if(strcmp(code, "LIB2026") == 0)
        {
            pay = fine * 0.50;
            printf("50%% waiver applied!\n");
        }
        else
            printf("Wrong code! No waiver.\n");
    }

    *tf = *tf + fine;
    cp[f]++;

    for(j = b; j < *bc - 1; j++)
        bb[j] = bb[j + 1];

    (*bc)--;

    printf("Book returned successfully!\n");
    printf("Fine before waiver: Rs. %.2f\n", fine);
    printf("Fine payable: Rs. %.2f\n", pay);

    return pay;
}

void displayMemberRecord(char nm[], int id, int tp, int bb[],
                         int bc, float tf, float fp)
{
    int i;

    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", nm);
    printf("Student ID: %d\n", id);

    if(tp == 1)
        printf("Membership: Student\n");
    else if(tp == 2)
        printf("Membership: Faculty\n");
    else
        printf("Membership: Not Registered\n");

    printf("Borrowed Books: ");

    if(bc == 0)
        printf("None");

    for(i = 0; i < bc; i++)
        printf("%d ", bb[i]);

    printf("\nTotal Fine Before Waiver: Rs. %.2f\n", tf);
    printf("Total Fine Payable: Rs. %.2f\n", fp);
}

int main()
{
    int bid[5] = {101, 102, 103, 104, 105};
    char bt[5][50] = {"C Programming", "Mathematics",
                      "Physics", "English", "Computer Science"};
    int cp[5] = {3, 4, 2, 3, 5};
    int bb[3], id = 0, tp = 0, bc = 0;
    int ch, reg = 0;
    char nm[50] = "";
    float tf = 0, fp = 0, f;

    do
    {
        displayMenu();
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                if(reg == 0)
                {
                    registerMember(nm, &id, &tp);
                    reg = 1;
                }
                else
                    printf("Member already registered!\n");
                break;

            case 2:
                displayBooks(bid, bt, cp, 5);
                break;

            case 3:
                if(reg == 1)
                    borrowBook(bid, bt, cp, 5, bb, &bc, tp);
                else
                    printf("Register first!\n");
                break;

            case 4:
                if(reg == 1)
                {
                    f = returnBook(bid, cp, 5, bb, &bc, tp, &tf);
                    fp = fp + f;
                }
                else
                    printf("Register first!\n");
                break;

            case 5:
                if(reg == 1)
                    displayMemberRecord(nm, id, tp, bb, bc, tf, fp);
                else
                    printf("No member registered!\n");
                break;

            case 6:
                printf("Exiting Library System...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(ch != 6);

    return 0;
}
