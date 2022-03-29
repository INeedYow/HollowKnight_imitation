#include "framework.h"
#include "CHUD.h"
#include "CTexture.h"

CHUD::CHUD()
{
	m_pTex = nullptr;
}

CHUD::~CHUD()
{
}

void CHUD::update()
{
}

void CHUD::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

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

void CHUD::setTex(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}

CTexture* CHUD::getTex()
{
	return m_pTex;
}
