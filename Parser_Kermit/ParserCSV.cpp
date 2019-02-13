#include "ParserCSV.h"

CParserCSV* CParserCSV::m_pInst = nullptr;

CParserCSV::CParserCSV()
{
}


CParserCSV::~CParserCSV()
{
	m_vecTextureAtlas.clear();
	fclose(m_pFile);
}

bool CParserCSV::LoadCSV(const char * pFileName,
	const char* mode, const char * strKey)
{

	if (strKey)
	{
		// add path to texture file
	}

	// fopen을 사용하기 위해 filestream을 사용해야한다. 
	// "": const char*
	// '': char  / 'rb234df' : int

	// SEEK_SET: 처음으로부터 offset 만큼
	// SEEK_CUR: 현재 위치로부터 offset만큼 떨어진
	// SEEK_END: 파일의 마지막 위치로부터 offset만큼 떨어진
	// fseek(pFile, 0, SEEK_SET);

	fopen_s(&m_pFile, pFileName, mode);

	if (!m_pFile)
		return false;

	return ReadCSV();
}

bool CParserCSV::ReadCSV()
{
	char cBuffer[MAX_STR];
	char *pLine = nullptr;

	bool readFirstLine = true;
	while (feof(m_pFile) == 0)
	{
		pLine = fgets(cBuffer, sizeof(cBuffer), m_pFile);

		if (readFirstLine)
		{
			ReadColumn(pLine);
			readFirstLine = false;
			continue;			
		}
		//fread(void* Buffer, size_t elemsize, size_t elemcount, FILE* stream);

		if (pLine != nullptr)
		{
			PTextureAtlasInfo tInfo = new TextureAtlasInfo;
			//strtok_s(분리할 문자열, 한정자, 남은 문자열) return: char* 
			// pStr에는 분리된 문자열 들어가고 pContext에는 남은 것들이 들어간다. 
			//char *pContext = nullptr;
			//char* pResult = strtok_s(pStr, ",", &pContext);
			//pResult = strtok_s(nullptr, ",", &pContext);

			// 정상: sscanf_s("queen,", "%[^,]", temp,20);

			char *pContext = nullptr;
			strtok_s(pLine, ",", &pContext);
			strtok_s(nullptr, ",", &pContext);
			sscanf_s(pContext, "%hd,%hd,%hd,%hd", &tInfo->xPos, &tInfo->yPos, &tInfo->xWidth, &tInfo->yWidth);
			tInfo->strName = pLine;
			//	sscanf_s("queen,2,3,4,5\r\n", "%[^,]s,%hd,%hd,%hd,%hd\n",
			//		temp,&tInfo->xPos, &tInfo->yPos, &tInfo->xWidth, &tInfo->yWidth,20);
			//	sscanf_s(pStr, "%[^,],%hud,%hud,%hud,%hud\n", tInfo->strName, tInfo->xPos, tInfo->yPos, tInfo->xWidth, tInfo->yWidth);
			m_vecTextureAtlas.push_back(tInfo);
		}
	}
	return true;
}

void CParserCSV::ReadColumn(char * pLine)
{
	char *pContext = nullptr;
	char *pResult = strtok_s(pLine, ",", &pContext);
	while (pResult != nullptr)
	{
		m_vecColum.push_back(pResult);
		pResult = strtok_s(nullptr, ",", &pContext);
	}

	std::string strLine = m_vecColum[m_vecColum.size() - 1];
	m_vecColum.pop_back();
	std::string modifyColum;

	for (int i = 0; i < strLine.size(); ++i)
	{
		if (strLine[i] == '\r' || strLine[i] == '\n')
		{
			modifyColum = strLine.substr(0, i);
			break;
		}
	}
	m_vecColum.push_back(modifyColum);
}


void CParserCSV::printCSV()
{
	for (int i = 0; i < m_vecColum.size(); ++i)
	{
		std::cout << m_vecColum[i].c_str();
		std::cout << "  ";
	}
	std::cout << std::endl;
	for (int i = 0; i < m_vecTextureAtlas.size(); ++i)
	{
		std::cout << m_vecTextureAtlas[i]->strName.c_str();
		std::cout << "  ";
		std::cout << m_vecTextureAtlas[i]->xPos;
		std::cout << "  ";
		std::cout << m_vecTextureAtlas[i]->yPos;
		std::cout << "  ";
		std::cout << m_vecTextureAtlas[i]->xWidth;
		std::cout << "  ";
		std::cout << m_vecTextureAtlas[i]->yWidth;
		std::cout << std::endl;
	}
}