#pragma once
#include "CMonster.h"

class CTexture;
class CShield;

class CBoss_Markoth : public CMonster
{
	UCHAR	m_ucPhase;
	float	m_fTimer;
	float	m_fDelay;
	fVec2	m_fvDir;

	vector<CShield*> m_vecShield;

	CTexture* m_pTex;

public:
	CBoss_Markoth();
	virtual ~CBoss_Markoth();
	virtual CBoss_Markoth* clone();	// 몬스터 상속해서 보스도 clone이 있어야 하는데 ?

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
	void collisionExit(CCollider* pOther);

private:
	void setRandDelay();
	void createSpear();
	void createShield();
	fPoint randSpearPos();

	void phaseInit();
};