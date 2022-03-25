#include "framework.h"
#include "CSpear.h"
#include "CTexture.h"
#include "CPlayer.h"

#include "SelectGDI.h"

CSpear::CSpear()
{
	setSize(fPoint(30.f, 30.f));
	setName(eOBJNAME::MISSILE_MONSTER);
	setTimer(0.f);
	setDir(fVec2(0.f, 0.f));

	getCollider()->setShape(eSHAPE::RECT);
	getCollider()->setSize(fPoint(30.f, 30.f));

	m_uiStep = 0;
	m_fTheta = 0.f;
	m_fSpd = 1.f;
	m_fpHead = {};
}

CSpear::~CSpear()
{
}

// TODO 
// 마젠타 지우는 방법
// mask 인자가 지우는 비트맵?
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
		
		timer = 1.2f;
		setSpeed(m_fSpd * 0.5f);
		m_uiStep++;

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
			timer = 0.8f;
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
			setSpeed(m_fSpd);
			setDir(destPos - pos);
			m_uiStep++;
		}
		break;
	}
	default:
	{
		
		break;
	}
	// shoot
	}
	
	dir.normalize();
	pos.x += getSpeed() * getDir().x * fDT;
	pos.y += getSpeed() * getDir().y * fDT;
	setTimer(timer);
	setPos(pos);

	pos = rendPos(pos);

	// step 조건 왜 안먹어
	if (m_uiStep == 3 && 
		pos.x < -300.f || pos.x > WINSIZEX + 300.f ||
		pos.y < -300.f || pos.y > WINSIZEY + 300.f)
	{	// 재활용
		m_uiStep = 0;
		setRandPos();
	}
}


// TODO
void CSpear::render(HDC hDC)
{
	//componentRender(hDC);
	//////////////////////////////
	fPoint pos = getPos();
	fPoint size = { 362.f, 83.f };
	
	

	POINT pThreeArr[3];
	pos = rendPos(pos);
	SelectGDI font(hDC, eFONT::COMIC24);
	wchar_t b[255] = {};
	swprintf_s(b, L"theta %f", m_fTheta);
	TextOutW(hDC, (int)pos.x - 300, (int)pos.y + 100, b, (int)wcslen(b));
	
	fPoint arr[3] = {
		fPoint(-size.x / 2.f, -size.y / 2.f),
		fPoint(size.x / 2.f, -size.y / 2.f),
		fPoint(-size.x / 2.f,  size.y / 2.f),
	};
	
	for (int i = 0; i < 3; i++)
	{
		pThreeArr[i].x = (LONG)(arr[i].x * cos(m_fTheta) - arr[i].y * sin(m_fTheta));
		pThreeArr[i].y = (LONG)(arr[i].x * sin(m_fTheta) + arr[i].y * cos(m_fTheta));
	}

	
	for (int i = 0; i < 3; i++)
	{
		pThreeArr[i].x += (LONG)pos.x;
		pThreeArr[i].y += (LONG)pos.y;
	}

	PlgBlt(hDC,
		pThreeArr,
		CMissile::getTex()->getDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		NULL,
		0, 0);
	/*SetColorAdjustment();*/
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

void CSpear::setRandPos()
{
	fPoint pos = CCameraManager::getInst()->getFocus();
	iPoint maxArea = { (int)(WINSIZEX / 2) ,(int)(WINSIZEY / 2) };
	iPoint minArea = { (int)(WINSIZEX / 4) ,(int)(WINSIZEY / 4) };
	iPoint randPos;

	randPos.x = rand() % (maxArea.x - minArea.x + 1) + minArea.x;
	randPos.y = rand() % (maxArea.y - minArea.y + 1) + minArea.y;

	if (rand() % 2)
		pos.x -= randPos.x;
	else
		pos.x += randPos.x;

	if (rand() % 2)
		pos.y -= randPos.y;
	else
		pos.y += randPos.y;

	setPos(fPoint(pos.x, pos.y));
}
