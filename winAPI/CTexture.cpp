#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBMP = 0;
	m_bmpInfo = {};
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

HDC CTexture::getDC()
{
	return m_hDC;
}

HBITMAP CTexture::getBmp()
{
	return m_hBMP;
}

BITMAP CTexture::getBmpInfo()
{
	return m_bmpInfo;
}

UINT CTexture::getBmpWidth()
{
	return (int)(m_bmpInfo.bmWidth);
}

UINT CTexture::getBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CTexture::load(const wstring& strPath)
{
	m_hBMP = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr로 해도 됨.
		strPath.c_str(),						// 파일 경로를 C style 문자열로 변환
		IMAGE_BITMAP,							// 이미지 타입, 비트맵 이미지로 지정
		0, 0,									// 이미지의 X, Y 크기, 0을 주면 이미지 크기로 설정
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// 이미지 로딩 타입.
	);


	assert(m_hBMP);		// 이미지 불러오기 실패한 경우

	m_hDC = CreateCompatibleDC(CCore::getInst()->getMainDC());	// DC

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);	// 비트맵을 DC와 연결

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);				// 비트맵 정보

}
