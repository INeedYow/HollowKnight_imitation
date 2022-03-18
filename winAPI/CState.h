#pragma once

class AI;

enum class MON_STATE{};

class CState
{
	friend class AI;

private:
	AI*			m_pOwner;
	MON_STATE	m_eState;

public:
	CState(MON_STATE state);
	virtual ~CState();

	AI* getOwner();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

};

