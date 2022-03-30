#pragma once
#include "CScene.h"
class CScene_Stage04 : public CScene
{
	bool m_bBGM;
public:
	CScene_Stage04();
	virtual ~CScene_Stage04();

	virtual void update();

	virtual void enter();
	virtual void exit();
};
