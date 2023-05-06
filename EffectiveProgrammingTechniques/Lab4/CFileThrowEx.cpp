#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Error handling through exceptions */

class CFileThrowEx
{
private:
	FILE *pf_file;

public:
	CFileThrowEx();
	CFileThrowEx(string sFileName);
	~CFileThrowEx();

	void vOpenFile(string sFileName);
	void vCloseFile();
	void vPrintLine(string sText);
	void vPrintManyLines(vector<string> sText);
	CFileThrowEx &operator=(const string &sFile);
};

// constructors
CFileThrowEx::CFileThrowEx() { pf_file = NULL; }
CFileThrowEx::CFileThrowEx(string sFileName) { vOpenFile(sFileName); }
// destructors
CFileThrowEx::~CFileThrowEx()
{
	if (pf_file != NULL)
	{
		fclose(pf_file);
	}
}

void CFileThrowEx::vOpenFile(string sFileName)
{
	if (pf_file != NULL)
	{
		throw 1;
	}
	pf_file = fopen(sFileName.c_str(), "a+");
	if (pf_file == NULL)
	{
		throw 1;
	}
}

void CFileThrowEx::vPrintLine(string sText)
{
	if (pf_file == NULL)
	{
		throw 1;
	}
	fprintf(pf_file, "%s\n", sText.c_str());
}

void CFileThrowEx::vPrintManyLines(vector<string> sText)
{
	if (pf_file == NULL)
	{
		throw 1;
	}
	for (int i = 0; i < sText.size(); i++)
	{
		fprintf(pf_file, "%s\n", sText[i].c_str());
	}
}

void CFileThrowEx::vCloseFile()
{
	if (pf_file == NULL)
	{
		throw 1;
	}
	fclose(pf_file);
}

CFileThrowEx &CFileThrowEx::operator=(const string &sFile)
{
	vOpenFile(sFile);
	return *this;
}

void vOpenFileTenTimes(string sFilename)
{
	CFileThrowEx CFile; // object
	for (int i = 0; i < 10; i++)
	{
		CFile.vOpenFile(sFilename);
	}
}

int main()
{
	CFileThrowEx CFile3;
	string sFilename = "file.txt";

	vector<string> sText = {"d", "e", "f"};
	try
	{
		CFile3.vOpenFile(sFilename);
		CFile3.vPrintLine("Hi!!: Printed by CFileThrowEx Class");
		cout << "line printed!" << endl;
		CFile3.vPrintManyLines(sText);
		cout << "vector of strings printed!" << endl;
	}
	catch (int e) // exception handled in catch
	{
		cout << "Error vOpenFile(), vPrintLine(), vPrintManyLines()! " 
		<< e << endl;
	}
	CFile3.vCloseFile();

// exception will be thrown because file pointer is not set to null
	try
	{
		vOpenFileTenTimes(sFilename);;
	}
	catch (int e)
	{
		cout << "error opening file 10 times! " 
		<< e << endl;
	}
	CFile3.vCloseFile();

	return 0;
}

