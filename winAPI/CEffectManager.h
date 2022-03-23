#pragma once

class CEffect;


class CEffectManager
{
	SINGLETON(CEffectManager);

private:
	map<wstring, CEffect*> m_mapEff;

public:
	
	void addEffect(const wstring& strName, CEffect* pEff);		// map�� effect ����

	CEffect* findEffect(const wstring& strName);
};

// obj - effector - effect // ������Ʈ �������� �Ϸ��ٰ�
// ���� �ٸ� obj�� ���� ����Ʈ�� �� ���� �ְڴٴ� ������ �Ŵ�����