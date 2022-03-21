#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CTexture.h"

CMissile* CMissile::clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	setSize(fPoint(30.f, 30.f));
	setName(eOBJNAME::MISSILE_MONSTER);
	m_fvDir = fVec2(0, 0);
	m_fSpeed = 0.f;
	m_fTimer = 0.f;

	// 역시 임시
	m_pTex = loadTex(L"Missile_player", L"texture\\attack\\missile_player.bmp");

	createCollider();
	getCollider()->setSize(fPoint(30.f, 30.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

	createAnim(L"Missile_player_R", m_pTex,
		fPoint(0.f, 0.f), fPoint(254.f, 108.f), fPoint(254.f, 0.f), 0.15f, 4, false);
	createAnim(L"Missile_player_L", m_pTex,
		fPoint(762.f, 108.f), fPoint(254.f, 108.f), fPoint(-254.f, 0.f), 0.15f, 4, false);
}


CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint pos = getPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	m_fTimer += fDT;

	if (m_fTimer > 8.f)
		deleteObj(this);

	if (nullptr != getAnimator())
		getAnimator()->update();

	setPos(pos);
}

void CMissile::render(HDC hDC)
{
	componentRender(hDC);
}

void CMissile::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CMissile::setDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::setTimer(float timer)
{
	m_fTimer = timer;
}

void CMissile::setSpeed(float spd)
{
	m_fSpeed = spd;
}

void CMissile::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

CTexture* CMissile::getTex()
{
	return m_pTex;
}

float CMissile::getSpeed()
{
	return m_fSpeed;
}

float CMissile::getTimer()
{
	return m_fTimer;
}

fVec2 CMissile::getDir()
{
	return m_fvDir;
}

void CMissile::collisionEnter(CCollider* pOther)
{
	CObject* pOtherObj = pOther->getOwner();

	if (eOBJNAME::MISSILE_PLAYER == getName())
	{	// 플레이어 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::MONSTER:
		case eOBJNAME::BOSS:
		case eOBJNAME::TILE:
		{
			// TODO 이펙트 생성
			break;
		}

		}
	}
	else if (eOBJNAME::MISSILE_MONSTER == getName())
	{	// 몬스터의 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::PLAYER:
		case eOBJNAME::TILE:
		{
			// TODO 이펙트 생성
			break;
		}

		}
	}
}

void CMissile::collisionKeep(CCollider* pOther)
{
	CObject* pOtherObj = pOther->getOwner();

	if (eOBJNAME::MISSILE_PLAYER == getName())
	{	// 플레이어 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::MONSTER:
		case eOBJNAME::BOSS:
		case eOBJNAME::TILE:
		{
			//deleteObj(this);
			// TODO 이펙트 생성
			break;
		}

		}
	}
	else if (eOBJNAME::MISSILE_MONSTER == getName())
	{	// 몬스터의 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::PLAYER:
		case eOBJNAME::TILE:
		{
			deleteObj(this);
			// TODO 이펙트 생성
			break;
		}

		}
	}
}
