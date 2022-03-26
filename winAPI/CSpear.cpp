#include "framework.h"
#include "CSpear.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CBoss_Markoth.h"

#include "SelectGDI.h"

CSpear::CSpear()
{
	setSize(fPoint(SPR_SIZEX, SPR_SIZEY));
	setName(eOBJNAME::MISSILE_MONSTER);
	setTimer(0.f);
	setDir(fVec2(0.f, 0.f));

	getCollider()->setShape(eSHAPE::RECT);
	getCollider()->setSize(fPoint(30.f, 30.f));

	m_uiStep = 0;
	m_fTheta = 0.f;
	m_fSpd = 1.f;
	m_bActive = true;

	m_pMemTex = nullptr;
}

CSpear::~CSpear()
{
}

// TODO 
// 마젠타 지우는 방법
// mask 인자가 지우는 비트맵?
void CSpear::update()
{
	if (KEY_ON('U'))
		camSetTrace(this);
	if (KEY_ON('Y'))
		camSetTrace(CGameManager::getInst()->getPlayer());

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
		
		timer = 0.6f;
		setSpeed(m_fSpd * 0.1f);
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
			timer = 0.6f;
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

	default:
	{	// 카메라 범위 나가면 재활용
		if (!m_bActive) break;		// 보스 스킬 쓸 때 비활성화 되면 재생성은 안 되게

		fPoint randPos = rendPos(pos);
		if (randPos.x < (float)(-1 * SPR_SIZEX / 2.f) || randPos.x > (float)(WINSIZEX + SPR_SIZEX / 2.f) ||
			randPos.y < (float)(-1 * SPR_SIZEY / 2.f) || randPos.y > (float)(WINSIZEX + SPR_SIZEY / 2.f))
		{
			m_uiStep = 0;
			setSpeed(0.f);
			pos = getRandPos();
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


// TODO
void CSpear::render(HDC hDC)
{
	componentRender(hDC);
	//////////////////////////////
	fPoint pos = getPos();
	fPoint size = { (float)SPR_SIZEX, (float)SPR_SIZEY };
	
	POINT pThreeArr[3];
	pos = rendPos(pos);
	
	// 좌상, 우상, 좌하 좌표 3개
	fPoint arr[3] = {
		fPoint(-size.x / 2.f, -size.y / 2.f),
		fPoint(size.x / 2.f, -size.y / 2.f),
		fPoint(-size.x / 2.f,  size.y / 2.f),
	};
	
	for (int i = 0; i < 3; i++)
	{	// 좌표에 회전행렬로 회전적용
		pThreeArr[i].x = (LONG)(arr[i].x * cos(m_fTheta) - arr[i].y * sin(m_fTheta));
		pThreeArr[i].y = (LONG)(arr[i].x * sin(m_fTheta) + arr[i].y * cos(m_fTheta));
	}

	for (int i = 0; i < 3; i++)
	{	// memDC 중앙 좌표로 이동
		pThreeArr[i].x += (LONG)(MEMTEX_SIZE / 2);
		pThreeArr[i].y += (LONG)(MEMTEX_SIZE / 2);
	}

	// memDC 마젠타로 채움
	SelectGDI brush(m_pMemTex->getDC(), eBRUSH::MAGENTA);

	Rectangle(m_pMemTex->getDC(), 
		-1, -1, MEMTEX_SIZE + 1, MEMTEX_SIZE + 1);

	// 회전한 좌표로 memDC에 그림
	PlgBlt(m_pMemTex->getDC(),
		pThreeArr,
		CMissile::getTex()->getDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		NULL,
		0, 0
	);

	// memDC에 그렸던 것 통쨰로 가져오면 됨
	TransparentBlt(hDC,
		(int)(pos.x - MEMTEX_SIZE / 2),
		(int)(pos.y - MEMTEX_SIZE / 2),
		MEMTEX_SIZE,
		MEMTEX_SIZE,
		m_pMemTex->getDC(),
		0,
		0,
		MEMTEX_SIZE,
		MEMTEX_SIZE,
		RGB(255, 0, 255)
	);
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

void CSpear::setMemTex(const wstring& texName, UINT sizeX, UINT sizeY)
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