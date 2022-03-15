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
	setSize(fPoint(100.f, 100.f));

	CPlayer::eACT act = eACT::IDLE;
	m_ucState = 0;
	m_fSpd = P_SPD;
	m_fJumpSpd = P_JSPD;
	m_fGravity = P_GRAV;
	m_fTimer = 0.f;
	m_iBottomCnt = 0;

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

	if (m_ucState & SP_DIR)
		PLAY(L"Idle_R");
	else
		PLAY(L"Idle_L");

	if (KEY_HOLD(VK_LEFT))
	{
		m_ucState &= ~(SP_DIR);

		if (KEY_NONE(VK_CONTROL))
		{
			pos.x -= m_fSpd * fDT;
			PLAY(L"Walk_L");
		}
		else
		{
			pos.x -= 2 * m_fSpd * fDT;
			PLAY(L"Run_L");
		}
	}
	if (KEY_HOLD(VK_RIGHT))
	{
		m_ucState |= SP_DIR;

		if (KEY_NONE(VK_CONTROL))
		{
			pos.x += m_fSpd * fDT;
			PLAY(L"Walk_R");
		}
		else
		{
			pos.x += 2 * m_fSpd * fDT;
			PLAY(L"Run_R");
		}
	}

	// юс╫ц
	if (KEY_HOLD(VK_UP))
	{

		pos.y -= m_fSpd * fDT;
	}
	if (KEY_HOLD(VK_DOWN))
	{
		pos.y += m_fSpd * fDT;
	}

	setPos(pos);
	getAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	fPoint pos = getPos();

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};

	swprintf_s(bufX, L"x = %d", (int)pos.x);
	swprintf_s(bufY, L"y = %d", (int)pos.y);

	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 60, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufY, (int)wcslen(bufY));

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
