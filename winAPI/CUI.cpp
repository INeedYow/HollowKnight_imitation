#include "framework.h"
#include "CUI.h"

#include "SelectGDI.h"

CUI::CUI(bool bCamAff)
{
	m_pParentUI = nullptr;
	m_fpFinalPos = {};
	m_bCamAffect = false;
	m_bMouseOn = false;
	m_bLbtnDown = false;
}

CUI::~CUI()
{	// �ڽ� UI���� ����
	for (int i = 0; i < m_vecChildUI.size(); i++)
	{
		if (nullptr != m_vecChildUI[i])
			delete m_vecChildUI[i];
	}
}

CUI* CUI::clone()
{
	return new CUI(*this);
}

void CUI::update()
{
	updateChild();
}

void CUI::finalUpdate()
{
	CObject::finalUpdate();

	m_fpFinalPos = getPos();
	if (getParent())
	{	// �θ� �ִ� ��� �ڽ� UI�� ��ġ�� �����
		fPoint parentPos = getParent()->getFinalPos();
		m_fpFinalPos += parentPos;
	}

	mouseOnChk();

	finalUpdateChild();
}

void CUI::render(HDC hDC)
{
	fPoint pos = getFinalPos();
	fPoint size = getSize();

	if (m_bCamAffect)
	{
		pos = rendPos(pos);
	}
	
	if (m_bLbtnDown)
	{
		SelectGDI pen(hDC, PEN::GREEN);

		Rectangle(hDC,
			(int)(pos.x),
			(int)(pos.y),
			(int)(pos.x + size.x),
			(int)(pos.y + size.y));
	}
	else
	{
		Rectangle(hDC,
			(int)(pos.x),
			(int)(pos.y),
			(int)(pos.x + size.x),
			(int)(pos.y + size.y));
	}

	rendChild(hDC);
}

void CUI::updateChild()
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalUpdateChild()
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalUpdate();
	}
}

void CUI::rendChild(HDC hDC)
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(hDC);
	}
}

void CUI::mouseOn()
{
	int a = 0;
}

void CUI::mouseLbtnDown()
{
	int a = 0;
}

void CUI::mouseLbtnUp()
{
	int a = 0;
}

void CUI::mouseLbtnClicked()
{
	int a = 0;
}

fPoint CUI::getFinalPos()
{
	return m_fpFinalPos;
}

CUI* CUI::getParent()
{
	return m_pParentUI;
}

bool CUI::isMouseOn()
{
	return m_bMouseOn;
}

bool CUI::getCamAffect()
{
	return m_bCamAffect;
}

void CUI::addChild(CUI* pUI)
{
	m_vecChildUI.push_back(pUI);
	pUI->m_pParentUI = this;
}

void CUI::mouseOnChk()
{
	fPoint mPos = mousePos();
	fPoint size = getSize();

	if (m_bCamAffect)
		mPos = rendPos(mPos);

	if (m_fpFinalPos.x <= mPos.x && mPos.x <= m_fpFinalPos.x + size.x && 
		m_fpFinalPos.y <= mPos.y && mPos.y <= m_fpFinalPos.y + size.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
