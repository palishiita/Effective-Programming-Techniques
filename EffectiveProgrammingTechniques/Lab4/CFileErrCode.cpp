#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Returning the value / error code */

class CFileErrCode
{
private:
    FILE *pf_file;

public:
    CFileErrCode();
    CFileErrCode(string sFileName);
    ~CFileErrCode();

    bool bOpenFile(string sFileName);
    bool bCloseFile();
    bool bPrintLine(string sText);
    bool bPrintManyLines(vector<string> sText);
};

CFileErrCode::CFileErrCode()
{
    pf_file = NULL;
}

CFileErrCode::CFileErrCode(string sFileName)
{
    bOpenFile(sFileName);
}

CFileErrCode::~CFileErrCode()
{
    if (pf_file != NULL)
    {
        fclose(pf_file);
    }
}

bool CFileErrCode::bOpenFile(string sFileName)
{
    if (pf_file != NULL) {
		return false;
	}
	pf_file = fopen(sFileName.c_str(), "a+");
	if (pf_file == NULL) {
		return false;
	}
	return true;
}

bool CFileErrCode::bPrintLine(string sText)
{
    if (pf_file == NULL)
    {
        return false;
    }
    fprintf(pf_file, "%s\n", sText.c_str());
    return true;
}

bool CFileErrCode::bPrintManyLines(vector<string> sText)
{
    if (pf_file == NULL)
    {
        return false;
    }
    for (int i = 0; i < sText.size(); i++)
    {
        fprintf(pf_file, "%s\n", sText[i].c_str());
    }
    return true;
}

bool CFileErrCode::bCloseFile()
{
    if (pf_file == NULL)
    {
        return false;
    }
    fclose(pf_file);
    return true;
}

void vOpenFileTenTimes(string sFilename)
{
    CFileErrCode CFile;
	for (int i = 0; i < 10; i++)
	{
		if (CFile.bOpenFile(sFilename) == false)
		{
			cout << "Error opening 10 times!" << endl;
        }
	}

}

int main()
{
    string sFilename = "file.txt";
    CFileErrCode CFile1;
    vector<string> sText = {"g", "h", "i"};

    if (CFile1.bOpenFile(sFilename))
    {
        CFile1.bPrintLine("Hi!!: Printed by CFileErrCode class");
        cout << "line printed!" << endl;
        CFile1.bPrintManyLines(sText);
        cout << "vector of strings printed!" << endl;
        cout << " " << endl;
    }
    else
    {
        cout << "Error! " << endl;
    }

    CFile1.bCloseFile();

    vOpenFileTenTimes(sFilename);	

    CFile1.bCloseFile();

    return 0;
}