#include "framework.h"
#include "CButtonUI.h"

// �θ��� �⺻ �����ڸ� ������ �߱� ������ 
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
