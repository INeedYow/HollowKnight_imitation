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

	/*TransparentBlt(hDC,
		)*/
}

void CImage::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}
