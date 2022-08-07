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
	m_fTime			= 0.2f;
	m_fAccTime		= 0.f;
	m_fSpeed		= 0.f;

	m_bArea = false;
	m_tCamArea = {};

	m_pTex = nullptr;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::init()
{
	m_pTex = CResourceManager::getInst()->createTexture(L"CameraTex", WINSIZEX, WINSIZEY);
	m_fpCurFocus =	{ WINSIZEX * 0.5f, WINSIZEY * 0.5f };
	m_fpFocus =		{ WINSIZEX * 0.5f, WINSIZEY * 0.5f };
	m_fpPrevFocus = { WINSIZEX * 0.5f, WINSIZEY * 0.5f };
}

void CCameraManager::update()
{
	if (m_pTraceObj)				// 추적 중일 때
	{
		if (m_pTraceObj->isDead())		// 유예 중 예외처리
			m_pTraceObj = nullptr;
		else
			camSetFocus(m_pTraceObj->getPos());
	}
	calculateDiff();
}

void CCameraManager::render(HDC hDC)
{
	// 이펙트 없을 때
	if (m_listCamEffect.empty()) return;

	tCamEffect& effect = m_listCamEffect.front();
	effect.fTimer += fDT;

	float fRatio = 0.f;
	fRatio = effect.fTimer / effect.fDura;

	if (fRatio < 0.f)
		fRatio = 0.f;
	else if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	// fade out
	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{	// fade in 때는 (1 - 비율)로 반대 효과
		iAlpha = (int)(255.f * (1.f - fRatio));
	}
	else if (CAM_EFFECT::SWING == effect.eEffect)
	{
		int random;
		random = rand() % 71 - 35;
		m_fpCurFocus.x += random;
		random = rand() % 71 - 35;
		m_fpCurFocus.y += random;
	}

	BLENDFUNCTION bf = {  };

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(hDC,
		 0, 0,
		 (int)(m_pTex->getBmpWidth()),
		 (int)(m_pTex->getBmpHeight()),
		 m_pTex->getDC(),
		 0, 0,
		 (int)(m_pTex->getBmpWidth()),
		 (int)(m_pTex->getBmpHeight()),
		 bf);

	// 효과 완료
	if (effect.fDura < effect.fTimer)
	{
		m_listCamEffect.pop_front();
	}
}

void CCameraManager::setFocusNow(fPoint focus)
{
	if (m_bArea)
	{
		if (focus.x < m_tCamArea.fMinX)
			focus.x = m_tCamArea.fMinX;
		if (focus.x > m_tCamArea.fMaxX)
			focus.x = m_tCamArea.fMaxX;

		if (focus.y < m_tCamArea.fMinY)
			focus.y = m_tCamArea.fMinY;
		if (focus.y > m_tCamArea.fMaxY)
			focus.y = m_tCamArea.fMaxY;
	}

	m_fpCurFocus = focus;
	m_fpFocus = focus;
	m_fpPrevFocus = focus;
}

void CCameraManager::setFocusOn(fPoint focus)
{
	if (m_bArea)
	{
		if (focus.x < m_tCamArea.fMinX)
			focus.x = m_tCamArea.fMinX;
		if (focus.x > m_tCamArea.fMaxX)
			focus.x = m_tCamArea.fMaxX;

		if (focus.y < m_tCamArea.fMinY)
			focus.y = m_tCamArea.fMinY;
		if (focus.y > m_tCamArea.fMaxY)
			focus.y = m_tCamArea.fMaxY;
	}

	m_fpFocus = focus;
	float fMoveDist = (m_fpFocus - m_fpPrevFocus).length();

	m_fSpeed = fMoveDist / m_fTime;

	m_fAccTime = 0.f;
}

void CCameraManager::setTraceObj(CObject* targetObj)
{
	m_pTraceObj = targetObj;
}

void CCameraManager::setCameraArea(float minX, float minY, float maxX, float maxY)
{											// 알아서 WINSIZE에 맞게 설정해주도록
	m_tCamArea = { 
		minX + WINSIZEX * 0.5f, 
		minY + WINSIZEY * 0.5f, 
		maxX - WINSIZEX * 0.5f, 
		maxY - WINSIZEY * 0.5f 
	};
	m_bArea = true;							// 범위 설정했다는 건 사용하겠다고 보고 true로
}

void CCameraManager::setIsArea(bool isOn)
{
	m_bArea = isOn;
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

void CCameraManager::fadeIn(float dura)
{	// fade in 이펙트 생성해서 리스트에 추가
	tCamEffect ef = {};
	ef.eEffect = CAM_EFFECT::FADE_IN;
	ef.fDura = dura;
	ef.fTimer = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == dura) assert(nullptr);
}

void CCameraManager::fadeOut(float dura)
{
	tCamEffect ef = {};
	ef.eEffect = CAM_EFFECT::FADE_OUT;
	ef.fDura = dura;
	ef.fTimer = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == dura) assert(nullptr);
}

void CCameraManager::swing(float dura)
{
	tCamEffect ef = {};
	ef.eEffect = CAM_EFFECT::SWING;
	ef.fDura = dura;
	ef.fTimer = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == dura) assert(nullptr);
}

void CCameraManager::scroll(fVec2 vec, float spd)
{
	m_fpFocus		= m_fpFocus + vec * spd * fDT;
	m_fpCurFocus	= m_fpCurFocus + vec * spd * fDT;

	if (m_bArea)
	{
		if (m_fpFocus.x < m_tCamArea.fMinX)
			m_fpFocus.x = m_tCamArea.fMinX;
		if (m_fpFocus.x > m_tCamArea.fMaxX)
			m_fpFocus.x = m_tCamArea.fMaxX;

		if (m_fpFocus.y < m_tCamArea.fMinY)
			m_fpFocus.y = m_tCamArea.fMinY;
		if (m_fpFocus.y > m_tCamArea.fMaxY)
			m_fpFocus.y = m_tCamArea.fMaxY;

		if (m_fpCurFocus.x < m_tCamArea.fMinX)
			m_fpCurFocus.x = m_tCamArea.fMinX;
		if (m_fpCurFocus.x > m_tCamArea.fMaxX)
			m_fpCurFocus.x = m_tCamArea.fMaxX;

		if (m_fpCurFocus.y < m_tCamArea.fMinY)
			m_fpCurFocus.y = m_tCamArea.fMinY;
		if (m_fpCurFocus.y > m_tCamArea.fMaxY)
			m_fpCurFocus.y = m_tCamArea.fMaxY;
	}

	fPoint fptCenter = fPoint(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_fpDiff = m_fpCurFocus - fptCenter;
}

void CCameraManager::calculateDiff()
{
	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
		m_fpCurFocus = m_fpFocus;
	else
	{
		fPoint fpCenter = fPoint(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
		m_fpCurFocus = m_fpPrevFocus + (m_fpFocus - m_fpPrevFocus).normalize() * m_fSpeed * fDT;
		m_fpDiff = m_fpCurFocus - fpCenter;

		m_fpPrevFocus = m_fpCurFocus;
	}
}
