#pragma once
#include "CObject.h"

class CTexture;
enum class eACT;

class CPlayer : public CObject
{
	eACT		m_eAction;				// �ൿ ���°�
	UINT		m_uiState;				// ���°� (����, Item ������Ȳ�� üũ)

	CTexture*	m_pTex;

	UINT		m_uiHP;
	UINT		m_uiSoul;
	UINT		m_uiZio;

	float		m_fSpdX;
	float		m_fSpdY;
	float		m_fGravity;
	int			m_iBottomCnt;

	float		m_fJumpTimer;
	//float		m_fFireTimer;			// attack Ÿ�̸ӷ� �ɵ�
	float		m_fAttackTimer;

	
private:
	void createMissile();
	void firstSlash();
	void secondSlash();
	void upSlash();
	void downSlash();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	void playAnim(const wstring& commonName);

	virtual void update();
	virtual void render(HDC hDC);

	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);
};

enum class eACT
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	HANG,
	SLASH1,
	SLASH2,
	UPSLASH,
	DOWNSLASH,
	FIRE,


	LOOKUP,
	LOOKDOWN,
	DEATH,

	END
};

// # state
#define P_SPDX				150
#define P_SPDY				300
#define P_GRAV				1000
#define P_GRAVMAX			(P_GRAV * 3)
#define P_FIRESOUL			30
#define P_FIREDELAY			0.5
#define P_ATTDELAY			0.4

// �÷��̾� ����
#define SP_DIR				0x0001			// ��, �� ����
#define SP_AIR				0x0002			// ���߿� ��
#define SP_JUMPHOLD			0x0004			// ���� Ű ������ �ִ� ��Ȳ

#define SP_INVIN			0x0010			// ���� (�ӽ�)
#define SP_GETDMG			0x0020			// �ǰ� ������ ����

// item ����
#define SP_ITEM1			0x0100
#define SP_ITEM2			0x0200