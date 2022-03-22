#pragma once
#include "CScene.h"
class CScene_Stage02 :
    public CScene
{
public:
	CScene_Stage02();
	virtual ~CScene_Stage02();

	virtual void update();

	virtual void enter();
	virtual void exit();
};

