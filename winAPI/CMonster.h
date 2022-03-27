#pragma once
#include "CObject.h"

class CAI;

struct tMonsInfo
{
	int		iHP;
	float	fSpd;
	fVec2	fvDir;
	float	fDist;					// �÷��̾�� �Ÿ�
	float	fTraceRange;			// trace �ϴ� �Ÿ�
	float	fAtkRange;				// ���� ��Ÿ�

	fVec2	fvKnockBackDir;
	float	fKnockBackSpd;
	float	fKnockBackTimer;
};


class CMonster : public CObject
{
private:
	tMonsInfo	m_tInfo;
	UINT		m_uiCheck;		// ���� ��Ʈüũ��

	CTexture*	m_pTex;
	CAI*		m_pAI;

public:
	void printInfo(HDC hDC);

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* clone() = 0;

	virtual void update();
	virtual void render(HDC hDC) = 0;

	virtual void collisionEnter(CCollider* pOther){}
	virtual void collisionKeep(CCollider* pOther){}
	virtual void collisionExit(CCollider* pOther){}

	void setAI(CAI* pAI);
	void setTex(const wstring& strName, const wstring& strPath);
	void setMonsInfo(const tMonsInfo& info);
	void setCheck(UINT chk, bool isOn);

	const tMonsInfo& getMonsInfo();
	CTexture* getTex();
	CAI* getAI();
	bool isCheck(UINT chk);

	virtual void death() = 0;		// �׾��� �� �ִϸ��̼� �� ó��

	void playAnim(const wstring& keyWord);

	static CMonster* create(eOBJNAME eName, fPoint pos);
};

//
enum class eSTATE_MONS
{
	STOP,
	PATROL,
	TRACE,
	ATTACK,

	DIE,


	// boss
	IDLE,
	MOVE,
	SPAWN,
	READY,
	SKILL,
	DEATH,

	END
};

#define SM_KBTIME				0.2
#define SM_KBSPD_L				500
#define SM_KBSPD_M				700

//
#define SM_TRACE				0x0001		// ���󰡴� ����� �ִ� ��������
#define SM_FALL					0x0002		// �������� ��
#define SM_DEATH				0x0004		// setInfo���� �ߺ� deathȣ�� ������

#define SM_DIR					0x0010		
#define SM_TURN					0x0020		// ������ȯ

//
#define SB_TIMER			0x00010000		// ���� ��Ÿ�� timer ���� ��������