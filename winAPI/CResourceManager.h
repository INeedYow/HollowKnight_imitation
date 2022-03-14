#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture* findTexture(const wstring& eKey);
	CTexture* loadTextrue(const wstring& eKey, const wstring& strRelativePath);

};
