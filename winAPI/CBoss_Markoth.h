#pragma once
#include "CMonster.h"

class CTexture;
class CShield;
enum class eSTATE_BOSS
{
	IDLE,
	MOVE,
	SPAWN,				// 방패 소환
	READY,				// skill 준비
	SKILL,
	DEATH,

	END
};

class CBoss_Markoth : public CMonster
{
	eSTATE_BOSS	m_eState;

	UCHAR		m_ucPhase;

	float		m_fTimer;
	float		m_fSkillTimer;
	float		m_fSpawnTimer;
	fVec2		m_fvDir;

	vector<CShield*> m_vecShield;

	CTexture* m_pTex;

public:
	CBoss_Markoth();
	virtual ~CBoss_Markoth();

	virtual CBoss_Markoth* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
	void collisionExit(CCollider* pOther);

private:
	void setRandDelay();
	void createSpear();
	void createShield(float theta = 0.f);
	fPoint randSpearPos();

	void spawnShield();
};

// boss

#define SB_HPMAX			20
#define SB_READY_DURA		0.8
#define SB_ACCEL			(2 * SB_SHIELD_SPD / SB_READY_DURA)

// collider size
#define SB_NmSIZEX			190		
#define SB_NmSIZEY			300
#define SB_MdSIZEX			210	
#define SB_MdSIZEY			280
#define SB_SkSIZEX			390
#define SB_SkSIZEY			215

#define SB_SKILL_DURA		8
#define SB_SKILL_COOL		13

#define SB_SHIELD_SPD		1.8
#define SB_SHIELD_RAD		270

#define SB_SPEAR_SPD		300