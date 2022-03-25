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
	READY,				// skill 준비 (방패 감속, 방향전환 후 가속)
	SKILL,				// 방패 빠르고 크게 회전
	DEATH,

	END
};
// TODOTODOTODOTODOTODOTDOTODO
class CBoss_Markoth : public CMonster
{
	UCHAR		m_ucPhase;					// 1, 2 페이즈

	float		m_fSkillTimer;
	float		m_fSpawnTimer;				// spear,,인데 타이머로 안 할생각
	float		m_fTimer;					// 플레이어 미사일 피해주기 갱신용

	vector<CShield*>	m_vecShield;
	vector<CSpear*>		m_vecSpear;			// 속도 조절을 위해서 가지고 있어야 하나?

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
	//void setRandDelay();
	//fPoint randSpearPos();
	//void createSpear();
	void createShield(float theta = 0.f);
	void createSpear();

	virtual void death();
};

// skill
#define B_SKILL_DURA		8
#define B_SKILL_COOL		13

// shield
#define B_SHD_EA_MAX		2				// 방패 최대 개수
#define B_SHD_SPD			1.8				// 쉴드 속도 (radian)
#define B_SHD_RAD			270				// 회전 크기 반지름

// spear
#define B_SPR_EA_MAX		2				// spear 최대 개수
#define B_SPR_SPD_1P		600			// 1 페이즈 spear 속도
#define B_SPR_SPD_2P		900				// 2

// boss
#define B_HPMAX				24
#define B_SPD				110
#define B_READY_DURA		2
#define B_ACCEL				(2 * B_SHD_SPD / B_READY_DURA)
#define B_DMG_DELAY			0.4			// 플레이어 미사일로 부터 피해 입는 주기

// collider size
#define SB_NmSIZEX			190				//
#define SB_NmSIZEY			300
#define SB_MdSIZEX			210				// 
#define SB_MdSIZEY			280
#define SB_SkSIZEX			390				//
#define SB_SkSIZEY			215

// move area 관련
#define SB_AREA_x			250
#define SB_AREA_y			620
#define SB_AREA_X			2750
#define SB_AREA_Y			1170
#define SB_AREA_ADDX		600
#define SB_AREA_ADDY		350