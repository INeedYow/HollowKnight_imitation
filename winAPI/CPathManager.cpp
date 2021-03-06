#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_strContentPath[0] = {};
}

CPathManager::~CPathManager()
{

}

void CPathManager::init()
{
	GetCurrentDirectory(255, m_strContentPath);					// 현재 경로 받아옴

	int iLen = (int)wcslen(m_strContentPath);

	for (int i = iLen - 1; i >= 0; i--)
	{
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_strContentPath, 255, L"\\Release\\content\\");	// wchar_t 문자열 붙이는 함수
}

const wchar_t* CPathManager::getContentPath()
{
	return m_strContentPath;
}

const wchar_t* CPathManager::getRelativeContentPath()
{
#ifdef _DEBUG
	return L"..\\Release\\content\\";
#else
	return L"content\\";
#endif

}