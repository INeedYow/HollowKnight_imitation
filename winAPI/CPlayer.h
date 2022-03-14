#pragma once
#include "CObject.h"



class CTexture;
enum class ePLAYER_ACTION;

class CPlayer : public CObject
{
	UCHAR		m_ucState;				// 상태값 (무적, Item 보유상황)

	CTexture*	m_pTex;

	float		m_fSpd;
	float		m_fJumpSpd;
	float		m_fGravity;
	float		m_fTimer;
	int			m_iBottomCnt;

	enum class eACT
	{
		IDLE,
		WALK,
		JUMP,
		FALL,
		ATTACK,
		HANG,

		LOOKUP,
		LOOKDOWN,
		DEATH,

		END
	};

	void createMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	virtual void update();
	virtual void render(HDC hDC);
};

