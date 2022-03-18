#include "framework.h"
#include "CAI.h"
#include "CState.h"

CAI::CAI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

CAI::~CAI()
{
	for (map<eSTATE_PLAYER, CState*>::iterator iter = m_mapState.begin(); 
		iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapState.clear();
}

void CAI::addState(CState* pState)
{
	CState* pNewState = findState(pState->getState());
	assert(!pNewState);

	m_mapState.insert(make_pair(pState->getState(), pState));
	pState->m_pOwner = this;
}

void CAI::changeState(eSTATE_PLAYER nextState)
{
	CState* pNextState = findState(nextState);
	assert(m_pCurState != pNextState);

	m_pCurState->exit();
	m_pCurState = pNextState;
	m_pCurState->enter();
}

void CAI::update()
{
	m_pCurState->update();
}

CPlayer* CAI::getOwner()
{
	return m_pOwner;
}

CState* CAI::findState(eSTATE_PLAYER state)
{
	map<eSTATE_PLAYER, CState*>::iterator iter = m_mapState.find(state);
	
	if (m_mapState.end() == iter)
		return nullptr;
	
	return iter->second;
}

void CAI::setCurState(eSTATE_PLAYER state)
{
	m_pCurState = findState(state);
	assert(m_pCurState);
}