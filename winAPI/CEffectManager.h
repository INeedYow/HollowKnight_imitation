#pragma once

class CEffect;


class CEffectManager
{
	SINGLETON(CEffectManager);

private:
	map<wstring, CEffect*> m_mapEff;

public:
	
	void addEffect(const wstring& strName, CEffect* pEff);		// map에 effect 저장

	CEffect* findEffect(const wstring& strName);
};

// obj - effector - effect // 컴포넌트 개념으로 하려다가
// 서로 다른 obj가 같은 이펙트를 쓸 수도 있겠다는 생각에 매니저로