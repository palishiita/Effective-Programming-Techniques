#include <iostream>
#include <string>

#define DEFAULT_SIZE 5
#define DEFAULT_NAME "Default"

using namespace std;

class CTable
{
    // fields
private:
    string s_name;
    int iTableLen;
    int *array;

public:
    // constructor: invoked when object is created to initialize the object
    // default constructor
    CTable();
    // param constructor
    CTable(string sName, int iTableLen);
    // copy constructor (clone): invoked when a new object is created from 
    // an existing object, as a copy of the existing object
    CTable(const CTable &pcOther);
    // destructors: invoked automatically when the object goes out of scope 
    // or is explicitly destroyed by a call to delete
    ~CTable();

    // getters and setters
    void vSetName(string sName) { s_name = sName; };
    void vSetSize(int iSize) { iTableLen = iSize; };
    int iGetSize() { return sizeof(array); };
    string sGetName() { return s_name; };
    int *getArray() { return array; };
    void setArray(int *arrayPtr) { array = arrayPtr; };
    
    // setting new size
    bool bSetNewSize(int iTableLen);
    
    // overriding the copy method
    CTable *pcClone() { return new CTable(*this); };
};

// procedures
void v_mod_tab(CTable *pcTab, int iNewSize);
void v_mod_tab(CTable cTab, int iNewSize);

// default constructor
CTable::CTable()
{
    vSetName(DEFAULT_NAME);
    vSetSize(DEFAULT_SIZE);
    array = new int[DEFAULT_SIZE];
    for (int i = 0; i < iTableLen; i++)
    {
        array[i] = rand() % 10;
    }
    cout << "without: '" << s_name << "'" << endl;
    for (int i = 0; i < iTableLen; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// param constructor
CTable::CTable(string sName, int iTableLen)
{
    vSetName(sName);
    vSetSize(iTableLen);
    array = new int[iTableLen];
    for (int i = 0; i < iTableLen; i++)
    {
        array[i] = rand() % 10;
    }
    cout << "parameter: '" << s_name << "'" << endl;
    for (int i = 0; i < iTableLen; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// copy constructor (clone object)
CTable::CTable(const CTable &pcOther) : s_name(pcOther.s_name), iTableLen(pcOther.iTableLen)
{
    array = new int[pcOther.iTableLen];
    for (int i = 0; i < pcOther.iTableLen; i++)
    {
        array[i] = pcOther.array[i];
    }
    for (int i = 0; i < iTableLen; i++)
    {
        cout << array[i] << " ";
    }
    cout << "copy: '" << s_name << "'" << endl;
    cout << endl;
}

// destructor
CTable::~CTable()
{
    cout << "delete: '" << s_name << "'" << endl;
    delete[] array;
}

// https://stackoverflow.com/questions/12032222/how-to-dynamically-increase-the-array-size
bool CTable::bSetNewSize(int new_iTableLen)
{
    array = new int[iTableLen];   
    int *arrayNew = new int[new_iTableLen];
    for (int i = 0; i < iTableLen; i++)
    {
        arrayNew[i] = array[i];
    }
    delete[] array; 
    array = arrayNew;
    if (sizeof(array) == sizeof(arrayNew))
    {
        return true;
    }
    else 
    {
        return false;
    }
    arrayNew = NULL;
}

void v_mod_tab(CTable *pcTab, int iNewSize)
{
    pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize)
{
    cTab.bSetNewSize(iNewSize);
}

int main()
{
    cout << "#1 Static initialization default and parameter constructor:" << endl;
    CTable c_tab1 = CTable();
    CTable c_tab2 = CTable("test1", 2);
    cout << "\n";

    cout << "#2 Dynamic initialization  default and parameter constructor:" << endl;
    CTable *c_tab3 = new CTable();
    
    CTable *c_tab4 = new CTable("test2", 7);
    cout << "\n";

    /*
    cout << "#3 Dynamic array initialization default:" << endl;
    // 3 arrays of default length of 5
    CTable *c_tab5 = new CTable[3];
    cout << "\n";
    */

    cout << "#4 Cloning of statically initialized object"
         << " default and parameter constructor:" << endl;
    CTable c_tab6 = CTable();
    CTable c_tab_copy1 = c_tab6;
    CTable c_tab7 = CTable("test3", 2);
    CTable c_tab_copy2 = c_tab7;
    cout << "\n";

    cout << "#5 Cloning of statically initialized object"
         << " default and parameter constructor:" << endl;
    CTable c_tab8 = CTable();
    CTable *c_tab_copy3 = c_tab8.pcClone();
    CTable c_tab9 = CTable("test4", 3);
    CTable *c_tab_copy4 = c_tab9.pcClone();
    cout << "\n";

    cout << "#6 Cloning of dynamically initialized object"
         << " default and parameter constructor:" << endl;
    CTable c_tab10 = CTable();
    CTable *c_tab_copy5 = c_tab10.pcClone();
    CTable c_tab11 = CTable("test4", 3);
    CTable *c_tab_copy6 = c_tab11.pcClone();
    cout << "\n";

    cout << "#7 Modifying cloned objects:" << endl;
    c_tab_copy5->vSetName("new copy");
    c_tab_copy5->vSetSize(3);
    cout << c_tab_copy5->sGetName() << endl;
    cout << c_tab_copy5->iGetSize() << endl;
    cout << "\n";

    cout << "#8 change size:" << endl;
    CTable *c_tab12 = new CTable("test5", 3);
    cout << "size: " << c_tab12->iGetSize() << endl;
    v_mod_tab(c_tab12, 6);
    c_tab12->bSetNewSize(6);
    cout << "changed size: " << c_tab12->iGetSize() << endl;
    cout << "\n";

    return 0;
}