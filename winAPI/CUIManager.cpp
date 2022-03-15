#include "framework.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{

}

CUIManager::~CUIManager()
{

}

void CUIManager::update()
{	
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	const vector<CObject*>& vecUI = pCurScene->getGroupObject(OBJ::UI);

	for (UINT i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];
		pUI = getTargetUI(pUI);			//

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
}

// UI가 부모 자식 겹쳐있는데 부모가 업데이트가 먼저 돼서 자식 UI를 클릭해도 부모 UI가 반응하기 때문에
// 자식 UI들 확인해서 자식 UI에 마우스가 올라가 있으면 자식 UI가 선택된 걸로 바꿔줌
CUI* CUIManager::getTargetUI(CUI* pParentUI)
{	
	list<CUI*> queue;
	vector<CUI*> vecNoneTarget;
	
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
