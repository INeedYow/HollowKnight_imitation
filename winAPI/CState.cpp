#include "framework.h"
#include "CState.h"

CState::CState(MON_STATE state)
{
}

CState::~CState()
{
}

AI* CState::getOwner()
{
    return m_pOwner;
}
