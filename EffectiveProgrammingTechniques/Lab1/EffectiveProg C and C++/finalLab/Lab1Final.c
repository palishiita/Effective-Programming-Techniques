#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PRODUCT 5
#define PERSON 4
#define DAYSINMONTH 30

void fillRandom(int DailySalesArray[PRODUCT][PERSON], int day)
{
    for (int row = 0; row < PRODUCT; row++)
    {
        for (int col = 0; col < PERSON; col++)
        {
            int randomNumber = rand() % 5;
            DailySalesArray[row][col] = randomNumber;
        }
    }
}

void writeTofile(int DailySalesArray[PRODUCT][PERSON], int day)
{
    FILE *fptr;
    fptr = fopen("salesdata.txt", "a");
    if (fptr == NULL)
    {
        printf("Error, cannot open file to write data!!");
        exit(1);
    }
    for (int row = 0; row < PRODUCT; row++)
    {
        for (int col = 0; col < PERSON; col++)
        {
            int s = DailySalesArray[row][col];
            fprintf(fptr, "%d\t ", s);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");
    fclose(fptr);
}

void readFileAndPrint()
{
    FILE *fptr;
    fptr = fopen("salesdata.txt", "r");
    if (fptr == NULL)
    {
        printf("Error, cannot open file to read data!!");
        exit(1);
    }

    int FinalSalesArray[PRODUCT][PERSON];
    for (int i = 0; i < PRODUCT; i++)
    {
        for (int j = 0; j < PERSON; j++)
        {
            FinalSalesArray[i][j] = 0;
        }
    }
    int num, row = 0, col = 0;
    while (!feof(fptr))
    {
        if (col == PERSON)
        {
            col = 0;
            row++;
        }
        if (row == PRODUCT)
        {
            row = 0;
        }
        fscanf(fptr, "%d", &num);
        FinalSalesArray[row][col] = FinalSalesArray[row][col] + num;
        col++;
    }

    fclose(fptr);

    int product[PRODUCT];
    int person[PERSON];

    product[0] = FinalSalesArray[0][0] + FinalSalesArray[0][1] + FinalSalesArray[0][2] + FinalSalesArray[0][3];
    product[1] = FinalSalesArray[1][0] + FinalSalesArray[1][1] + FinalSalesArray[1][2] + FinalSalesArray[1][3];
    product[2] = FinalSalesArray[2][0] + FinalSalesArray[2][1] + FinalSalesArray[2][2] + FinalSalesArray[2][3];
    product[3] = FinalSalesArray[3][0] + FinalSalesArray[3][1] + FinalSalesArray[3][2] + FinalSalesArray[3][3];
    product[4] = FinalSalesArray[4][0] + FinalSalesArray[4][1] + FinalSalesArray[4][2] + FinalSalesArray[4][3];

    person[0] = FinalSalesArray[0][0] + FinalSalesArray[1][0] + FinalSalesArray[2][0] + FinalSalesArray[3][0] + FinalSalesArray[4][0];
    person[1] = FinalSalesArray[0][1] + FinalSalesArray[1][1] + FinalSalesArray[2][1] + FinalSalesArray[3][1] + FinalSalesArray[4][1];
    person[2] = FinalSalesArray[0][2] + FinalSalesArray[1][2] + FinalSalesArray[2][2] + FinalSalesArray[3][2] + FinalSalesArray[4][2];
    person[3] = FinalSalesArray[0][3] + FinalSalesArray[1][3] + FinalSalesArray[2][3] + FinalSalesArray[3][3] + FinalSalesArray[4][3];

    // printing the results
    printf("\t\tPERSON1\tPERSON2\tPERSON3\tPERSON4    TOTAL\n");
    for (row = 0; row < 5; row++)
    {
        printf("Product %d\t", row + 1);
        for (col = 0; col < 4; col++)
        {
            int number = FinalSalesArray[row][col];
            printf("%d\t", number);
        }
        printf("   %d\n", product[row]);
    }
    printf("TOTAL\t\t%d\t%d\t%d\t%d\t", 
    person[0], person[1], person[2], person[3]);
}

int main(void)
{
    srand(time(NULL));
    for (int day = 0; day < DAYSINMONTH; day++)
    {
        int DailySalesArray[PRODUCT][PERSON];
        fillRandom(DailySalesArray, day);
        writeTofile(DailySalesArray, day);
    }
    readFileAndPrint();
    return 0;
}
