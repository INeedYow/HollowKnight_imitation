#include "framework.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CScene_Stage01.h"
#include "CScene_Stage02.h"
#include "CScene_Stage03.h"
#include "CScene_Stage04.h"

CSceneManager::CSceneManager()
{
	for (int i = 0; i < (int)eSCENE::SIZE; i++)
		m_pArrScene[i] = nullptr;
	m_pCurScene = nullptr;
}
CSceneManager::~CSceneManager()
{
	for (int i = 0; i < (int)eSCENE::SIZE; i++)
	{
		if (nullptr != m_pArrScene[i])
			delete m_pArrScene[i];
	}
}

void CSceneManager::sceneChange(eSCENE scene)
{
	m_pCurScene->exit();
	m_pCurScene = m_pArrScene[(int)scene];
	m_pCurScene->enter();
}


void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalUpdate();			// 모든 오브젝트의 업데이트가 끝난 후 동시간대 결과로써 처리
}

void CSceneManager::render(HDC hDC)
{
	m_pCurScene->render(hDC);
}

// 배열의 원소에 바로 동적할당하면 됨
void CSceneManager::init()
{
	m_pArrScene[(int)eSCENE::TITLE] = new CScene_Title;
	m_pArrScene[(int)eSCENE::TOOL] = new CScene_Tool;
	m_pArrScene[(int)eSCENE::STAGE_01] = new CScene_Stage01;
	m_pArrScene[(int)eSCENE::STAGE_02] = new CScene_Stage02;
	m_pArrScene[(int)eSCENE::STAGE_03] = new CScene_Stage03;
	m_pArrScene[(int)eSCENE::STAGE_04] = new CScene_Stage04;

	m_pCurScene = m_pArrScene[(int)eSCENE::TITLE];
	m_pCurScene->enter();
}

CScene* CSceneManager::getCurScene()
{
	return m_pCurScene;
}
