#include "framework.h"
#include "CSpear.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CBoss_Markoth.h"
#include "CEffect.h"

#include "SelectGDI.h"

CSpear::CSpear()
{
	setSize(fPoint(SPR_SIZEX, SPR_SIZEY));
	setName(eOBJNAME::MISSILE_MONSTER);
	setTimer(0.f);
	setDir(fVec2(0.f, 0.f));

	getCollider()->setShape(eSHAPE::RECT);

	
	m_uiStep = 0;
	m_fTheta = 0.f;
	m_fSpd = 1.f;
	m_bActive = true;

	m_pMemTex = nullptr;
}

CSpear::~CSpear()
{
}

void CSpear::update()
{
	fPoint pos = getPos();
	float timer = getTimer();
	fPoint destPos = gameGetPlayer()->getPos();

	fVec2 dir;

	float distX, distY;

	timer -= fDT;
	
	switch (m_uiStep)
	{

	case 0:
	{	// init
		distX = destPos.x - pos.x;
		distY = destPos.y - pos.y;
		m_fTheta = (float)atan2(distY, distX);
		
		//timer = m_fSpd == B_SPR_SPD_1P ? 0.65f : 0.5f;
		timer = 0.65f;
		setSpeed(m_fSpd * 0.1f);
		m_uiStep++;

		/*CEffect* pEff = new CEffect;
		pEff->load(L"Effect_dream", L"texture\\effect\\dream_catcher_mini.bmp");
		pEff->setDuration(1.f);
		pEff->createAnim(L"effect_dream", pEff->getTex(),
			fPoint(0, 0), fPoint(61, 61), fPoint(61, 0), 0.05f, 13, false);
		pEff->setPos(pos);
		pEff->PLAY(L"effect_dream");
		createObj(pEff, eOBJ::EFFECT);*/

		CSoundManager::getInst()->addSound(L"spear_appear", L"sound\\boss\\spear_appear.wav");
		CSoundManager::getInst()->play(L"spear_appear", 0.1f);

		break;
	}

	case 1:
	{	// pull and aim
		distX = destPos.x - pos.x;
		distY = destPos.y - pos.y;
		m_fTheta = (float)atan2(distY, distX);

		dir = pos - destPos;
		setDir(dir);

		if (timer < 0.f)
		{
			//timer = m_fSpd == B_SPR_SPD_1P ? 0.65f : 0.5f;
			timer = 0.65f;
			setSpeed(0.f);
			m_uiStep++;
		}
		break;
	}

	case 2:
	{	// hold and aim
		distX = destPos.x - pos.x;
		distY = destPos.y - pos.y;
		m_fTheta = (float)atan2(distY, distX);

		if (timer < 0.f)
		{
			CSoundManager::getInst()->addSound(L"spear_shoot", L"sound\\boss\\spear_shoot.wav");
			CSoundManager::getInst()->play(L"spear_shoot", 0.1f);

			timer = 1.f;
			setSpeed(m_fSpd);
			setDir(destPos - pos);
			m_uiStep++;
		}
		break;
	}
	
	case 3:
	{	//shoot						
		if (timer < 0.f)			// 발사후 일정 시간 지나고
		{
			m_uiStep++;
		}
		break;
	}

	case 4:
	{	// 카메라 범위 나가면 비활성화
		fPoint randPos = rendPos(pos);
		if (randPos.x < (float)(SPR_SIZEX / -2.f) || randPos.x > (float)(WINSIZEX + SPR_SIZEX / 2.f) ||
			randPos.y < (float)(SPR_SIZEY / -2.f) || randPos.y > (float)(WINSIZEX + SPR_SIZEY / 2.f))
		{
			m_uiStep++;
			m_bActive = false;
			pos = fPoint(-444.f, -444.f);
			setSpeed(0.f);
		}
		break;
	}
	default:
	{
		if (m_bActive)
		{
			pos = getRandPos();
			m_uiStep = 0;
		}
		break;
	}
	}
	
	dir.normalize();
	pos.x += getSpeed() * getDir().x * fDT;
	pos.y += getSpeed() * getDir().y * fDT;
	setTimer(timer);
	setPos(pos);
}


void CSpear::render(HDC hDC)
{
	componentRender(hDC, m_fTheta);
}

void CSpear::collisionEnter(CCollider* pOther)
{
}

void CSpear::collisionKeep(CCollider* pOther)
{
}

void CSpear::setSpd(float spd)
{
	m_fSpd = spd;
}

void CSpear::setActive(bool isOn)
{
	m_bActive = isOn;
}

void CSpear::createMemTex(const wstring& texName, UINT sizeX, UINT sizeY)
{
	m_pMemTex = CResourceManager::getInst()->createTexture(texName, sizeX, sizeY);
}


bool CSpear::isActive()
{
	return m_bActive;
}


fPoint CSpear::getRandPos()
{
	fPoint pos = CCameraManager::getInst()->getFocus();

	int max, min, random;
	
	random = rand() % 2;					// x 좌표 설정
	if (random)
	{	// left
		max = (int)(pos.x - WINSIZEX / 4.f);
		min = (int)(pos.x - WINSIZEX / 2.f);
	}
	else
	{	// right
		max = (int)(pos.x + WINSIZEX / 2.f);
		min = (int)(pos.x + WINSIZEX / 4.f);
	}
	pos.x = (float)(rand() % (max - min + 1) + min);

	random = rand() % 2;					// y 좌표 설정
	if (random)
	{	// left
		max = (int)(pos.y - WINSIZEY / 4.f);
		min = (int)(pos.y - WINSIZEY / 2.f);
	}
	else
	{	// right
		max = (int)(pos.y + WINSIZEY / 2.f);
		min = (int)(pos.y + WINSIZEY / 4.f);
	}
	pos.y = (float)(rand() % (max - min + 1) + min);

	return fPoint(pos.x, pos.y);
}