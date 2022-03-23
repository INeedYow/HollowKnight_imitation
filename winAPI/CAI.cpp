#include "framework.h"
#include "CAI.h"
#include "CState_Mons.h"

CAI::CAI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

CAI::~CAI()
{
	for (map<eSTATE_MONS, CState_Mons*>::iterator iter = m_mapState.begin();
		iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapState.clear();
}

void CAI::update(UINT& chk)
{
}

CMonster* CAI::getOwner()
{
	return m_pOwner;
}

CState_Mons* CAI::findState(eSTATE_MONS state)
{
	map<eSTATE_MONS, CState_Mons*>::iterator iter = m_mapState.find(state);

	if (m_mapState.end() == iter)
		return nullptr;

	return iter->second;
}

eSTATE_MONS* CAI::getCurState()
{
	return m_pCurState;
}

void CAI::setCurState(eSTATE_MONS state)
{
}

void CAI::addState(CState_Mons* pState)
{
	CState_Mons* pNewState = findState(pState->getState());
	assert(!pNewState);

	m_mapState.insert(make_pair(pState->getState(), pState));
	pState->m_pOwner = this;
}

void CAI::changeState(eSTATE_MONS nextState)
{
}
