#include "framework.h"
#include "CBackGround.h"
#include "CTexture.h"

CBackGround::CBackGround()
{
	setSize(fPoint(3000.f, 1689.f));
	setPos(fPoint(getSize().x / 2.f, getSize().y / 2.f));

	m_pTex = loadTex(L"BossStg1Tex", L"texture\\background\\bossStage.bmp");;
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
	pos = rendPos(pos);

	//TransparentBlt(hDC,
	//	/*(pos.x - size.x / 2.f) + (int)(pos.x - WINSIZEX / 2.f),
	//	(pos.y - size.y / 2.f) + (int)(pos.y - WINSIZEY / 2.f),*/
	//	(int)(pos.x - WINSIZEX / 2.f),
	//	(int)(pos.y - WINSIZEY / 2.f),
	//	(int)WINSIZEX,
	//	(int)WINSIZEY,
	//	m_pTex->getDC(),
	//	(int)(pos.x - WINSIZEX / 2.f),
	//	(int)(pos.y - WINSIZEY / 2.f),
	//	(int)WINSIZEX,
	//	(int)WINSIZEY,
	//	RGB(255, 0, 255));
}
