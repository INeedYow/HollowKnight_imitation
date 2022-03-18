#include "framework.h"
#include "CImage.h"
#include "CTexture.h"

CImage::CImage()
{
	m_pTex = nullptr;
}

CImage::~CImage()
{
}

CObject* CImage::clone()
{
	return nullptr;
}

void CImage::update()
{
}

void CImage::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint size = getSize();

	TransparentBlt(hDC,
		(int)pos.x,
		(int)pos.y,
		(int)size.x,
		(int)size.y,
		m_pTex->getDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		RGB(255, 0, 255));
}

void CImage::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}
