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

// ���� ���� �� ������ �������� addEffect�� �߰��ϰ� �� ������ showEffect�� ���� ���� ������ �Ϸ���
// ���� ���ӽð� ������ deleteObj�����ʰ� active toggle�ϵ��� �ص��� 