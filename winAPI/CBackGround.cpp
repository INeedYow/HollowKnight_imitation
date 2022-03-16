#include "framework.h"
#include "CBackGround.h"
#include "CTexture.h"

CBackGround::CBackGround()
{
	setSize(fPoint(0.f, 0.f));
	setPos(fPoint(0.f, 0.f));

	m_pTex = nullptr;
	m_bMove = false;
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
	fPoint pos = getPos();
	fPoint size = getSize();
	fPoint renderPos = rendPos(pos);

	if (m_bMove)
	{
		renderPos = pos + (renderPos - pos) / 5;

		BitBlt(hDC,
			0,0,
			m_pTex->getBmpWidth(),
			m_pTex->getBmpHeight(),
			m_pTex->getDC(),
			(int)renderPos.x,
			(int)renderPos.y,
			SRCCOPY);
	}
	else
	{
		TransparentBlt(hDC,
			0, 0,
			m_pTex->getBmpWidth() / 2,
			m_pTex->getBmpHeight() / 2,
			m_pTex->getDC(),
			(int)renderPos.x,
			(int)renderPos.y,
			(int)WINSIZEX,
			(int)WINSIZEY,
			RGB(255, 0, 255));
	}

}

void CBackGround::setMove(bool isMove)
{
	m_bMove = isMove;
}

void CBackGround::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
}