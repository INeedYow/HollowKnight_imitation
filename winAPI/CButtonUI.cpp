#include "framework.h"
#include "CButtonUI.h"

// 부모의 기본 생성자를 재정의 했기 때문에 
CButtonUI::CButtonUI()
	: CUI(false)
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::mouseOn()
{
}

void CButtonUI::mouseLbtnDown()
{
}

void CButtonUI::mouseLbtnUp()
{
}

void CButtonUI::mouseLbtnClicked()
{
	if (nullptr != m_pFunc)
		m_pFunc(m_pParam1, m_pParam2);
}

void CButtonUI::setClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}