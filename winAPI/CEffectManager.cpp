#include "framework.h"
#include "CEffectManager.h"

CEffectManager::CEffectManager()
{
	m_mapEff = {};
}

CEffectManager::~CEffectManager()
{
	/*map<wstring, CEffect*>::iterator iter = m_mapEff.begin();
	for (; iter != m_mapEff.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapEff.clear();*/
}


void CEffectManager::addEffect(const wstring& strName ,CEffect* pEff)
{
	m_mapEff.insert(make_pair(strName, pEff));
}

CEffect* CEffectManager::findEffect(const wstring& strName)
{
	map<wstring, CEffect*>::iterator iter = m_mapEff.find(strName);

	if (m_mapEff.end() == iter)
		assert(nullptr);

	return iter->second;
}
