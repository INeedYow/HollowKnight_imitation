#pragma once
#include "CScene.h"

class CScene_Stage01 : public CScene
{
	bool	m_bBGM;

public:
	CScene_Stage01();
	virtual ~CScene_Stage01();

	virtual void update();

	virtual void enter();
	virtual void exit();

};