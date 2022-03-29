#include "framework.h"
#include "CAttack.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CEffect.h"

CAttack::CAttack()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::ATTACK);

	m_pOwner = nullptr;
	m_eDir = eDIR::NONE;
	m_fDura = 0.1f;
	//m_uiDmg = 1;

	// 임시 TODO
	m_pTex = loadTex(L"Attack_Player", L"texture\\attack\\slash.bmp");

	createCollider();
	getCollider()->setSize(fPoint(30.f, 30.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

	
	

	createAnim(L"UpSlash_player_R", m_pTex,
		fPoint(0.f, 0.f), fPoint(129.f, 151.f), fPoint(129.f, 0.f), 0.1f, 2, false);
	createAnim(L"UpSlash_player_L", m_pTex,
		fPoint(129.f, 151.f), fPoint(129.f, 151.f), fPoint(-129.f, 0.f), 0.1f, 2, false);

	createAnim(L"DownSlash_player_R", m_pTex,
		fPoint(258.f, 0.f), fPoint(129.f, 151.f), fPoint(129.f, 0.f), 0.1f, 2, false);
	createAnim(L"DownSlash_player_L", m_pTex,
		fPoint(387.f, 151.f), fPoint(129.f, 151.f), fPoint(-129.f, 0.f), 0.1f, 2, false);

	PLAY(L"Slash_player_R");
}

CAttack::~CAttack()
{
}

CAttack* CAttack::clone()
{
	return new CAttack(*this);
}

void CAttack::update()
{
	m_fDura -= fDT;

	if (m_fDura < 0.f)
		deleteObj(this);

	if (nullptr != getAnimator())
		getAnimator()->update();
}

void CAttack::render(HDC hDC)
{
	componentRender(hDC);
}

void CAttack::setDir(eDIR dir)
{
	m_eDir = dir;
}

void CAttack::setDura(float dura)
{
	m_fDura = dura;
}

//void CAttack::setDmg(UINT dmg)
//{
//	m_uiDmg = dmg;
//}

void CAttack::setOwner(CObject* pOwner)
{
	m_pOwner = pOwner;
}

void CAttack::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

CObject* CAttack::getOwner()
{
	return m_pOwner;
}

CTexture* CAttack::getTex()
{
	return m_pTex;
}

void CAttack::collisionEnter(CCollider* pOther)
{
	CObject* pOwner = getOwner();
	CObject* pTarget = pOther->getOwner();

	if (eOBJNAME::PLAYER == pOwner->getName())
	{	// 플레이어의 atk
		tPlayerInfo info = ((CPlayer*)pOwner)->getPlayerInfo();

		switch (pTarget->getName())
		{
		case eOBJNAME::BOSS:
		case eOBJNAME::MONS_BEETLE:
		case eOBJNAME::MONS_MUSH:
		case eOBJNAME::MONS_BEE:
		{	
			fPoint pos = (getPos() + pOther->getPos()) / 2.f;

			CEffect* pEff = new CEffect;
			pEff->load(L"nail_hit_effect", L"texture\\effect\\nail_hit_effect.bmp");
			pEff->setDuration(0.4f);

			pEff->createAnim(L"nail_hit_effect", pEff->getTex(),
				fPoint(0, 0), fPoint(243, 155), fPoint(243, 0), 0.1f, 4, false);

			pEff->setPos(pos);
			pEff->PLAY(L"nail_hit_effect");
			createObj(pEff, eOBJ::EFFECT);

			CSoundManager::getInst()->addSound(L"enemy_damage", L"sound\\player\\enemy_damage.wav");
			CSoundManager::getInst()->play(L"enemy_damage", 0.1f);

			if (m_eDir == eDIR::BOTTOM && !((CMonster*)pOther->getOwner())->isCheck(SM_DEATH))
			{
				((CPlayer*)pOwner)->setCheck(SP_DWSLASH, true);
				changeMyState(((CPlayer*)pOwner)->getAI(), eSTATE_PLAYER::JUMP);
			}

			if (((CMonster*)pTarget)->isCheck(SM_DEATH)) break;			// 죽은 상태인 경우 이펙트랑 사운드만 출력하고 그만

			info.fvKnockBackDir = (pOwner->getPos() - pTarget->getPos());
			info.fKnockBackTimer = P_KB_TIMER;

			// soul 획득량
			info.uiSoul += 20;
			if (info.uiSoul > 100)
				info.uiSoul = 100;

			
			break;
		}
		case eOBJNAME::SHIELD:
		{
			fPoint pos = (getPos() + pOther->getPos()) / 2.f;

			info.fvKnockBackDir = (pOwner->getPos() - pTarget->getPos());
			info.fKnockBackTimer = P_KB_TIMER;

			CEffect* pEff = new CEffect;
			pEff->load(L"effect_paring", L"texture\\effect\\effect_paring.bmp");
			pEff->setDuration(0.4f);

			pEff->createAnim(L"effect_paring", pEff->getTex(),
				fPoint(0, 0), fPoint(373, 278), fPoint(373, 0), 0.13f, 3, false);

			pEff->setPos(pos);
			pEff->PLAY(L"effect_paring");
			createObj(pEff, eOBJ::EFFECT);

			CSoundManager::getInst()->addSound(L"hero_parry", L"sound\\player\\hero_parry.wav");
			CSoundManager::getInst()->play(L"hero_parry", 0.1f);

			break;
		}
		}
		

		((CPlayer*)pOwner)->setPlayerInfo(info);
	}
}
