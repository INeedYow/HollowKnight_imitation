#pragma once
#include "CScene.h"
class CScene_Stage03 : public CScene
{
public:
	CScene_Stage03();
	virtual ~CScene_Stage03();

	virtual void update();

	virtual void enter();
	virtual void exit();
};