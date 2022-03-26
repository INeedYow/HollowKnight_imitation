#include "framework.h"
#include "CShield.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "CBoss_Markoth.h"

CShield::CShield()
{
	m_pTex = nullptr;
	m_pMemTex = nullptr;

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(70.f, 70.f));
	setName(eOBJNAME::SHIELD);
	m_fSpd = (float)B_SHD_SPD;
	m_fTheta = 0.f;
	m_fRadius = 0.f;
	m_bRotRight = true;

	m_pOwner = nullptr;

	createCollider();
	getCollider()->setSize(fPoint(70.f, 70.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();
}

CShield::CShield(fPoint pos, CObject* pOwner)
{
	setPos(pos);
	m_pOwner = pOwner;

	calculateRad();
}

CShield::~CShield()
{
}

CShield* CShield::clone()
{
	return new CShield(*this);
}

void CShield::calculateRad()
{
	float x = getPos().x - m_pOwner->getPos().x;
	float y = getPos().y - m_pOwner->getPos().y;

	m_fRadius = (float)sqrt((double)x * x + (double)y * y);
}

void CShield::update()
{
	fPoint pos = getPos();

	if (m_bRotRight)
	{
		m_fTheta += m_fSpd * fDT;
	}
	else
	{
		m_fTheta -= m_fSpd * fDT;
	}

	pos.x = m_fRadius * (float)cos(m_fTheta);
	pos.y = m_fRadius * (float)sin(m_fTheta);

	pos += m_pOwner->getPos();

	setPos(pos);
	
	getAnimator()->update();
}

//void CShield::render(HDC hDC)
//{
//	SelectGDI font(hDC, eFONT::COMIC24);
//
//	fPoint pos = rendPos(getPos());
//
//	wchar_t bufTheta[255] = {};
//	wchar_t bufRad[255] = {};
//
//	swprintf_s(bufTheta, L"theta = %.1f", m_fTheta);
//	swprintf_s(bufRad, L"rad = %.1f", m_fRadius);
//
//	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 40, bufTheta, (int)wcslen(bufTheta));
//	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 60, bufRad, (int)wcslen(bufRad));
//
//	componentRender(hDC);
//}

#define sizex 166
#define sizey 308
#define MEMTEX_SIZE (UINT)(308 * 1.5f)

void CShield::render(HDC hDC)
{
	fPoint pos = rendPos(getPos());
	fPoint size = { (float)sizex, (float)sizey };

	POINT pThreeArr[3];

	// 좌상, 우상, 좌하 좌표 3개
	fPoint arr[3] = {
		fPoint(-size.x / 2.f, -size.y / 2.f),
		fPoint(size.x / 2.f, -size.y / 2.f),
		fPoint(-size.x / 2.f,  size.y / 2.f),
	};

	for (int i = 0; i < 3; i++)
	{	// 좌표에 회전행렬로 회전적용
		pThreeArr[i].x = -(LONG)(arr[i].x * cos(m_fTheta) - arr[i].y * sin(m_fTheta));
		pThreeArr[i].y = -(LONG)(arr[i].x * sin(m_fTheta) + arr[i].y * cos(m_fTheta));
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
		m_pTex->getDC(),
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


void CShield::setRot(bool isRight)
{
	m_bRotRight = isRight;
}

void CShield::toggleRot()
{
	m_bRotRight = !m_bRotRight;
}

void CShield::setOwner(CObject* pOwner)
{
	m_pOwner = pOwner;
}

void CShield::setfSpeed(float spd)
{
	m_fSpd = spd;
}

void CShield::setRadius(float rad)
{
	m_fRadius = rad;
}

void CShield::setTheta(float theta)
{
	m_fTheta = theta;
}

void CShield::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

void CShield::createMemTex(const wstring& texName, UINT sizeX, UINT sizeY)
{
	m_pMemTex = CResourceManager::getInst()->createTexture(texName, sizeX, sizeY);
}

bool CShield::isRotRight()
{
	return m_bRotRight;
}

CTexture* CShield::getTex()
{
	return m_pTex;
}

float CShield::getSpeed()
{
	return m_fSpd;
}

float CShield::getRadius()
{
	return m_fRadius;
}

float CShield::getTheta()
{
	return m_fTheta;
}

void CShield::collisionEnter(CCollider* pOther)
{
}
