#pragma once

class CTexture;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;
	map<wstring, CSound*>	m_mapSound;
	CSound* m_pBGM;

public:
	CTexture* findTexture(const wstring& strKey);
	CTexture* loadTextrue(const wstring& strKey, const wstring& strRelativePath);
	CTexture* createTexture(const wstring& strKey, UINT width, UINT height);

	CSound* findSound(const wstring& strKey);		// 저장된 Sound 탐색
	CSound* loadSound(const wstring& strKey, const wstring& strRelativePath);	// Sound 불러오기 이미 있는 경우 있던 Sound 반환

	CSound* loadBGM(const wstring& strKey, const wstring& strRelativePath);		// BGM 불러오기 이미 있는 경우 있던 BGM 반환
};
