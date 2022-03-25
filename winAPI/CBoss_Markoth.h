#pragma once
#include "CMonster.h"

class CTexture;
class CShield;
class CSpear;

enum class eSTATE_BOSS
{
	IDLE,
	MOVE,
	SPAWN,				// ���� ��ȯ
	READY,				// skill �غ� (���� ����, ������ȯ �� ����)
	SKILL,				// ���� ������ ũ�� ȸ��
	DEATH,

	END
};
// TODOTODOTODOTODOTODOTDOTODO
class CBoss_Markoth : public CMonster
{
	UCHAR		m_ucPhase;					// 1, 2 ������

	float		m_fSkillTimer;
	float		m_fSpawnTimer;				// spear,,�ε� Ÿ�̸ӷ� �� �һ���
	float		m_fTimer;					// �÷��̾� �̻��� �����ֱ� ���ſ�

	vector<CShield*>	m_vecShield;
	vector<CSpear*>		m_vecSpear;			// �ӵ� ������ ���ؼ� ������ �־�� �ϳ�?

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
#define B_SHD_EA_MAX		2				// ���� �ִ� ����
#define B_SHD_SPD			1.8				// ���� �ӵ� (radian)
#define B_SHD_RAD			270				// ȸ�� ũ�� ������

// spear
#define B_SPR_EA_MAX		2				// spear �ִ� ����
#define B_SPR_SPD_1P		600			// 1 ������ spear �ӵ�
#define B_SPR_SPD_2P		900				// 2

// boss
#define B_HPMAX				24
#define B_SPD				110
#define B_READY_DURA		2
#define B_ACCEL				(2 * B_SHD_SPD / B_READY_DURA)
#define B_DMG_DELAY			0.4			// �÷��̾� �̻��Ϸ� ���� ���� �Դ� �ֱ�

// collider size
#define SB_NmSIZEX			190				//
#define SB_NmSIZEY			300
#define SB_MdSIZEX			210				// 
#define SB_MdSIZEY			280
#define SB_SkSIZEX			390				//
#define SB_SkSIZEY			215

// move area ����
#define SB_AREA_x			250
#define SB_AREA_y			620
#define SB_AREA_X			2750
#define SB_AREA_Y			1170
#define SB_AREA_ADDX		600
#define SB_AREA_ADDY		350