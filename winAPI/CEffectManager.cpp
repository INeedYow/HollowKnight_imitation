#include "framework.h"
#include "CEffectManager.h"
#include "CEffect.h"

CEffectManager::CEffectManager()
{
	m_listEff = {};
}

CEffectManager::~CEffectManager()
{	// scn에서 모두 지움
	/*list<CEffect*>::iterator iter = m_listEff.begin();
	for (; iter != m_listEff.end(); iter++)
	{
		if (nullptr != *iter)
			delete *iter;
	}

	m_listEff.clear();*/
}

void CEffectManager::addEffect(CEffect* pEff)
{	// 같은 이펙트 여러개 사용할 수 있으니 중복 허용
	m_listEff.push_back(pEff);
}

CEffect* CEffectManager::findEffect(const wstring& strName)
{
	list<CEffect*>::iterator iter = m_listEff.begin();
	for (; iter != m_listEff.end(); iter++)
	{	// 찾는 이름의 비활성화 된 이펙트를 찾으면 반환
		if ((*iter)->getEffName() == strName && !((*iter)->isActive()))
		{
			return *iter;
		}
	}

	return nullptr;
}

CEffect* CEffectManager::loadEffect(const wstring& effName, fPoint pos, float dura,
	const wstring& texName, const wstring& texPath, CObject* pFollow, fPoint offset)
{
	CEffect* pEff = findEffect(effName);
	
	if (nullptr == pEff)
	{	// 사용할 수 있는 이펙트가 없는 경우 생성 후 추가
		
		CEffect* pEff = new CEffect;
		pEff->setEffName(effName);
		pEff->setPos(pos);
		pEff->setDuration(dura);
		pEff->setTex(loadTex(texName, texPath));
		pEff->setFollow(pFollow);
		pEff->setOffset(offset);

		m_listEff.push_back(pEff);
	}
	return pEff;
}

void CEffectManager::showEffect(const wstring& effName, fPoint pos, float dura)
{
	CEffect* pEff = findEffect(effName);
	assert(pEff);

	pEff->setPos(pos);
	
	if (dura)	// 지속 시간 
		pEff->setDuration(dura);

	pEff->setActive(true);
}
