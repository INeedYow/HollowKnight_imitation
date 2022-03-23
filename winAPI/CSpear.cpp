#include "framework.h"
#include "CSpear.h"
#include "CTexture.h"

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
	m_fSpdMax = 1.f;
}

CSpear::~CSpear()
{
}

// TODO Spear의 head를 플레이어한테 어떻게 맞추지
// // 처음 좌표 구분해서?
// 마젠타 지우는 방법
// mask 인자가 지우는 비트맵?
void CSpear::update()
{
	fPoint pos = getPos();
	float timer = getTimer();

	fPoint camPos;
	fPoint dist;
	float distance;
	fVec2 dir;

	timer -= fDT;

	switch (m_uiStep)
	{
	case 0:
	{	// init
	/*	camPos = getCamPos();
		dist = camPos - pos;
		distance = (float)(dist.y * dist.y) / (float)(dist.x * dist.x);
		m_fTheta = (float)atan((double)distance);
		setSpeed(m_fSpdMax * 0.5f);
		m_uiStep++;
		timer = 1.2f;*/

		camPos = getCamPos();
		dist = camPos - pos;
		m_fTheta = (float)atan2((double)dist.x, (double)dist.y);
		setSpeed(m_fSpdMax * 0.5f);
		m_uiStep++;
		timer = 1.2f;

		break;
	}
	case 1:
	{	// pull and aim
		/*camPos = getCamPos();
		dist = camPos - pos;
		dir = pos - camPos;
		setDir(dir);
		distance = (float)(dist.y * dist.y) / (float)(dist.x * dist.x);
		m_fTheta = (float)atan((double)distance);*/

		////// ....
		/*if (camPos.x < pos.x && camPos.y < pos.y)
			m_fTheta += (float)PI;
		else if (camPos.x < pos.x && camPos.y >= pos.y)
			m_fTheta += (float)PI / 2.f;
		else if (camPos.x >= pos.x && camPos.y < pos.y)
			m_fTheta += (float)PI * 3 / 2.f;*/
		//////

		camPos = getCamPos();
		dist = camPos - pos;
		m_fTheta = (float)atan2((double)dist.x, (double)dist.y);


		if (timer < 0.f)
		{
			timer = 0.8f;
			m_uiStep++;
			setSpeed(0.f);
		}
		break;
	}
	case 2:
	{	// hold and aim
		//camPos = getCamPos();
		//dist = camPos - pos;
		//distance = (float)(dist.y * dist.y) / (float)(dist.x * dist.x);
		//m_fTheta = (float)atan((double)distance);

		////////
		//if (camPos.x < pos.x && camPos.y < pos.y)
		//	m_fTheta += (float)PI;
		//else if (camPos.x < pos.x && camPos.y >= pos.y)
		//	m_fTheta += (float)PI / 2.f;
		//else if (camPos.x >= pos.x && camPos.y < pos.y)
		//	m_fTheta += (float)PI * 3 / 2.f;
		////////

		camPos = getCamPos();
		dist = camPos - pos;
		m_fTheta = (float)atan2((double)dist.x, (double)dist.y);

		if (timer < 0.f)
		{
			m_uiStep++;
			setSpeed(m_fSpdMax);
			setDir(camPos - pos);
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
	
}

void CSpear::collisionEnter(CCollider* pOther)
{
}

void CSpear::collisionKeep(CCollider* pOther)
{
}

void CSpear::setMaxSpd(float spd)
{
	m_fSpdMax = spd;
}

//POINT* CSpear::rotate(fPoint pos1, /*fPoint pos2, fPoint pos3,*/ float theta)
//{
//	POINT posArr[3];
//	POINT temp;
//
//	temp.x = (LONG)(pos1.x * cos(theta) - pos1.y * sin(theta));
//	temp.y = (LONG)(pos1.x * sin(theta) + pos1.y * cos(theta));
//	posArr[0] = temp;
//
//	//temp.x = (LONG)(pos2.x * cos(theta) - pos2.y * sin(theta));
//	//temp.y = (LONG)(pos2.x * sin(theta) + pos2.y * cos(theta));
//	//posArr[1] = temp;
//
//	//temp.x = (LONG)(pos3.x * cos(theta) - pos3.y * sin(theta));
//	//temp.y = (LONG)(pos3.x * sin(theta) + pos3.y * cos(theta));
//	//posArr[2] = temp;
//
//	return posArr;
//}
