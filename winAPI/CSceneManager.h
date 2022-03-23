#pragma once

class CScene;
class CPlayer;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene* m_pArrScene[(int)eSCENE::SIZE];
	CScene* m_pCurScene;

	CPlayer* m_pPlayer;

public:
	void sceneChange(eSCENE scene);

	void update();
	void render(HDC hDC);
	void init();

	CScene* getCurScene();

	void registerPlayer(CPlayer* pPlayer);
	fPoint getPlayerPos();
};