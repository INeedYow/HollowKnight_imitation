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
	// ����ó��
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

// UI�� �θ� �ڽ� �����ִµ� �θ� ������Ʈ�� ���� �ż� �ڽ� UI�� Ŭ���ص� �θ� UI�� �����ϱ� ������
// �ڽ� UI�� Ȯ���ؼ� �ڽ� UI�� ���콺�� �ö� ������ �ڽ� UI�� ���õ� �ɷ� �ٲ���
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