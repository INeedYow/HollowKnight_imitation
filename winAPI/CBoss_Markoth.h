#pragma once
#include "CMonster.h"

class CTexture;
class CShield;
class CSpear;

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
	UCHAR		m_ucPhase;

	float		m_fTimer;
	float		m_fSkillTimer;
	float		m_fSpawnTimer;

	vector<CShield*>	m_vecShield;
	vector<CSpear*>		m_vecSpear;

public:
	CBoss_Markoth();
	virtual ~CBoss_Markoth();

	virtual CBoss_Markoth* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
	void collisionExit(CCollider* pOther);

	void setSkillCooldown(float cd);
	vector<CShield*>& getVecShield();
	void spawnShield();
private:
	void setRandDelay();
	fPoint randSpearPos();
	void createSpear();
	void createShield(float theta = 0.f);


	virtual void death();
};

// skill
#define SB_SKILL_DURA		8
#define SB_SKILL_COOL		13

// shield
#define SB_SHIELD_SPD		1.8
#define SB_SHIELD_RAD		270

// boss
#define SB_HPMAX			20
#define SB_SPD				110
#define SB_READY_DURA		2
#define SB_ACCEL			(2 * SB_SHIELD_SPD / SB_READY_DURA)
#define SB_DMG_DELAY		0.35			// 플레이어 미사일로 부터 피해 입는 주기

// collider size
#define SB_NmSIZEX			190		
#define SB_NmSIZEY			300
#define SB_MdSIZEX			210	
#define SB_MdSIZEY			280
#define SB_SkSIZEX			390
#define SB_SkSIZEY			215

// spear
#define SB_SPEAR_SPD		300

// move state 관련
#define SB_AREA_x			250
#define SB_AREA_y			620
#define SB_AREA_X			2750
#define SB_AREA_Y			1170
#define SB_AREA_ADDX		600
#define SB_AREA_ADDY		350