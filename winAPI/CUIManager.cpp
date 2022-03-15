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

// UI�� �θ� �ڽ� �����ִµ� �θ� ������Ʈ�� ���� �ż� �ڽ� UI�� Ŭ���ص� �θ� UI�� �����ϱ� ������
// �ڽ� UI�� Ȯ���ؼ� �ڽ� UI�� ���콺�� �ö� ������ �ڽ� UI�� ���õ� �ɷ� �ٲ���
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
