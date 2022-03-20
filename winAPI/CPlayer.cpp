#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CMissile.h"
#include "CAttack.h"
#include "CAI.h"

#include "CState.h"
#include "CState_Idle.h"
#include "CState_Run.h"
#include "CState_Jump.h"
#include "CState_Fall.h"
#include "CState_Slash1.h"
#include "CState_Slash2.h"
#include "CState_Upslash.h"
#include "CState_Downslash.h"
#include "CState_Fire.h"
#include "CState_Focus.h"
#include "CState_Stun.h"

// test
#include "CTest.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\player\\texPlayer.bmp");
	setName(eOBJNAME::PLAYER);
	setSize(fPoint(P_SIZEX, P_SIZEY));

	m_tInfo = {
		5,
		50,
		0,
		P_SPDX,
		P_SPDY,
		0.f,
		0,
		{},
		//0.f
	};
	m_tPrevInfo = {};

	m_pAI = nullptr;
	m_uiCheck = 0;

	createCollider();
	getCollider()->setSize(fPoint(50.f, 108.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

#pragma region createAnimation

	createAnim(L"Idle_R",		m_pTex,	fPoint(0.f, 0.f),			fPoint(60.f, 127.f),		fPoint(60.f, 0.f),			0.25f,	6);
	createAnim(L"Idle_L",		m_pTex,	fPoint(300.f, 127.f),		fPoint(60.f, 127.f),		fPoint(-60.f, 0.f),			0.25f,	6);

	createAnim(L"Run_R",		m_pTex,	fPoint(360.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	12);
	createAnim(L"Run_L",		m_pTex,	fPoint(1262.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	12);

	createAnim(L"Jump_R",		m_pTex,	fPoint(1344.f, 0.f),		fPoint(77.f, 127.f),		fPoint(77.f, 0.f),			0.2f,	6);
	createAnim(L"Jump_L",		m_pTex,	fPoint(1729.f, 127.f),		fPoint(77.f, 127.f),		fPoint(-77.f, 0.f),			0.2f,	6);

	createAnim(L"Fall_R",		m_pTex,	fPoint(1806.f, 0.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	6);
	createAnim(L"Fall_L",		m_pTex,	fPoint(2241.f, 127.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	6);

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.3f,	3);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.3f,	3);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 0.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 127.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	5);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	5);

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.1f,	5);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.1f,	5);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.2f,	5);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.2f,	5);

	createAnim(L"DownSlash_R",	m_pTex,	fPoint(1475.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5);
	createAnim(L"DownSlash_L",	m_pTex,	fPoint(1947.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5);

	createAnim(L"Fire_R",		m_pTex,	fPoint(2065.f, 254.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.07f,	7);
	createAnim(L"Fire_L",		m_pTex,	fPoint(2587.f, 381.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.07f,	7);

	createAnim(L"Focus2Idle_R",	m_pTex,	fPoint(0.f, 508.f),			fPoint(64.f, 127.f),		fPoint(64.f, 0.f),			0.2f,	2);
	createAnim(L"Focus2Idle_L",	m_pTex,	fPoint(64.f, 635.f),		fPoint(64.f, 127.f),		fPoint(-64.f, 0.f),			0.2f,	2);

	createAnim(L"Death_R",		m_pTex,	fPoint(128.f, 508.f),		fPoint(107.f, 127.f),		fPoint(107.f, 0.f),			0.2f,	12);
	createAnim(L"Death_L",		m_pTex,	fPoint(1305.f, 635.f),		fPoint(107.f, 127.f),		fPoint(-107.f, 0.f),		0.2f,	12);

	createAnim(L"Focus_R",		m_pTex,	fPoint(1412.f, 508.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.2f,	10);
	createAnim(L"Focus_L",		m_pTex,	fPoint(2258.f, 635.f),		fPoint(94.f, 127.f),		fPoint(-94.f, 0.f),			0.2f,	10);

#pragma endregion

	PLAY(L"Idle_R");
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

CPlayer* CPlayer::createNormal(fPoint pos)
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;
	pPlayer->setPos(pos);

	CAI* pAI = new CAI;
	pAI->addState(new CState_Idle(eSTATE_PLAYER::IDLE));
	pAI->addState(new CState_Run(eSTATE_PLAYER::RUN));
	pAI->addState(new CState_Jump(eSTATE_PLAYER::JUMP));
	pAI->addState(new CState_Fall(eSTATE_PLAYER::FALL));

	pAI->addState(new CState_Slash1(eSTATE_PLAYER::SLASH1));
	pAI->addState(new CState_Slash2(eSTATE_PLAYER::SLASH2));
	pAI->addState(new CState_Upslash(eSTATE_PLAYER::UPSLASH));
	pAI->addState(new CState_Downslash(eSTATE_PLAYER::DOWNSLASH));

	pAI->addState(new CState_Fire(eSTATE_PLAYER::FIRE));
	pAI->addState(new CState_Focus(eSTATE_PLAYER::FOCUS));

	pAI->addState(new CState_Stun(eSTATE_PLAYER::STUN));

	pAI->setCurState(eSTATE_PLAYER::IDLE);
	pPlayer->setAI(pAI);

	return pPlayer;
}


// �¿� �̵��� fSpdX�� -1 ���ؼ� �ϸ� ��Ȳ���� �ִϸ��̼� �ϱ� ���ҵ�
void CPlayer::playAnim(const wstring& keyWord)
{
	wstring strKey = keyWord;

	if (m_uiCheck & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
	//if (strKey == L"\0" && SP_STOPANIM)
	//{
	//	fPoint pos = getPos();

	//	if (m_tPrevInfo.uiPrevHP < m_tInfo.uiHP)
	//		strKey = L"Stun";
	//	else
	//	{
	//		if (m_tPrevInfo.fpPrevPos == pos)
	//			strKey = L"Idle";
	//		else
	//			strKey = L"Run";

	//		if (m_tPrevInfo.fpPrevPos.y > pos.y)
	//			strKey = L"Jump";
	//		else if (m_tPrevInfo.fpPrevPos.y < pos.y)
	//			strKey = L"Fall";

	//		// �̷��� �� �Ÿ� Ű�Է����� �ϴ� �Ŷ� �ٸ� �� ���� ��
	//		//if (m_uiCheck & SP_SLASH1)
	//		//	strKey = L"Slash1";
	//		//else if (m_uiCheck & SP_SLASH2)
	//		//	strKey = L"Slash2";
	//		//else if (m_uiCheck & SP_UPSLASH)
	//		//	strKey = L"UpSlash";
	//		//else if (m_uiCheck & SP_DOWNSLASH)
	//		//	strKey = L"DownSlash";
	//		//else if (m_uiCheck & SP_FIRE)
	//		//	strKey = L"Fire";
	//		//else if (m_uiCheck & SP_FOCUS)
	//	}
	//}
	//addDirAndPlay(strKey);
}

void CPlayer::addDirAndPlay(const wstring& keyWord)
{
	wstring strKey = keyWord;

	if (m_uiCheck & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

// TODO : ���� �ִϸ��̼� �غ��۱��� �ݺ��ż� ���� ���� ���� �����ϸ� ���ڿ�������
	// �ִϸ��̼� �ݺ� ���� ����
// TODO : �� ���� Ű ������ �� ������
void CPlayer::update()
{

	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	////////////////////////////
	// �ӽ� // ȸ���׽�Ʈ
	// T Y U I 
	// G H J
	fPoint pos = getPos();
	if (KEY_ON('Q'))
	{
		createRotTester();
	}
	// �ӽ� // Ÿ�� ���
	if (pos.y > 1518.f)
	{
		pos.y = 1518.f;
		m_uiCheck &= ~(SP_AIR);
		m_uiCheck &= ~(SP_GODOWN);
		//changeAIState(m_pAI, eSTATE_PLAYER::IDLE);
		m_tInfo.fGravity = 0.f;
	}
	setPos(pos);
	///////////////////////////

	//playAnim();					// 
	if (nullptr != m_pAI)
		m_pAI->update(m_uiCheck);
	if (nullptr != getAnimator())
		getAnimator()->update();
	
	renewPrevInfo(getPos());			// anim ��� �� ���� ��Ȳ ����
}

void CPlayer::render(HDC hDC)
{
	if (g_bDebug)
		printInfo(hDC);

	componentRender(hDC);
	
}

void CPlayer::setAI(CAI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CPlayer::setPlayerInfo(const tPlayerInfo& info)
{
	m_tInfo = info;
}

const tPlayerInfo& CPlayer::getPlayerInfo()
{
	return m_tInfo;
}

void CPlayer::setCheck(UINT chk, bool isOn)
{
	if (isOn)
		m_uiCheck |= chk;
	else
		m_uiCheck &= ~(chk);
}

bool CPlayer::isCheck(UINT chk)
{
	return m_uiCheck & chk;
}

UINT CPlayer::getCheck()
{
	return m_uiCheck;
}

void CPlayer::collisionKeep(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::MISSILE_MONSTER:
	case eOBJNAME::SHIELD:
	case eOBJNAME::BOSS:
	{
		if (!(m_uiCheck & SP_NODMG))
		{
			m_tInfo.uiHP--;
			m_tInfo.fvKnockBackDir = (getPos() - pTarget->getPos());
			m_tInfo.uiSoul += 10;
			changeAIState(m_pAI, eSTATE_PLAYER::STUN);
		}
		break;
	}
	case eOBJNAME::ATTACK:
	{
		// ���ݵ� attack�� ���� �÷��̾� ������ �ϳ�
		// ((CAttack*)pOther->getOwner())->getOwner()->getName()
		
		break;
	}
	}
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	//�� �浹
	case eOBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
		{
			if (m_uiCheck & SP_GODOWN)
			{
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiCheck & SP_AIR)
					m_uiCheck &= ~(SP_AIR);
				m_tInfo.iBottomCnt++;
				m_tInfo.fGravity = 0.f;
			}
			break;
		}
		case eDIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_tInfo.fSpdX = 0.f;
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_tInfo.fSpdX = 0.f;
			break;
		}
		case eDIR::BOTTOM:	// �Ӹ� ��
			m_tInfo.fSpdY = 0.f;
			break;
		}
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
			if (--m_tInfo.iBottomCnt <= 0)
			{
				m_uiCheck |= SP_AIR;
				m_uiCheck |= SP_GODOWN;
				m_tInfo.fGravity = 0.f;
			}
			break;
		}
		break;
	}
}

void CPlayer::createMissile()
{
	fPoint mPos = getPos();
	float mDir = 1.f;

	CMissile* pMissile = new CMissile;

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += getSize().x / 2.f;
		mDir = 1.f;
	}
	else
	{
		mPos.x -= getSize().x / 2.f;
		mDir = -1.f;
	}
	pMissile->setPos(fPoint(mPos.x, mPos.y));
	pMissile->setSize(fPoint(30.f, 30.f));
	pMissile->getCollider()->setSize(fPoint(30.f, 30.f));
	pMissile->setDir(fVec2(mDir, 0.f));
	pMissile->setName(eOBJNAME::MISSILE_PLAYER);
	pMissile->setSpeed(400.f);

	createObj(pMissile, eOBJ::MISSILE_PLAYER);
}

void CPlayer::renewPrevInfo(fPoint pos)
{
	m_tPrevInfo.fpPrevPos = pos;
	m_tPrevInfo.uiPrevHP = m_tInfo.uiHP;
}

/////////////////////////////////////// test
void CPlayer::createRotTester()
{	
	fPoint mPos = getPos();

	CTest* pTest = new CTest;

	if (m_uiCheck & SP_DIR)
	{
		pTest->setDir(fPoint(1.f, 0.f));
		mPos.x = -100.f;
		pTest->setRot(true);
	}
	else
	{
		pTest->setDir(fPoint(-1.f, 0.f));
		mPos.x = 100.f;
		pTest->setRot(false);
	}
	pTest->setOwner(this);
	//pTest->setPos(fPoint(mPos.x, mPos.y));
	pTest->setOffset(fPoint(mPos.x, 0.f));
	pTest->setName(eOBJNAME::TEST);

	createObj(pTest, eOBJ::TEST);
}
///////////////////////////////////////////////

void CPlayer::printInfo(HDC hDC)
{
	fPoint pos = getPos();

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufGrav[255] = {};

	wchar_t bufHP[255] = {};
	wchar_t bufSoul[255] = {};

	// state �κи� �ű��
	LPCWSTR	szAct = L"";
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 60, szAct, (int)wcslen(szAct));
	// ����

	swprintf_s(bufX, L"x = %d", (int)pos.x);
	swprintf_s(bufY, L"y = %d", (int)pos.y);
	swprintf_s(bufGrav, L"grav = %f", m_tInfo.fGravity);

	swprintf_s(bufHP, L"HP = %d", (int)m_tInfo.uiHP);
	swprintf_s(bufSoul, L"Soul = %d", (int)m_tInfo.uiSoul);

	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 90, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 105, bufGrav, (int)wcslen(bufGrav));

	TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 75, bufHP, (int)wcslen(bufHP));
	TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 90, bufSoul, (int)wcslen(bufSoul));
}

// Slash�� ���ĵ� �ɵ�
void CPlayer::firstSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEX));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += PSLASH_OFFSETX;
		pAttack->setDir(eDIR::RIGHT);
	}
	else
	{
		mPos.x -= PSLASH_OFFSETX;
		pAttack->setDir(eDIR::LEFT);
	}

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);
	
	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::secondSlash()
{
}

void CPlayer::upSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->setOwner(this);

	mPos.y -= PSLASH_OFFSETY;
	pAttack->setDir(eDIR::TOP);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);

	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::downSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->setOwner(this);

	mPos.y += PSLASH_OFFSETY;
	pAttack->setDir(eDIR::BOTTOM);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);

	createObj(pAttack, eOBJ::ATTACK);
}