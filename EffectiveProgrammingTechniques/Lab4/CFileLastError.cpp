#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* GetLastError type communication, via a global variable
that indicates the success or failure of the last operation */

class CFileLastError
{
private: // fields
    FILE *pf_file;
    bool b_last_error; // global variable

public:
    CFileLastError();
    CFileLastError(string sFileName);
    ~CFileLastError();
    void vOpenFile(string sFileName);
    void vCloseFile();
    void vPrintLine(string sText);
    void vPrintManyLines(vector<string> sText);
    // indicates whether an error occurred when calling the last method
    bool bGetLastError();
};

// creates an object to use, but file is not open.
CFileLastError::CFileLastError()
{
    pf_file = NULL;
}

// creates the object to use,tries to open file with given name
CFileLastError::CFileLastError(string sFileName)
{
    vOpenFile(sFileName);
}

// destructor closes the open file if it is necessary
CFileLastError::~CFileLastError()
{
    if (pf_file != NULL)
    {
        fclose(pf_file);
    }
}

/* Each member function firstly sets the attribute b_last_error to
false, and if an error occurs, sets it to true and exits. */
void CFileLastError::vOpenFile(string sFileName)
{
    b_last_error = true;
    if (pf_file == NULL)
    {
        b_last_error = false;
    }
    
    pf_file = fopen(sFileName.c_str(), "a+");
    
    if (pf_file != NULL)
    {
        b_last_error = false;
    }
}

// writes one line of text to the file, if the file is
// not open, it causes an error
void CFileLastError::vPrintLine(string sText)
{
    b_last_error = true;
    if (pf_file == NULL)
    {
        b_last_error = false;
    }
    fprintf(pf_file, "%s\n", sText.c_str());
    if (pf_file != NULL)
    {
        b_last_error = false;
    }
}

// calls the vPrintLine function a number of times,
// separately for each string variable
void CFileLastError::vPrintManyLines(vector<string> sText)
{
    b_last_error = true;
    if (pf_file == NULL)
    {
        b_last_error = false;
    }
    for (int i = 0; i < sText.size(); i++)
    {
        fprintf(pf_file, "%s\n", sText[i].c_str());
    }
}

void CFileLastError::vCloseFile()
{
    b_last_error = true;
    if (pf_file == NULL)
    {
        b_last_error = false;
    }
    fclose(pf_file);
}

bool CFileLastError::bGetLastError() 
{ 
    return (b_last_error); 
}

void vOpenFileTenTimes(string sFilename)
{
	CFileLastError CFile;
	for (int i = 1; i <= 10; i++)
	{
		if (CFile.bGetLastError()) {
			cout << "error opening file 10 times" << endl;
			i = 10;
		}
		CFile.vOpenFile(sFilename);
        CFile.vCloseFile();
	}
}

int main()
{

    CFileLastError CFile2;

    string sFilename = "file.txt";
    
    CFile2.vOpenFile(sFilename);

    vector<string> sText = {"a", "b", "c"};

    // b_last_error is set to false, 
    // and if an error occurs, its to true
    if (CFile2.bGetLastError() == false) // SUCCESS 
    {
        CFile2.vPrintLine("Hi!!: Printed by CFileLastError class");
        cout << "line printed!" << endl;
        CFile2.vPrintManyLines(sText);
        cout << "vector of strings printed!" << endl;
        cout << " " << endl;
    }
    else
	{
		cout << "Error!" << endl;
	}
    
    CFile2.vCloseFile();
    

    vOpenFileTenTimes(sFilename);

    CFile2.vCloseFile();
    
    return 0;
}