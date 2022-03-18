#include "framework.h"
#include "CState_Idle.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Idle::CState_Idle(eSTATE_PLAYER state)
	: CState(state)
{

}

CState_Idle::~CState_Idle()
{
}

// TODO getOwner() 두 단계 최선인가
void CState_Idle::update()
{
	//fPoint pos = getOwner()->getOwner()->getPos();

	//// run
	//if (KEY_HOLD(VK_LEFT))
	//{
	//	m_uiState &= ~(SP_DIR);
	//	m_eAction = eSTATE_PLAYER::RUN;
	//}

	//else if (KEY_HOLD(VK_RIGHT))
	//{
	//	m_uiState |= SP_DIR;
	//	m_eAction = eSTATE_PLAYER::RUN;
	//}
	//// jump
	//else if (KEY_ON('Z'))
	//{
	//	pos.y--;
	//	m_eAction = eSTATE_PLAYER::JUMP;
	//	m_uiState |= SP_JUMPHOLD;
	//	m_uiState |= SP_AIR;
	//}
	//// slash
	//else if (KEY_ON('X'))
	//{
	//	if (KEY_HOLD(VK_UP))
	//	{
	//		m_eAction = eSTATE_PLAYER::UPSLASH;
	//	}
	//	else
	//	{
	//		m_eAction = eSTATE_PLAYER::SLASH1;
	//	}
	//}

	//// focus
	//if (KEY_HOLD('A'))
	//{
	//	m_fTimer += fDT;

	//	if (m_fTimer >= 0.5f)
	//	{
	//		m_eAction = eSTATE_PLAYER::FOCUS;
	//		m_fTimer = 0.f;
	//	}
	//}
	//// fire
	//else if (KEY_OFF('A'))
	//{
	//	m_fTimer = 0.f;

	//	if (m_uiSoul >= P_FIRESOUL)
	//	{
	//		m_eAction = eSTATE_PLAYER::FIRE;
	//	}
	//}

	//playAnim(L"Idle");
	
	
}

void CState_Idle::enter()
{
}

void CState_Idle::exit()
{
}
