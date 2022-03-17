#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene* m_pArrScene[(int)eSCENE::SIZE];
	CScene* m_pCurScene;

public:
	void sceneChange(eSCENE scene);

	void update();
	void render(HDC hDC);
	void init();

	CScene* getCurScene();
};