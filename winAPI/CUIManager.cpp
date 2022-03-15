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

void CUIManager::update()
{	
	CUI* pFocusUI = getFocusUI();

	if (nullptr == pFocusUI) return;

	// 포커스 된 UI 상태만 업데이트
	CUI* pTargetUI = getTargetUI(pFocusUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->mouseOn();

		if (KEY_ON(VK_LBUTTON))
		{
			pTargetUI->mouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (KEY_OFF(VK_LBUTTON))
		{
			pTargetUI->mouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->mouseLbtnClicked();
			}
			pTargetUI->m_bLbtnDown = false;
		}
	}
	
}

void CUIManager::setFocusUI(CUI* pUI)
{
	if (m_pFocusUI == pUI) return;			// 이미 포커싱 된 UI인 경우
	if (nullptr == m_pFocusUI)				// 이전 포커스 UI가 없는 경우
	{
		m_pFocusUI = pUI;
		return;
	}

	m_pFocusUI = pUI;

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>& vecUI = pCurScene->getUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusUI == *iter)			// 포커스된 UI를 찾음
			break;
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusUI);			// 지우고 추가해서 상단에 노출
}

CUI* CUIManager::getFocusUI()
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>& vecUI = pCurScene->getUIGroup();
	
	CUI* pFocusUI = m_pFocusUI;

	// 클릭 없으면 포커스 유지
	if (!KEY_OFF(VK_LBUTTON))
		return pFocusUI;

	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); iter++)
	{
		if (((CUI*)*iter)->isMouseOn())			// 마우스 올라간 UI 있으면 
			targetIter = iter;
	}

	if (vecUI.end() == targetIter)					// 없으면
		return nullptr;

	pFocusUI = (CUI*)*targetIter;

	// 상단으로 보여줄 UI를 지우고 새로 추가해서 상단에 노출되도록
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusUI);
	m_pFocusUI = pFocusUI;

	return pFocusUI;
}

// UI가 부모 자식 겹쳐있는데 부모가 업데이트가 먼저 돼서 자식 UI를 클릭해도 부모 UI가 반응하기 때문에
// 자식 UI들 확인해서 자식 UI에 마우스가 올라가 있으면 자식 UI가 선택된 걸로 바꿔줌
CUI* CUIManager::getTargetUI(CUI* pParentUI)
{	
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	CUI* pTargetUI = nullptr;

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
