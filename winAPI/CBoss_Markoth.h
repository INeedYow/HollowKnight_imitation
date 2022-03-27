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

class CBoss_Markoth : public CMonster
{
	UCHAR		m_ucPhase;					// 1, 2 ������

	float		m_fSkillTimer;
	float		m_fSpawnTimer;				// spear,,�ε� Ÿ�̸ӷ� �� �һ���
	float		m_fTimer;					// �÷��̾� �̻��� �����ֱ� ���ſ�

	vector<CShield*>	m_vecShield;
	vector<CSpear*>		m_vecSpear;	

public:
	CBoss_Markoth();
	virtual ~CBoss_Markoth();

	virtual CBoss_Markoth* clone();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionKeep(CCollider* pOther);

	void setSkillCooldown(float cd);
	void setSpawnTimer(float time);
	vector<CShield*>& getVecShield();
	vector<CSpear*>& getVecSpear();

	void spawnShield();
	void createSpear();
private:
	void createShield(float theta = 0.f, bool rightRot = true);

	virtual void death();
};

// skill
#define B_SKILL_DURA		6
#define B_SKILL_COOL		12
#define B_SKILL_RAD			300

// shield
#define B_SHD_SPD			3.f			// ���� �ӵ� (radian)
#define B_SHD_RAD			285				// ȸ�� ũ�� ������

// spear
#define B_SPR_SPD_1P		1020			// 1 ������ spear �ӵ�
#define B_SPR_SPD_2P		1180			// 2
#define B_SPR_COOL			1.25f

// boss
#define B_HPMAX				20
#define B_SPD				150
#define B_READY_DURA		3.25f
#define B_ACCEL				(2.f /** B_SHD_SPD / B_READY_DURA*/)
#define B_DMG_DELAY			0.4				// �÷��̾� �̻��Ϸ� ���� ���� �Դ� �ֱ�

// collider size
#define SB_NmSIZEX			190				//
#define SB_NmSIZEY			310
#define SB_MdSIZEX			210				// 
#define SB_MdSIZEY			290
#define SB_SkSIZEX			390				//
#define SB_SkSIZEY			215

// move area ����
#define SB_AREA_x			250
#define SB_AREA_y			620
#define SB_AREA_X			2750
#define SB_AREA_Y			1170
#define SB_AREA_ADDX		600
#define SB_AREA_ADDY		350