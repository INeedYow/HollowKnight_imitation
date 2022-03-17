#pragma once
#include "CObject.h"

class CTexture;
enum class eACT;

class CPlayer : public CObject
{
	eACT		m_eAction;				// 행동 상태값
	UINT		m_uiState;				// 상태값 (무적, Item 보유상황등 체크)

	CTexture*	m_pTex;

	UINT		m_uiHP;
	float		m_uiSoul;
	UINT		m_uiZio;

	float		m_fSpdX;
	float		m_fSpdY;
	float		m_fGravity;
	int			m_iBottomCnt;

	float		m_fTimer;				// jump, focus 등에서 쓸 타이머
	float		m_fAttackDelay;			//

	
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
	FOCUS,

	STUN,

	LOOKUP,
	LOOKDOWN,
	DEATH,

	END
};

// # state
#define P_SPDX				150
#define P_SPDY				350
#define P_GRAV				1200
#define P_GRAVMAX			(P_GRAV * 3)
#define P_FIRESOUL			30
#define P_FOCUSSOUL			33
#define P_FIREDELAY			0.5
#define P_ATTDELAY			0.4

// 플레이어 상태
#define SP_DIR				0x0001			// 좌, 우 방향
#define SP_AIR				0x0002			// 공중에 뜸
#define SP_JUMPHOLD			0x0004			// 점프 키 누르고 있는 상황

#define SP_INVIN			0x0010			// 무적 (임시)
#define SP_GETDMG			0x0020			// 피격 등으로 무적

// item 보유
#define SP_ITEM1			0x0100
#define SP_ITEM2			0x0200