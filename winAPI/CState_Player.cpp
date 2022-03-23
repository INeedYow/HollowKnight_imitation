#include "framework.h"
#include "CState_Player.h"
#include "CStatus.h"
#include "CPlayer.h"
#include "SelectGDI.h"

CState_Player::CState_Player(eSTATE_PLAYER state)
{
    m_pOwner = nullptr;
    m_ePlayerState = state;
}

CState_Player::~CState_Player()
{
}

CStatus* CState_Player::getOwner()
{
    return m_pOwner;
}

eSTATE_PLAYER CState_Player::getState()
{
    return m_ePlayerState;
}

CPlayer* CState_Player::getPlayer()
{
    return m_pOwner->getOwner();
}