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
	m_pTex = loadTex(L"PlayerTex", L"texture\\Animation_Player.bmp");
	setName(OBJNAME::PLAYER);
	setSize(fPoint(70.f, 70.f));
	m_fSpeed = 300.f;

	createCollider();
	getCollider()->setSize(fPoint(40.f, 40.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();
	createAnim(L"LeftNone",		m_pTex, fPoint(0.f, 0.f),		fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.5f,	2);
	createAnim(L"RightNone",	m_pTex, fPoint(0.f, 70.f),		fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.5f,	2);
	createAnim(L"LeftMove",		m_pTex, fPoint(0.f, 140.f),		fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.25f,	3);
	createAnim(L"RightMove",	m_pTex, fPoint(0.f, 210.f),		fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.25f,	3);
	createAnim(L"LeftHit",		m_pTex, fPoint(140.f, 0.f),		fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.25f,	1);
	createAnim(L"RightHit",		m_pTex, fPoint(140.f, 70.f),	fPoint(70.f, 70.f),		fPoint(70.f, 0.f),		0.25f,	1);
	PLAY(L"LeftNone");

	CAnimation* pAni;
	pAni = getAnimator()->findAnimation(L"LeftMove");
	pAni->getFrame(1).fpOffset = fPoint(0.f, -20.f);
	pAni = getAnimator()->findAnimation(L"RightMove");
	pAni->getFrame(1).fpOffset = fPoint(0.f, -20.f);
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
