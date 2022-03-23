#include "framework.h"
#include "CStatus.h"
#include "CState_Player.h"

CStatus::CStatus()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

CStatus::~CStatus()
{
	for (map<eSTATE_PLAYER, CState_Player*>::iterator iter = m_mapState.begin(); 
		iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapState.clear();
}

void CStatus::addState(CState_Player* pState)
{
	CState_Player* pNewState = findState(pState->getState());
	assert(!pNewState);

	m_mapState.insert(make_pair(pState->getState(), pState));
	pState->m_pOwner = this;
}

void CStatus::changeState(eSTATE_PLAYER nextState)
{
	CState_Player* pNextState = findState(nextState);
	//assert(m_pCurState != pNextState);

	m_pCurState->exit();
	m_pCurState = pNextState;
	m_pCurState->enter();
}

void CStatus::update(UINT& chk)
{
	m_pCurState->update(chk);
}

CPlayer* CStatus::getOwner()
{
	return m_pOwner;
}

CState_Player* CStatus::getCurState()
{
	return m_pCurState;
}

CState_Player* CStatus::findState(eSTATE_PLAYER state)
{
	map<eSTATE_PLAYER, CState_Player*>::iterator iter = m_mapState.find(state);
	
	if (m_mapState.end() == iter)
		return nullptr;
	
	return iter->second;
}

void CStatus::setCurState(eSTATE_PLAYER state)
{
	m_pCurState = findState(state);
	assert(m_pCurState);
}