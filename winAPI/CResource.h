#pragma once
class CResource
{

	wstring	m_strKey;
	wstring	m_strRelativePath;

public:
	CResource();
	virtual ~CResource();

	void setKey(const wstring& eKey);
	void setRelativePath(const wstring& strPath);

	const wstring& getKey();
	const wstring& getRelativePath();
};
