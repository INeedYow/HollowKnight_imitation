#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture* findTexture(const wstring& strKey);
	CTexture* loadTextrue(const wstring& strKey, const wstring& strRelativePath);
	CTexture* createTexture(const wstring& strKey, UINT width, UINT height);
};
