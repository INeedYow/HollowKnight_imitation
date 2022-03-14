#include "framework.h"
#include "CUI.h"

CUI::CUI()
{
	m_pParentUI = nullptr;
	m_fpFinalPos = {};
}

CUI::~CUI()
{	// 자식 UI벡터 해제
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
	{	// 부모가 있는 경우 자식 UI의 위치는 상대적
		fPoint parentPos = getParent()->getFinalPos();
		m_fpFinalPos += parentPos;
	}

	finalUpdateChild();
}

void CUI::render(HDC hDC)
{
	fPoint pos = getFinalPos();
	fPoint size = getSize();

	Rectangle(hDC,
		(int)(pos.x),
		(int)(pos.y),
		(int)(pos.x + size.x),
		(int)(pos.y + size.y));

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
}

void CUI::mouseLbtnDown()
{
}

void CUI::mouseLbtnUp()
{
}

void CUI::mouseLbtnClicked()
{
}

fPoint CUI::getFinalPos()
{
	return m_fpFinalPos;
}

CUI* CUI::getParent()
{
	return m_pParentUI;
}

void CUI::addChild(CUI* pUI)
{
	m_vecChildUI.push_back(pUI);
	pUI->m_pParentUI = this;
}
