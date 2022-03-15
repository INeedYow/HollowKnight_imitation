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

		if (pUI->IsMouseOn())
		{
			pUI->MouseOn();

			if (KeyDown(VK_LBUTTON))
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (KeyUp(VK_LBUTTON))
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}
				pUI->m_bLbtnDown = false;
			}
		}
		else
		{
			if (KeyUp(VK_LBUTTON))
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
