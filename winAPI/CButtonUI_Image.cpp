#include "framework.h"
#include "CButtonUI_Image.h"
#include "CTexture.h"

CButtonUI_Image::CButtonUI_Image()
{
	m_pTex = nullptr;
}

CButtonUI_Image::~CButtonUI_Image()
{
}


void CButtonUI_Image::update()
{
}

// TODO
void CButtonUI_Image::render(HDC hDC)
{
	if (nullptr == m_pTex)
	{
		
	}
	else
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
}

void CButtonUI_Image::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}
