#pragma once

class CMonster;
class CState_Mons;
enum class eSTATE_MONS;

class CAI
{
	friend class CMonster;

	map<eSTATE_MONS, CState_Mons*> m_mapState;
	CMonster*		m_pOwner;
	eSTATE_MONS*	m_pCurState;

public:
	CAI();
	~CAI();

	void update(UINT& chk);

	CMonster* getOwner();

	CState_Mons* findState(eSTATE_MONS state);
	eSTATE_MONS* getCurState();

	void setCurState(eSTATE_MONS state);

	void addState(CState_Mons* pState);
	void changeState(eSTATE_MONS nextState);
};

