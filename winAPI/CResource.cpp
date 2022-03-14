#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
	m_strKey = L"";
	m_strRelativePath = L"";

}

CResource::~CResource()
{
}

void CResource::setKey(const wstring& key)
{
	m_strKey = key;
}

void CResource::setRelativePath(const wstring& strPath)
{
	m_strRelativePath = strPath;
}

const wstring& CResource::getKey()
{
	return m_strKey;
}

const wstring& CResource::getRelativePath()
{
	return m_strRelativePath;
}
