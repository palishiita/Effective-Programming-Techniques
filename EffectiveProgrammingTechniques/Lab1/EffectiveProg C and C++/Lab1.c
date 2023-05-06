#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define PRODUCT 5
#define PERSON 4

void fillRandom(int array[PRODUCT][PERSON], int max);

int main(void)
{
    int salesArray[PRODUCT][PERSON];

    // generate random values in array
    srand(time(NULL));
    fillRandom(salesArray, 100);
    // print array
    printf("sales array:\n");
    for (int i = 0; i < PRODUCT; i++)
    {
        for (int j = 0; j < PERSON; j++)
        {
            printf("%3d ", salesArray[i][j]);
        }
        printf("\n");
    }

    // write array to a file and printing it in the file
    FILE *fptr;
    //fptr = fopen("SalesData.txt", "w");
    if (fptr == NULL)
    {
        printf("Error, cannot open file!!");
        return 1;
    }
    for (int i = 0; i < PRODUCT; i++)
    {
        for (int j = 0; j < PERSON; j++)
        {
            fprintf(fptr, "%d ", salesArray[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    getch();

    // totalsales per product
    printf("        Person1    Person2    Person3    Person4    TotSale");
    int totalSalesPerProduct = 0; // total of every row
    for (int row = 0; row < 5; row++)
    {
        printf("\nProduct");
        printf("%d      ", (row + 1));
        for (int col = 0; col < 4; col++)
        {
            printf("%d        ", salesArray[row][col]);
            totalSalesPerProduct = totalSalesPerProduct + salesArray[row][col];
        }
        printf("%d   \n", totalSalesPerProduct);
        totalSalesPerProduct = 0;
    }

    // totalsales per person
    printf("\nTotSale    ");
    int totalSalesPerPerson = 0; // total of every column
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 5; row++)
        {
            totalSalesPerPerson = totalSalesPerPerson + salesArray[row][col];
        }
        printf("%d         ", totalSalesPerPerson);
        totalSalesPerPerson = 0;
    }

    return 0;
}

// method to generate random number in array
void fillRandom(int array[PRODUCT][PERSON], int max)
{
    for (int row = 0; row < PRODUCT; row++)
    {
        for (int col = 0; col < PERSON; col++)
        {
            array[row][col] = (rand() % max) + 1;
        }
    }
}

