#include "framework.h"
#include "CPanelUI.h"

CPanelUI::CPanelUI()
	: CUI(false)
{
	m_fpDragStart = {};
}

CPanelUI::~CPanelUI()
{
}

CPanelUI* CPanelUI::clone()
{
	return new CPanelUI(*this);
}

void CPanelUI::mouseOn()
{
	if (isLbtnDown())
	{
		fPoint diff = mousePos() - m_fpDragStart;

		fPoint curPos = getPos();
		curPos += diff;
		setPos(curPos);

		m_fpDragStart = mousePos();
	}
}

void CPanelUI::mouseLbtnDown()
{
	m_fpDragStart = mousePos();
}

void CPanelUI::mouseLbtnUp()
{
}
