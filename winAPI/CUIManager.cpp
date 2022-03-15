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

	// ��Ŀ�� �� UI ���¸� ������Ʈ
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
	if (m_pFocusUI == pUI) return;			// �̹� ��Ŀ�� �� UI�� ���
	if (nullptr == m_pFocusUI)				// ���� ��Ŀ�� UI�� ���� ���
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
		if (m_pFocusUI == *iter)			// ��Ŀ���� UI�� ã��
			break;
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusUI);			// ����� �߰��ؼ� ��ܿ� ����
}

CUI* CUIManager::getFocusUI()
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>& vecUI = pCurScene->getUIGroup();
	
	CUI* pFocusUI = m_pFocusUI;

	// Ŭ�� ������ ��Ŀ�� ����
	if (!KEY_OFF(VK_LBUTTON))
		return pFocusUI;

	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); iter++)
	{
		if (((CUI*)*iter)->isMouseOn())			// ���콺 �ö� UI ������ 
			targetIter = iter;
	}

	if (vecUI.end() == targetIter)					// ������
		return nullptr;

	pFocusUI = (CUI*)*targetIter;

	// ������� ������ UI�� ����� ���� �߰��ؼ� ��ܿ� ����ǵ���
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusUI);
	m_pFocusUI = pFocusUI;

	return pFocusUI;
}

// UI�� �θ� �ڽ� �����ִµ� �θ� ������Ʈ�� ���� �ż� �ڽ� UI�� Ŭ���ص� �θ� UI�� �����ϱ� ������
// �ڽ� UI�� Ȯ���ؼ� �ڽ� UI�� ���콺�� �ö� ������ �ڽ� UI�� ���õ� �ɷ� �ٲ���
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
