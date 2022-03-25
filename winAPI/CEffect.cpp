#include "framework.h"
#include "CEffect.h"
#include "CTexture.h"

CEffect::CEffect()
{
	CObject::setName(eOBJNAME::EFFECT);

	m_pTex = nullptr;
	m_pFollow = nullptr;
	m_fDura = 0.f;
	m_bActive = false;

	createAnimator();
}

CEffect::~CEffect()
{
}

void CEffect::setDuration(float fDura)
{
	m_fDura = fDura;
}

void CEffect::setFollow(CObject* pFollow)
{
	m_pFollow = pFollow;
}

void CEffect::setEffName(const wstring& strName)
{
	m_strName = strName;
}

void CEffect::setOffset(fPoint offset)
{
	m_fpOffset = offset;
}

void CEffect::setActive(bool isAct)
{
	m_bActive = isAct;
}

void CEffect::setTex(CTexture* pTex)
{
	m_pTex = pTex;
}

fPoint CEffect::getOffset()
{
	return m_fpOffset;
}

const wstring& CEffect::getEffName()
{
	return m_strName;
}

CTexture* CEffect::getTex()
{
	return m_pTex;
}

bool CEffect::isActive()
{
	return m_bActive;
}

void CEffect::update()
{
	if (!m_bActive) return;

	m_fDura -= fDT;

	if (m_fDura < 0.f)
		m_bActive = false;

	if (nullptr != m_pFollow)
	{
		setPos(m_pFollow->getPos() + m_fpOffset);
	}

	if (nullptr != getAnimator())
		getAnimator()->update();
}

void CEffect::render(HDC hDC)
{
	if (!m_bActive) return;

	componentRender(hDC);
}

void CEffect::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
}