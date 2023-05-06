#include <string>
#include <iostream>

using namespace std;

#define DEFAULT_NAME "name"
#define DEFAULT_SIZE 4

class CTable
{
public:
    // fields
    string s_name;
    int *array;
    int iTableLen;

    // default constructor without parameter
    CTable()
    {
        s_name = DEFAULT_NAME;
        array = new int[DEFAULT_SIZE];
        cout << "without: "
             << "'" << s_name << "'" << endl;
    }

    // constructor with parameter
    CTable(string sName, int iTableLen)
    {
        s_name = sName;
        array = new int[iTableLen];
        // filling with random numbers
        for (int i = 0; i < iTableLen; i++)
        {
            array[i] = rand() % 10;
        }
        cout << "parameter: "
             << "'" << s_name << "'" << endl;
        for (int i = 0; i < iTableLen; i++)
        {
            cout << array[i] << endl;
        }
    }

    // copy constructor
    CTable(const CTable &pcOther)
    {
        s_name = (pcOther.s_name);
        iTableLen = (pcOther.iTableLen);
        array = new int[pcOther.iTableLen];
        for (int i = 0; i < pcOther.iTableLen; i++)
        {
            array[i] = pcOther.array[i];
        }
        cout << "copy: "
             << "'" << s_name << "'" << endl;
    }

    // destructor
    ~CTable()
    {
        delete[] array;
        cout << "removing: "
             << "'" << s_name << "'" << endl;
    }

    // getters and setters
    void vSetName(string sName) { s_name = sName; }
    void vSetSize(int iSize) { iTableLen = iSize; }
	string sGetName() { return s_name; }
    int iGetSize() { return iTableLen; }

    // dynamically change the array size using a new array
    bool bSetNewSize(int iNewTableLen)
    {
        // Allocate a new[] array and store it in a temporary pointer.
        int *newArray = new int[iNewTableLen];
        // Copy over the previous values that you want to keep.
        for (int i = 0; i < iTableLen; i++)
        {
            newArray[i] = array[i];
        }
        // Delete[] the old array
        delete[] array;
        // Change the member variables, ptr and size to point to
        // the new array and hold the new size
        if (iTableLen = iNewTableLen)
            return true;
        else
            return false;
    }

    CTable *pcClone()
    {
        return new CTable(*this);
    }

};

// procedures
void v_mod_tab(CTable *pcTab, int iNewSize);
void v_mod_tab(CTable cTab, int iNewSize);

int main()
{
    // creating CTable objects
    cout << "Static initialization default constructor:" << endl;
    CTable c_tab;
    cout << "\n";

    CTable c_tab1;
    c_tab1.s_name = "testName";
    c_tab1.iTableLen = 6;
    cout << c_tab1.s_name << "\n"
         << c_tab1.iTableLen << "\n";
    cout << "\n";
    // c_tab.vSetName("testNewName");
    // c_tab.bSetNewSize(7);

    cout << "Static initialization param constructor:" << endl;
    CTable c_tab2{"testName2", 7};
    cout << c_tab2.s_name << "\n"
         << c_tab2.iTableLen << "\n"; // doubt why is the length not printing??
    cout << "\n";

    cout << "creating clone of CTable objects:" << endl;
    CTable *pc_new_tab;
    pc_new_tab = c_tab.pcClone();
    cout << pc_new_tab << "\n";

    return 0;
}

/*
questions:
Q1) Consider whether the pcClone() method is functionally
similar to other elements of the code?
If so, how do you write the program to take advantage of this
fact and not copy the code unnecessarily?
Q2) Check which procedure will modify the object given as the
parameter. Will any copies will be created?
Q3) Test static and dynamic allocation of CTable objects.
When is the constructor called and when the destructor is called?
Check the constructor and destructors call when allocating
an array of CTable objects
*/