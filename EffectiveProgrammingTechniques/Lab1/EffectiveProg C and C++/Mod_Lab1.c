#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRODUCT 5
#define PERSON 4
#define DAYSINMONTH 20
#define SLIPS 5

// method to generate random sales for product-person in array
void fillRandomSalesValue(int array[PRODUCT][PERSON])
{
    for (int row = 0; row < PRODUCT; row++)
    {
        for (int col = 0; col < PERSON; col++)
        {
            array[row][col] = (rand() % 100) + 1;
        }
    }
}

int main()
{
    srand(time(NULL));
    
    // opening the file
    FILE *fptr;

    // writing in the file randomly gernerated product-person array
    fptr = fopen("dailysalesdata.txt", "a"); 
    
    // creating product-person array for each day
    // creating multiple such product-person arrays (for month)
    int day = 0;
    while (day < DAYSINMONTH)
    {
        // declaring sales array for each day (for 30 days)
        int salesArrayPerDay[PRODUCT][PERSON];
        // filling in random values in sales array
        fillRandomSalesValue(salesArrayPerDay);
        //writing sales array to file and print it in the file
        if (fptr == NULL)
        {
            printf("Error, cannot open file to write data!!");
            return 1;
        }
        for (int row = 0; row < PRODUCT; row++)
        {
            for (int col = 0; col < PERSON; col++)
            {
                fprintf(fptr, "%d ", salesArrayPerDay[row][col]);
            }
            fprintf(fptr, "\n");
        }
        fprintf(fptr, "\n");
    }

    int num, row = 0, col = 0;
    int summedData[5][4];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            summedData[i][j] = 0;
        }
    }

    fptr = fopen("salesdata.txt", "r");

    if (fptr == NULL)
    {
        printf("Error, cannot open file to read data!!");
        return 1;
    }

    // reading data from file and summing it in a double-array
    while (!feof(fptr))
    {
        if (col == 4)
        {
            col = 0;
            row++;
        }
        if (row == 5)
        {
            row = 0;
        }

        fscanf(fptr, "%d", &num);
        summedData[row][col] = summedData[row][col] + num;
        col++;
    }
    fclose(fptr);

    // summing up data by product and by employee
    int product[5];
    int employee[4];
    product[0] = summedData[0][0] + summedData[0][1] + summedData[0][2] + summedData[0][3];
    product[1] = summedData[1][0] + summedData[1][1] + summedData[1][2] + summedData[1][3];
    product[2] = summedData[2][0] + summedData[2][1] + summedData[2][2] + summedData[2][3];
    product[3] = summedData[3][0] + summedData[3][1] + summedData[3][2] + summedData[3][3];
    product[4] = summedData[4][0] + summedData[4][1] + summedData[4][2] + summedData[4][3];
    employee[0] = summedData[0][0] + summedData[1][0] + summedData[2][0] + summedData[3][0] + summedData[4][0];
    employee[1] = summedData[0][1] + summedData[1][1] + summedData[2][1] + summedData[3][1] + summedData[4][1];
    employee[2] = summedData[0][2] + summedData[1][2] + summedData[2][2] + summedData[3][2] + summedData[4][2];
    employee[3] = summedData[0][3] + summedData[1][3] + summedData[2][3] + summedData[3][3] + summedData[4][3];

    // printing the results
    printf("\n");
    printf("\n---------------------------TOTAL MONTHLY SALES---------------------------\n");
    printf("\t\t\tEmployee number\n");
    printf("\t\t\t1.\t2.\t3.\t4.\n");
    for (row = 0; row < 5; row++)
    {
        printf("Product no.%d\t|\t", row + 1);
        for (col = 0; col < 4; col++)
        {
            int number = summedData[row][col];
            printf("%d\t", number);
        }
        printf("|   TOTAL = %d\n", product[row]);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("TOTAL\t\t|\t%d\t%d\t%d\t%d\t|", employee[0], employee[1], employee[2], employee[3]);

    return 0;
}