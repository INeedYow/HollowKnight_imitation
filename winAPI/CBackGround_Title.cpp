#include "framework.h"
#include "CBackGround_Title.h"
#include "CTexture.h"

CBackGround_Title::CBackGround_Title()
{
	m_pTex = loadTex(L"BG_title", L"texture\\background\\title.bmp");
	setSize(fPoint(WINSIZEX, WINSIZEY));
	setPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

CBackGround_Title::~CBackGround_Title()
{
	
}

CBackGround_Title* CBackGround_Title::clone()
{
	return new CBackGround_Title(*this);
}

void CBackGround_Title::update()
{
	
}

void CBackGround_Title::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint size = getSize();

	BitBlt(hDC,
		0, 0,
		WINSIZEX, WINSIZEY,
		m_pTex->getDC(),
		0, 0, 
		SRCCOPY);
}
