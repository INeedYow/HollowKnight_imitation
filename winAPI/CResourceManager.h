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

	CSound* findSound(const wstring& strKey);		// ����� Sound Ž��
	CSound* loadSound(const wstring& strKey, const wstring& strRelativePath);	// Sound �ҷ����� �̹� �ִ� ��� �ִ� Sound ��ȯ

	CSound* loadBGM(const wstring& strKey, const wstring& strRelativePath);		// BGM �ҷ����� �̹� �ִ� ��� �ִ� BGM ��ȯ
};
