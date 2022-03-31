#include "framework.h"
#include "CCollider.h"
#include "CObject.h"

#include "SelectGDI.h"

UINT CCollider::s_uiID = 0;

CCollider::CCollider()
{
	m_pOwner = nullptr;
	m_fpPos = {};
	m_fpSize = {};
	m_fpOffset = {};
	m_uiCollCnt = 0;
	m_eShape = eSHAPE::POINT;
	m_fRad = 0.f;

	m_uiID = s_uiID++;
}

// 복사 생성자
CCollider::CCollider(const CCollider& other)
{
	m_pOwner = nullptr;
	m_fpPos = other.m_fpPos;
	m_fpSize = other.m_fpSize;
	m_fpOffset = other.m_fpOffset;
	m_uiCollCnt = other.m_uiCollCnt;
	m_eShape = other.m_eShape;
	m_fRad = other.m_fRad;

	m_uiID = s_uiID++;
}

CCollider::~CCollider()
{
}

void CCollider::setPos(fPoint pos)
{
	m_fpPos = pos;
}

void CCollider::setSize(fPoint size)
{
	m_fpSize = size;
}

void CCollider::setOffset(fPoint offset)
{
	m_fpOffset = offset;
}

void CCollider::setShape(eSHAPE shape)
{
	m_eShape = shape;
}

void CCollider::setRad(float rad)
{
	m_fRad = rad;
}

float CCollider::getRad()
{
	return m_fRad;
}

fPoint CCollider::getPos()
{
	return m_fpPos;
}

fPoint CCollider::getSize()
{
	return m_fpSize;
}

fPoint CCollider::getOffset()
{
	return m_fpOffset;
}

CObject* CCollider::getOwner()
{
	return m_pOwner;
}

eSHAPE CCollider::getShape()
{
	return m_eShape;
}

UINT CCollider::getID()
{
	return m_uiID;
}

void CCollider::finalUpdate()
{
	m_fpPos = m_pOwner->getPos() + m_fpOffset;

}

void CCollider::render(HDC hDC, float theta, bool rotReverse)
{
	if (!g_bDebug) return;

	fPoint pos = rendPos(m_fpPos);

	SelectGDI pen(hDC, ePEN::RED, ePEN::GREEN, m_uiCollCnt);
	SelectGDI brush(hDC, eBRUSH::HOLLOW);

	if (0.f == theta)
	{	// 회전 X
		switch (m_eShape)
		{
		case eSHAPE::CIRCLE:
			Ellipse(hDC,
				(int)(pos.x - m_fpSize.x / 2.f),
				(int)(pos.y - m_fpSize.y / 2.f),
				(int)(pos.x + m_fpSize.x / 2.f),
				(int)(pos.y + m_fpSize.y / 2.f));
			break;
		case eSHAPE::RECT:
			Rectangle(hDC,
				(int)(pos.x - m_fpSize.x / 2.f),
				(int)(pos.y - m_fpSize.y / 2.f),
				(int)(pos.x + m_fpSize.x / 2.f),
				(int)(pos.y + m_fpSize.y / 2.f));
			break;
		}
	}
	else
	{	// 회전 O
		if (m_eShape != eSHAPE::RECT) return;

		POINT pPointArr[4];

		// 좌상, 우상, 우하, 좌하 좌표 (LineTo로 이어 그리기 위해 순서 변형)
		fPoint arr[4] = {
			fPoint(-m_fpSize.x / 2.f, -m_fpSize.y / 2.f),
			fPoint(m_fpSize.x / 2.f, -m_fpSize.y / 2.f),
			fPoint(m_fpSize.x / 2.f,  m_fpSize.y / 2.f),
			fPoint(-m_fpSize.x / 2.f,  m_fpSize.y / 2.f)
		};

		for (int i = 0; i < 4; i++)
		{	// 좌표에 회전행렬로 회전적용
			pPointArr[i].x = (LONG)(arr[i].x * cos(theta) - arr[i].y * sin(theta));
			pPointArr[i].y = (LONG)(arr[i].x * sin(theta) + arr[i].y * cos(theta));

			if (rotReverse)
			{	// 반대로 회전 시 부호 변경
				pPointArr[i].x *= -1;
				pPointArr[i].y *= -1;
			}
		}

		for (int i = 0; i < 4; i++)
		{	// pos 만큼 위치로
			pPointArr[i].x += (LONG)(pos.x);
			pPointArr[i].y += (LONG)(pos.y);
		}
		
		for (int i = 0; i < 4; i++)
		{	// point [1]->[2]->[3]->[4]->[1] 선 그리기
			//if (i == 0)
			//{	// 디버깅용
			//	SelectGDI pen(hDC, ePEN::BLUE);
			//	MoveToEx(hDC, pPointArr[i].x, pPointArr[i].y, NULL);
			//	LineTo(hDC, pPointArr[(i + 1) % 4].x, pPointArr[(i + 1) % 4].y);
			//	continue;
			//}
			MoveToEx(hDC, pPointArr[i].x, pPointArr[i].y, NULL);
			LineTo(hDC, pPointArr[(i + 1) % 4].x, pPointArr[(i + 1) % 4].y);
		}
	}

	// 정보 출력
	SelectGDI font(hDC, eFONT::COMIC18);
	WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", m_uiCollCnt);
	TextOutW(hDC, (int)pos.x, (int)pos.y, szBuffer, (int)wcslen(szBuffer));
}

void CCollider::collisionKeep(CCollider* pOther)
{
	m_pOwner->collisionKeep(pOther);
}

void CCollider::collisionEnter(CCollider* pOther)
{
	m_pOwner->collisionEnter(pOther);
	m_uiCollCnt++;
}

void CCollider::collisionExit(CCollider* pOther)
{
	m_pOwner->collisionExit(pOther);
	m_uiCollCnt--;
}
