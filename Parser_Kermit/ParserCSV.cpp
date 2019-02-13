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

	// fopen�� ����ϱ� ���� filestream�� ����ؾ��Ѵ�. 
	// "": const char*
	// '': char  / 'rb234df' : int

	// SEEK_SET: ó�����κ��� offset ��ŭ
	// SEEK_CUR: ���� ��ġ�κ��� offset��ŭ ������
	// SEEK_END: ������ ������ ��ġ�κ��� offset��ŭ ������
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
			//strtok_s(�и��� ���ڿ�, ������, ���� ���ڿ�) return: char* 
			// pStr���� �и��� ���ڿ� ���� pContext���� ���� �͵��� ����. 
			//char *pContext = nullptr;
			//char* pResult = strtok_s(pStr, ",", &pContext);
			//pResult = strtok_s(nullptr, ",", &pContext);

			// ����: sscanf_s("queen,", "%[^,]", temp,20);

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