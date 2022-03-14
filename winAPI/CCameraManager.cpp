#include "framework.h"
#include "CCameraManager.h"
#include "CObject.h"

CCameraManager::CCameraManager()
{
	m_fpFocus		= {};
	m_fpCurFocus	= {};
	m_fpPrevFocus	= {};
	m_pTraceObj		= nullptr;
	m_fpDiff		= {};
	m_fTime			= 1.f;
	m_fAccTime		= 0.f;
	m_fSpeed		= 0.f;

}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::update()
{
	if (m_pTraceObj)				// 추적 중일 때
	{
		if (m_pTraceObj->isDead())		// 유예 중 예외처리
			m_pTraceObj = nullptr;
		else
			setFocus(m_pTraceObj->getPos());
	}

	calculateDiff();
}

void CCameraManager::setFocusOn(fPoint focus)
{
	m_fpFocus = focus;
	float fMoveDist = (m_fpFocus - m_fpPrevFocus).length();

	m_fSpeed = fMoveDist / m_fTime;

	m_fAccTime = 0.f;
}

void CCameraManager::setTraceObj(CObject* targetObj)
{
	m_pTraceObj = targetObj;
}

fPoint CCameraManager::getFocus()
{
	return m_fpCurFocus;
}

fPoint CCameraManager::getRealPos(fPoint renderPos)
{
	return renderPos + m_fpDiff;
}

fPoint CCameraManager::getRenderPos(fPoint pos)
{
	return pos - m_fpDiff;
}

void CCameraManager::calculateDiff()
{
	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
		m_fpCurFocus = m_fpFocus;
	else
	{
		fPoint fpCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
		m_fpCurFocus = m_fpPrevFocus + (m_fpFocus - m_fpPrevFocus).normalize() * m_fSpeed * fDT;
		m_fpDiff = m_fpCurFocus - fpCenter;

		m_fpPrevFocus = m_fpCurFocus;
	}
}
