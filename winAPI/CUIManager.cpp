#include "framework.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
	m_pFocusUI = nullptr;
}

CUIManager::~CUIManager()
{

}

// TODO
void CUIManager::update()
{	
	m_pFocusUI = getFocusUI();
	CUI* pUI = getTargetUI(m_pFocusUI);

	if (nullptr != pUI)
	{
		pUI->mouseOn();

		if (KEY_ON(VK_LBUTTON))
		{
			pUI->mouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (KEY_OFF(VK_LBUTTON))
		{
			pUI->mouseLbtnUp();

			if (pUI->m_bLbtnDown)
			{
				pUI->mouseLbtnClicked();
			}
			pUI->m_bLbtnDown = false;
		}
	}
	
}

void CUIManager::setFocusUI(CUI* pUI)
{
	// 예외처리
	if (m_pFocusUI == pUI || nullptr == m_pFocusUI)
	{
		m_pFocusUI = pUI;
		return;
	}

	m_pFocusUI = pUI;

	if (nullptr == m_pFocusUI)
		return;

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>& vecUI = pCurScene->getUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusUI);
}

// UI가 부모 자식 겹쳐있는데 부모가 업데이트가 먼저 돼서 자식 UI를 클릭해도 부모 UI가 반응하기 때문에
// 자식 UI들 확인해서 자식 UI에 마우스가 올라가 있으면 자식 UI가 선택된 걸로 바꿔줌
CUI* CUIManager::getTargetUI(CUI* pParentUI)
{	
	list<CUI*> queue;
	vector<CUI*> vecNoneTarget;
	
	CUI* pTargetUI = nullptr;

	if (nullptr == pParentUI)
		return nullptr;

	queue.push_back(pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->isMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->getChildUI();
		for (UINT i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (KEY_OFF(VK_LBUTTON))
	{
		for (UINT i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	return pTargetUI;
}

CUI* CUIManager::getFocusUI()
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>& vecUI = pCurScene->getUIGroup();
	CUI* pFocusUI = m_pFocusUI;

	if (!KEY_ON(VK_LBUTTON))
	{
		return pFocusUI;
	}

	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->isMouseOn())
		{
			targetiter = iter;
		}
	}

	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusUI = (CUI*)*targetiter;

	vecUI.erase(targetiter);
	vecUI.push_back(pFocusUI);

	return pFocusUI;
}