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
	m_pCurScene->finalUpdate();			// ��� ������Ʈ�� ������Ʈ�� ���� �� ���ð��� ����ν� ó��
}

void CSceneManager::render(HDC hDC)
{
	m_pCurScene->render(hDC);
}

// �迭�� ���ҿ� �ٷ� �����Ҵ��ϸ� ��
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
