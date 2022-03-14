#include "framework.h"
#include "CScene_Title.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	CScene::update();

	if (KEY_ON(VK_TAB))
	{
		changeScn(GROUP_SCENE::TOOL);
	}

	if (KEY_ON(VK_LBUTTON))
	{
		fPoint fptLookAt = CCameraManager::getInst()->getRealPos(mousePos());
		CCameraManager::getInst()->setFocus(fptLookAt);
	}
}

void CScene_Title::enter()
{
	//// 타일 로딩
	//wstring path = CPathManager::getInst()->GetContentPath();
	//path += L"tile\\Start.tile";
	//loadTile(path);

	// Player 추가
	CObject* pPlayer = new CPlayer;
	pPlayer->setPos(fPoint(200, 200));
	addObject(pPlayer, OBJ::PLAYER);

	// Monster 추가
	CMonster* pMonster = new CMonster;
	pMonster->setPos(fPoint(1100, 350));
	pMonster->setCenterPos(pMonster->getPos());
	addObject(pMonster, OBJ::MONSTER);

	checkGrp(OBJ::PLAYER, OBJ::MONSTER);
	checkGrp(OBJ::MISSILE_PLAYER, OBJ::MONSTER);

	// Camera Look 지정
	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Title::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}
