#pragma once
#include "CScene.h"

class CScene_Stage01 : public CScene
{

public:
	CScene_Stage01();
	virtual ~CScene_Stage01();

	virtual void update();

	virtual void enter();
	virtual void exit();
};

#define STG01_SIZEX 3840
#define STG01_SIZEY 2160
