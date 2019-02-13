#include "ParserCSV.h"
using namespace std;

int main()
{
	CParserCSV *pCSV = CParserCSV::GetInst();
	if (!pCSV->LoadCSV("Book1.csv"))
	{
		CParserCSV::DestroyInst();
		return -1;
	}

	pCSV->printCSV();
	CParserCSV::DestroyInst();

	return 0;
}