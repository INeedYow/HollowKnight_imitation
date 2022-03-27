#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	WCHAR m_strContentPath[255];

public:
	void init();

	const wchar_t* getContentPath();				// 리소스 저장 폴더의 경로 반환
	const wchar_t* getRelativeContentPath();		// 리소스 저장 폴더의 상대 경로 반환
};

