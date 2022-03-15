#include "framework.h"
#include "CButtonUI.h"

// 부모의 기본 생성자를 재정의 했기 때문에 
CButtonUI::CButtonUI()
	: CUI(false)
{
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{
}
