#include "framework.h"
#include "CScene_Stage03.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CBoss_Markoth.h"

CScene_Stage03::CScene_Stage03()
{
}

CScene_Stage03::~CScene_Stage03()
{
}

void CScene_Stage03::update()
{
	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_04);
}

void CScene_Stage03::enter()
{
}

void CScene_Stage03::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.8f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
