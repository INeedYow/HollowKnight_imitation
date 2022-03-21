#include "framework.h"
#include "CEffector.h"
#include "CEffect.h"

CEffector::CEffector()
{
    m_pOwner = nullptr;
}

CEffector::~CEffector()
{
	for (map<wstring, CEffect*>::iterator iter = m_mapEff.begin();
		iter != m_mapEff.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapEff.clear();
}

CObject* CEffector::getOwner()
{
    return m_pOwner;
}

void CEffector::update()
{
	for (list<CEffect*>::iterator iter = m_listEff.begin();
		iter != m_listEff.end(); iter++)
	{
		if (nullptr != *iter)
		{
			(*iter)->update();
		}
	}
}

void CEffector::render(HDC hDC)
{
	for (list<CEffect*>::iterator iter = m_listEff.begin();
		iter != m_listEff.end();)
	{
		if (nullptr != *iter)
		{
			(*iter++)->render(hDC);
		}
		else
		{
			m_listEff.erase(iter);
		}
	}
}

void CEffector::createEffect(const wstring& strName, CTexture* pTex/*//TODO*/)
{
	CEffect* pEff = findEffect(strName);

	if (nullptr == pEff) return;

	pEff = new CEffect;
	pEff->setName(strName);
}

CEffect* CEffector::findEffect(const wstring& strName)
{
	map<wstring, CEffect*>::iterator iter = m_mapEff.find(strName);

	if (iter == m_mapEff.end()) return nullptr;
   
	return iter->second;
}

void CEffector::show(const wstring& strName)
{
}
