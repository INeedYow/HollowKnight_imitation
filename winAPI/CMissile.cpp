#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CEffect.h"

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

	m_pTex = nullptr;

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();
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
	fPoint pos = getPos();

	if (eOBJNAME::MISSILE_PLAYER == getName())
	{	// 플레이어 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::MONS_BEETLE:
		case eOBJNAME::MONS_BEE:
		case eOBJNAME::MONS_MUSH:
		case eOBJNAME::BOSS:
		{
			CSoundManager::getInst()->addSound(L"hero_thorn_counter", L"sound\\player\\hero_thorn_counter.wav");
			CSoundManager::getInst()->play(L"hero_thorn_counter", 0.1f);
			break;
		}
		case eOBJNAME::WALL:
		{
			
			if (pOther->getSize().x >= 300.f)
				deleteObj(this);
			break;
		}

		}
	}
	else if (eOBJNAME::MISSILE_MONSTER == getName())
	{	// 몬스터의 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::PLAYER:
		{
			break;
		}
		case eOBJNAME::WALL:
		{
			CEffect* pEff = new CEffect;
			pEff->load(L"Effect_enemyMsl_sidepop", L"texture\\effect\\enemy_missilesidePop.bmp");
			pEff->setDuration(0.4f);

			if (isLeftColl(getCollider(), pOther))
			{
				pEff->createAnim(L"Effect_enemyMsl_sidepop", pEff->getTex(),
					fPoint(0, 87), fPoint(505, 87), fPoint(-101, 0), 0.08f, 5, false);
			}
			else
			{
				pEff->createAnim(L"Effect_enemyMsl_sidepop", pEff->getTex(),
					fPoint(0, 0), fPoint(101, 87), fPoint(101, 0), 0.08f, 5, false);
			}
			pEff->setPos(pos);
			pEff->PLAY(L"Effect_enemyMsl_sidepop");
			createObj(pEff, eOBJ::EFFECT);

			CSoundManager::getInst()->addSound(L"orb_break", L"sound\\monster\\orb_break.wav");
			CSoundManager::getInst()->play(L"orb_break", 0.1f);

			break;
		}
		case eOBJNAME::GROUND:
		{
			CEffect* pEff = new CEffect;
			pEff->load(L"Effect_enemyMsl_pop", L"texture\\effect\\enemy_missilePop.bmp");
			pEff->setDuration(0.42f);

			if (getCollider()->getPos().y < pOther->getPos().y)
			{
				pEff->createAnim(L"Effect_enemyMsl_pop", pEff->getTex(),
					fPoint(0, 0), fPoint(88, 103), fPoint(88, 0), 0.07f, 6, false);
			}
			else 
			{
				pEff->createAnim(L"Effect_enemyMsl_pop", pEff->getTex(),
					fPoint(440, 103), fPoint(88, 103), fPoint(-88, 0), 0.07f, 6, false);
			}
			pEff->setPos(pos);
			pEff->PLAY(L"Effect_enemyMsl_pop");
			createObj(pEff, eOBJ::EFFECT);

			CSoundManager::getInst()->addSound(L"orb_break", L"sound\\monster\\orb_break.wav");
			CSoundManager::getInst()->play(L"orb_break", 0.1f);

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
		case eOBJNAME::MONS_BEETLE:
		case eOBJNAME::BOSS:
		{
			break;
		}
		}
	}
	else if (eOBJNAME::MISSILE_MONSTER == getName())
	{	// 몬스터의 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::PLAYER:
		case eOBJNAME::GROUND:
		case eOBJNAME::WALL:
		{
			deleteObj(this);
			break;
		}

		}
	}
}
