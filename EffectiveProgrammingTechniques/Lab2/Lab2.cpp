#include <iostream>
#include <stdlib.h>
using namespace std;

/*
task 1: pointer arithmatic
▪ should the value 5 appear directly in the function?
size of integer = 4 bytes
array offset *(array+0) same as array dereferencing array[0]
offset+5: incrementing by 4*6 = 24 bytes therefore array is
printed from the 6th position i.e. from 5, therefore 5 should appear.
*/
void v_alloc_table_add_5(int iSize)
{
    // dynamic memory allocation of 1D array
    int *array = NULL;                // Pointer initialized with NULL
    array = new (nothrow) int[iSize]; // request memory for the variable
    // invalid array size
    if (iSize <= 0)
    {
        cout << "Error! memory could not be allocated.";
    }
    else
    {
        // incrementing array offset
        for (int offset = 0; offset < iSize; offset++)
        {
            array[offset] = offset + 5;
        }
        // printing array
        cout << "Final array: ";
        for (int i = 0; i < iSize; i++)
        {
            cout << array[i] << " ";
        }
    }
    // free dynamically allocated array pointed by pointer variable
    delete[] array;
}

/*
task 2: true if pointer points to array[row][col] else false
▪ Determine what to insert instead of ??? when the reference cannot be used.
*/
bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY)
{
    // no array is created and pointer does not point to array
    if (iSizeX < 0 || iSizeY < 0)
    {
        return false;
    }
    // dynamic allocation of 2d array
    else
    {
        //Create an array of pointers that points to more arrays
        int **pi_table_array = new int *[iSizeX];
        for (int i = 0; i < iSizeX; i++)
        {
            pi_table_array[i] = new int[iSizeY];
        }
        // pointer pointing to pointer of array
        *piTable = pi_table_array;
    }
    return true;
}

/* 
task 3
▪ Determine what to insert instead of ??? when the reference cannot be used.
▪ Will there be a difference compared with function b_alloc_table_2_dim?
yes after dealocation the memory will not be in use.
▪ Can b_dealloc_table_2_dim have fewer parameters then function b_alloc_table_2_dim?
yes we can do away with iSizeY parameter
*/
bool b_dealloc_table_2_dim(int **piTable, int iSizeX, int iSizeY)
{
    // no array is created and pointer does not point to array
    if (iSizeX < 0 || iSizeY < 0)
    {
        return false;
    }
    // delete dynamically allocated 2D array
    else
    {
         // Free each sub-array
        for (int i = 0; i < iSizeX; i++)
        {
            delete[] piTable[i];
            cout << "\n";
            cout << "column deleted\n";
        }
        // Free the array of pointers
        delete[] piTable;
        cout << "deleted\n";
    }
    return true;
}

int main()
{
    cout << "\n"; 
    cout << "Enter Array size: ";
    int iSize;
    cin >> iSize;
    v_alloc_table_add_5(iSize);
    cout << "\n\n";

    int **pi_table;

    // task 2
    cout << "succesfull 1 or unsuccesfull 0: ";
    bool allocate = b_alloc_table_2_dim(&pi_table, 5, 3);
    cout << allocate;
    cout << "\n\n";

    // task 3
    cout << "succesfull 1 or unsuccesfull 0: ";
    bool deallocate = b_dealloc_table_2_dim(pi_table, 5, 3);
    cout << deallocate;

    return 0;
}