#include "framework.h"
#include "CEffectManager.h"
#include "CEffect.h"

CEffectManager::CEffectManager()
{
	m_listEff = {};
}

CEffectManager::~CEffectManager()
{	// scn���� ��� ����
	/*list<CEffect*>::iterator iter = m_listEff.begin();
	for (; iter != m_listEff.end(); iter++)
	{
		if (nullptr != *iter)
			delete *iter;
	}

	m_listEff.clear();*/
}

void CEffectManager::addEffect(CEffect* pEff)
{	// ���� ����Ʈ ������ ����� �� ������ �ߺ� ���
	m_listEff.push_back(pEff);
}

CEffect* CEffectManager::findEffect(const wstring& strName)
{
	list<CEffect*>::iterator iter = m_listEff.begin();
	for (; iter != m_listEff.end(); iter++)
	{	// ã�� �̸��� ��Ȱ��ȭ �� ����Ʈ�� ã���� ��ȯ
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
	{	// ����� �� �ִ� ����Ʈ�� ���� ��� ���� �� �߰�
		
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
	
	if (dura)	// ���� �ð� 
		pEff->setDuration(dura);

	pEff->setActive(true);
}
