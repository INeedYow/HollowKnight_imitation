#include "framework.h"
#include "CTest.h"
#include "SelectGDI.h"
CTest::CTest()
{
	m_fRad = 0;
	m_bOn = true;
	setSize(fPoint(1.f, 1.f));
	setName(eOBJNAME::TEST);

	createCollider();
	getCollider()->setSize(fPoint(100.f,250.f));
	getCollider()->setShape(eSHAPE::RECT);
}

CTest::~CTest()
{
}

void CTest::update()
{
	if (KEY_ON('I'))
		m_bOn = !m_bOn;

	if (m_bOn)
	{
		m_fRad += 0.2f * fDT;
	}
	else
	{
		if (KEY_ON('R'))
			m_fRad += 0.1f;
		if (KEY_ON('T'))
			m_fRad -= 0.1f;
		if (KEY_HOLD('F'))
			m_fRad += 0.4f * fDT;
		if (KEY_HOLD('G'))
			m_fRad -= 0.4f * fDT;
	}

	getCollider()->setRad(m_fRad);
}

void CTest::render(HDC hDC)
{
	componentRender(hDC, m_fRad);

	// 정보 출력
	SelectGDI font(hDC, eFONT::COMIC24);
	fPoint pos = rendPos(getPos());

	WCHAR szBuffer[255] = {};
	WCHAR szBuffer2[255] = {};
	swprintf_s(szBuffer, L"%.2f", m_fRad);
	swprintf_s(szBuffer2, L"%.1f , %.1f", getPos().x, getPos().y);
	TextOutW(hDC, (int)pos.x + 10, (int)pos.y - 100 , szBuffer, (int)wcslen(szBuffer));
	TextOutW(hDC, (int)pos.x + 10, (int)pos.y - 130 , szBuffer2, (int)wcslen(szBuffer2));
}

float CTest::getRad()
{
	return m_fRad;
}


void CTest::collisionKeep(CCollider* pOther)
{
}

void CTest::collisionEnter(CCollider* pOther)
{
}

void CTest::collisionExit(CCollider* pOther)
{
}
