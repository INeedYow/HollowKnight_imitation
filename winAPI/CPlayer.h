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
	UINT		m_uiSoul;
	UINT		m_uiZio;

	float		m_fSpdX;
	float		m_fSpdY;
	float		m_fGravity;
	int			m_iBottomCnt;

	float		m_fJumpTimer;
	//float		m_fFireTimer;			// attack 타이머로 될듯
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