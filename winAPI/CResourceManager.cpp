#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{
	for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapTex.clear();
}

CTexture* CResourceManager::findTexture(const wstring& strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(strKey);

	if (m_mapTex.end() == iter)
		return nullptr;

	return iter->second;
}

CTexture* CResourceManager::loadTextrue(const wstring& strKey, const wstring& strRelativePath)
{
	CTexture* pTex = findTexture(strKey);		// �̹� Texture�� �ִ��� Ȯ��
	if (nullptr == pTex)
	{
		// Texture ���� ��� Ȯ��
		wstring strFilePath = CPathManager::getInst()->getContentPath();
		strFilePath += strRelativePath;

		// Texture ���� �� ����
		pTex = new CTexture;
		pTex->load(strFilePath);
		pTex->setKey(strKey);
		pTex->setRelativePath(strRelativePath);

		m_mapTex.insert(make_pair(strKey, pTex));
	}
	return pTex;
}
