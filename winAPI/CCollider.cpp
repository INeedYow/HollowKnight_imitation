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
	//m_fpSize = m_pOwner->getSize();
}

void CCollider::render(HDC hDC)
{
	if (!g_bDebug) return;

	fPoint fpRendPos = rendPos(m_fpPos);

	SelectGDI pen(hDC, ePEN::RED, ePEN::GREEN, m_uiCollCnt);
	SelectGDI brush(hDC, eBRUSH::HOLLOW);

	switch (m_eShape)
	{
	case eSHAPE::CIRCLE:
		Ellipse(hDC,
			(int)(fpRendPos.x - m_fpSize.x / 2.f),
			(int)(fpRendPos.y - m_fpSize.y / 2.f),
			(int)(fpRendPos.x + m_fpSize.x / 2.f),
			(int)(fpRendPos.y + m_fpSize.y / 2.f));
		break;
	case eSHAPE::RECT:
		Rectangle(hDC,
			(int)(fpRendPos.x - m_fpSize.x / 2.f),
			(int)(fpRendPos.y - m_fpSize.y / 2.f),
			(int)(fpRendPos.x + m_fpSize.x / 2.f),
			(int)(fpRendPos.y + m_fpSize.y / 2.f));
		break;
	}

	// 정보 출력
	WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", m_uiCollCnt);
	TextOutW(hDC, (int)fpRendPos.x, (int)fpRendPos.y, szBuffer, (int)wcslen(szBuffer));

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
