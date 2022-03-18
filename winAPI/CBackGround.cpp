#include "framework.h"
#include "CBackGround.h"
#include "CTexture.h"

CBackGround::CBackGround()
{
	setSize(fPoint(0.f, 0.f));
	setPos(fPoint(0.f, 0.f));
	setName(eOBJNAME::BACKGROUND);

	m_pTex = nullptr;
}

CBackGround::~CBackGround()
{
}

CBackGround* CBackGround::clone()
{
	return new CBackGround(*this);
}

void CBackGround::update()
{
}

void CBackGround::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

	fPoint pos = getPos();
	fPoint size = getSize();
	fPoint renderPos = rendPos(pos);

	renderPos = pos + (renderPos - pos) / 5;

	BitBlt(hDC,
		(int)renderPos.x,
		(int)renderPos.y,
		(int)size.x,
		(int)size.y,
		m_pTex->getDC(),
		(int)0,
		(int)0,
		SRCCOPY);
}

void CBackGround::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}