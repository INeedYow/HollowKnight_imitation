#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSound.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{
	// Texture ����
	for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapTex.clear();

	// Sound ����
	for (map<wstring, CSound*>::iterator iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
	m_mapSound.clear();
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

CTexture* CResourceManager::createTexture(const wstring& strKey, UINT width, UINT height)
{
	CTexture* pTex = findTexture(strKey);
	if (nullptr != pTex)
	{
		return nullptr;
	}

	pTex = new CTexture;
	pTex->create(width, height);
	pTex->setKey(strKey);

	m_mapTex.insert(make_pair(strKey, pTex));

	return pTex;
}

CSound* CResourceManager::findSound(const wstring& strKey)
{
	// CSound Ű ���� ���� Ž��
	map<wstring, CSound*>::iterator iter = m_mapSound.find(strKey);

	if (m_mapSound.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CSound* CResourceManager::loadSound(const wstring& strKey, const wstring& strRelativePath)
{
	// Sound�� �ҷ����� �� �ڷᱸ���� �̹� Sound�� �ִ��� Ȯ��
	CSound* pSound = findSound(strKey);
	if (nullptr != pSound)
	{
		return pSound;
	}

	// Sound ���� ��� Ȯ��
	wstring strFilePath = CPathManager::getInst()->getRelativeContentPath();
	strFilePath += strRelativePath;

	// Sound ���� �� ����
	pSound = new CSound;
	pSound->load(strFilePath, false);
	pSound->setKey(strKey);
	pSound->setRelativePath(strRelativePath);

	m_mapSound.insert(make_pair(strKey, pSound));

	return pSound;
}

CSound* CResourceManager::loadBGM(const wstring& strKey, const wstring& strRelativePath)
{
	CSound* pBGM = m_pBGM;
	if (nullptr != pBGM)
		return pBGM;

	// Sound ���� ��� Ȯ��
	wstring strFilePath = CPathManager::getInst()->getRelativeContentPath();
	strFilePath += strRelativePath;

	// Sound ���� �� ����
	pBGM = new CSound;
	pBGM->load(strFilePath, true);
	pBGM->setKey(strKey);
	pBGM->setRelativePath(strRelativePath);

	m_pBGM = pBGM;

	return pBGM;
}