#include "framework.h"
#include "CFrontGround.h"
#include "CTexture.h"

CFrontGround::CFrontGround()
{
	setSize(fPoint(0.f, 0.f));
	setPos(fPoint(0.f, 0.f));
	setName(eOBJNAME::FRONTGROUND);

	m_pTex = nullptr;
}

CFrontGround::~CFrontGround()
{
}

void CFrontGround::update()
{
}

void CFrontGround::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

	fPoint camPos = getCamPos();

	TransparentBlt(hDC,
		(int)(0),
		(int)(0),
		(int)WINSIZEX,
		(int)WINSIZEY,
		m_pTex->getDC(),
		(int)(camPos.x - WINSIZEX * 0.5f),
		(int)(camPos.y - WINSIZEY * 0.5f),
		(int)WINSIZEX,
		(int)WINSIZEY,
		RGB(255,0,255));
}

void CFrontGround::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}
