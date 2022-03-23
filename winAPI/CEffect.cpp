#include "framework.h"
#include "CEffect.h"
#include "CTexture.h"

 //TODO 이펙트 구현방법
CEffect::CEffect()
{
	m_pTex = nullptr;

	m_tInfo = {};

	CObject::setName(eOBJNAME::EFFECT);

	createAnimator();
}

CEffect::~CEffect()
{
}

void CEffect::setInfo(tEffectInfo info)
{
	m_tInfo = info;
}

void CEffect::setName(const wstring& strName)
{
	m_strName = strName;
}

//void CEffect::setTex(const wstring& strName, const wstring& strPath)
//{
//	m_pTex = loadTex();
//}

const wstring& CEffect::getName()
{
	return m_strName;
}

const tEffectInfo& CEffect::getInfo()
{
	return m_tInfo;
}

CTexture* CEffect::getTex()
{
	return m_pTex;
}

void CEffect::update()
{
	m_tInfo.fTimer += fDT;

	if (m_tInfo.fDura <= m_tInfo.fTimer)
		deleteObj(this);
}

void CEffect::render(HDC hDC)
{
	componentRender(hDC);
}

void CEffect::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}