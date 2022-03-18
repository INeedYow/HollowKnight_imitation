#include "framework.h"
#include "CState.h"
#include "CAI.h"
#include "CPlayer.h"

CState::CState(eSTATE_PLAYER state)
{
    m_pOwner = nullptr;
    m_ePlayerState = state;
}

CState::~CState()
{
}

CAI* CState::getOwner()
{
    return m_pOwner;
}

eSTATE_PLAYER CState::getState()
{
    return m_ePlayerState;
}

CPlayer* CState::getPlayer()
{
    return m_pOwner->getOwner();
}
