#include "framework.h"
#include "CCameraManager.h"
#include "CObject.h"
#include "CTexture.h"

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

void CCameraManager::init()
{
	m_pTex = CResourceManager::getInst()->createTexture(L"CameraTex", WINSIZEX, WINSIZEY);
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

void CCameraManager::render(HDC hDC)
{
	Rectangle(m_pTex->getDC(), 0, 0, 500, 500);
	BLENDFUNCTION bf = {  };

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(hDC,
		 0, 0,
		 (int)(m_pTex->getBmpWidth()),
		 (int)(m_pTex->getBmpHeight()),
		 m_pTex->getDC(),
		 0, 0,
		 (int)(m_pTex->getBmpWidth()),
		 (int)(m_pTex->getBmpHeight()),
		 bf);
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

void CCameraManager::scroll(fVec2 vec, float spd)
{
	m_fpFocus		= m_fpFocus + vec * spd * fDT;
	m_fpCurFocus	= m_fpCurFocus + vec * spd * fDT;

	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fpDiff = m_fpCurFocus - fptCenter;
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
