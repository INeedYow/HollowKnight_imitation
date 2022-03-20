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

HBITMAP& CTexture::getTestBMP()
{
	return m_hBMP;
}

void CTexture::load(const wstring& strPath)
{
	m_hBMP = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr�� �ص� ��.
		strPath.c_str(),						// ���� ��θ� C style ���ڿ��� ��ȯ
		IMAGE_BITMAP,							// �̹��� Ÿ��, ��Ʈ�� �̹����� ����
		0, 0,									// �̹����� X, Y ũ��, 0�� �ָ� �̹��� ũ��� ����
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// �̹��� �ε� Ÿ��.
	);


	assert(m_hBMP);		// �̹��� �ҷ����� ������ ���

	m_hDC = CreateCompatibleDC(CCore::getInst()->getMainDC());	// DC

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);	// ��Ʈ���� DC�� ����

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);				// ��Ʈ�� ����

}

void CTexture::create(UINT width, UINT height)
{
	HDC mainDC = CCore::getInst()->getMainDC();
	m_hBMP = CreateCompatibleBitmap(mainDC, width, height);
	m_hDC = CreateCompatibleDC(mainDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hOldBmp);

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}

