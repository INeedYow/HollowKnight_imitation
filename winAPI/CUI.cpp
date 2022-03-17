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

CUI::CUI(const CUI& other)
	: CObject(other)		// 부모의 복사생성자를 지정해주어야 함
{
	m_pParentUI = nullptr;
	m_bCamAffect = other.m_bCamAffect;
	m_bMouseOn = false;
	m_bLbtnDown = false;

	for (UINT i = 0; i < other.m_vecChildUI.size(); i++)
	{	// 자식 UI 개수만큼 생성 해줌
		addChild(other.m_vecChildUI[i]->clone());
	}
}

CUI::~CUI()
{	// 자식 UI벡터 해제
	for (int i = 0; i < m_vecChildUI.size(); i++)
	{
		if (nullptr != m_vecChildUI[i])
			delete m_vecChildUI[i];
	}
}

void CUI::update()
{
	updateChild();
}

void CUI::finalUpdate()
{
	CObject::finalUpdate();

	m_fpFinalPos = getPos();
	if (getParentUI())
	{	// 부모가 있는 경우 자식 UI의 위치는 상대적
		fPoint parentPos = getParentUI()->getFinalPos();
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
		SelectGDI pen(hDC, ePEN::GREEN);

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

CUI* CUI::getParentUI()
{
	return m_pParentUI;
}

const vector<CUI*>& CUI::getChildUI()
{
	return m_vecChildUI;
}

bool CUI::isMouseOn()
{
	return m_bMouseOn;
}

bool CUI::isCamAffect()
{
	return m_bCamAffect;
}

bool CUI::isLbtnDown()
{
	return m_bLbtnDown;
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
