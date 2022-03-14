#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\test.bmp");
	setName(OBJNAME::PLAYER);
	setSize(fPoint(70.f, 70.f));
	m_fSpeed = 300.f;

	createCollider();
	getCollider()->setSize(fPoint(90.f, 120.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();
	createAnim(L"Idle_L", m_pTex, fPoint(0.f, 127.f), fPoint(60.f, 127.f), fPoint(60.f, 0.f), 0.25f, 6);
	createAnim(L"Idle_R", m_pTex, fPoint(0.f, 0.f), fPoint(60.f, 127.f), fPoint(60.f, 0.f), 0.25f, 6);

	createAnim(L"Walk_L", m_pTex, fPoint(0.f, 381.f), fPoint(60.f, 127.f), fPoint(60.f, 0.f), 0.25f, 7);
	createAnim(L"Walk_R", m_pTex, fPoint(0.f, 254.f), fPoint(60.f, 127.f), fPoint(60.f, 0.f), 0.25f, 7);

	createAnim(L"Run_L", m_pTex, fPoint(902.f, 635.f), fPoint(82.f, 127.f), fPoint(-82.f, 0.f), 0.2f, 8);
	createAnim(L"Run_R", m_pTex, fPoint(328.f, 508.f), fPoint(82.f, 127.f), fPoint(82.f, 0.f), 0.2f, 8);

	PLAY(L"Idle_R");

	
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = getPos();

	if (KEY_HOLD(VK_LEFT))
	{
		pos.x -= m_fSpeed * fDT;
		PLAY(L"LeftMove");
	}
	if (KEY_HOLD(VK_RIGHT))
	{
		pos.x += m_fSpeed * fDT;
		PLAY(L"RightMove");
	}
	if (KEY_HOLD(VK_UP))
	{
		pos.y -= m_fSpeed * fDT;
	}
	if (KEY_HOLD(VK_DOWN))
	{
		pos.y += m_fSpeed * fDT;
	}

	setPos(pos);

	if (KEY_ON(VK_SPACE))
	{
		createMissile();
		PLAY(L"LeftHit");
	}

	getAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	componentRender(hDC);
}

void CPlayer::createMissile()
{
	fPoint fpMissilePos = getPos();
	fpMissilePos.x += getSize().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->setPos(fpMissilePos);
	pMissile->setDir(fVec2(1, 0));

	createObj(pMissile, OBJ::MISSILE_PLAYER);
}
