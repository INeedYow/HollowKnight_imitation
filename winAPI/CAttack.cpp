#include "framework.h"
#include "CAttack.h"
#include "CPlayer.h"

CAttack::CAttack()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::ATTACK);

	m_pOwner = nullptr;
	m_eDir = eDIR::NONE;
	m_fDura = 0.1f;
	//m_uiDmg = 1;

	// ÀÓ½Ã TODO
	m_pTex = loadTex(L"Attack_Player", L"texture\\attack\\slash.bmp");

	createCollider();
	getCollider()->setSize(fPoint(30.f, 30.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

	createAnim(L"Slash_player_R", m_pTex,
		fPoint(516.f, 0.f), fPoint(151.f, 129.f), fPoint(151.f, 0.f), 0.1f, 2, false);
	createAnim(L"Slash_player_L", m_pTex,
		fPoint(667.f, 129.f), fPoint(151.f, 129.f), fPoint(-151.f, 0.f), 0.1f, 2, false);

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
	{
		tPlayerInfo info = ((CPlayer*)pOwner)->getPlayerInfo();

		switch (pTarget->getName())
		{
		case eOBJNAME::BOSS:
		case eOBJNAME::MONS_BEETLE:
		{	// soul È¹µæ·®
			info.fvKnockBackDir = (pOwner->getPos() - pTarget->getPos());
			info.uiSoul += 20;
			if (info.uiSoul > 100)
				info.uiSoul = 100;

			if (m_eDir == eDIR::BOTTOM)
			{
				((CPlayer*)pOwner)->setCheck(SP_DWSLASH, true);
				changeMyState(((CPlayer*)pOwner)->getAI(), eSTATE_PLAYER::JUMP);
			}
			break;
		}
		}
		
		((CPlayer*)pOwner)->setPlayerInfo(info);
	}
}
