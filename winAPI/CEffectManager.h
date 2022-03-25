#pragma once

class CEffect;


class CEffectManager
{
	SINGLETON(CEffectManager);

private:
	list<CEffect*> m_listEff;

public:
	void addEffect(CEffect* pEff);
	void showEffect(const wstring& effName, fPoint pos, float dura = 0.f);

	CEffect* findEffect(const wstring& strName);
	CEffect* loadEffect(const wstring& effName, fPoint pos, float dura, const wstring& texName, const wstring& texPath,
		CObject* pFollow = nullptr, fPoint offset = fPoint(0.f ,0.f));

};

// 자주 많이 쓸 경우게임 진입전에 addEffect로 추가하고 씬 내에서 showEffect로 꺼내 쓰는 식으로 하려고
// 지금 지속시간 지나도 deleteObj하지않고 active toggle하도록 해뒀음 