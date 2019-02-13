#pragma once
#include <iostream>
#include <vector>

#define MAX_STR 255
typedef struct _tagTextureAtlasInfo
{
	std::string strName;
	std::string fileName;
	unsigned short int xPos;
	unsigned short int yPos;
	unsigned short int xWidth;
	unsigned short int yWidth;
	
	_tagTextureAtlasInfo() :
		strName(""), fileName(""),
		xPos(-1), yPos(-1),
		xWidth(-1), yWidth(-1)
	{

	}

}TextureAtlasInfo, *PTextureAtlasInfo;

class CParserCSV
{
private:
	FILE* m_pFile;
	std::vector<TextureAtlasInfo*> m_vecTextureAtlas;
	std::vector<std::string> m_vecColum;

public:
	bool LoadCSV(const char* pFileName,
		const char* mode ="rb", const char* strKey = nullptr);
	bool ReadCSV();

private:
	void ReadColumn(char* pLine);

public:
	void printCSV();

private:
	CParserCSV();
	~CParserCSV();

	//singleton
private:
	static CParserCSV* m_pInst;

public:

	static CParserCSV* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CParserCSV;

		return m_pInst;
	}
	static void DestroyInst()
	{
		if (m_pInst)
		{
			delete m_pInst;
		}
	}
};

