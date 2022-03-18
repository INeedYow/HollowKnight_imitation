﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

// 속성 -> 일반 -> 출력 디렉터리 : $(SolutionDir)Output\$(Configuration)\
	// -> 디버깅 -> 작업 디렉터리 : $(ProjectDir)..\Output\Release\

#pragma once

#pragma comment(lib, "msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <time.h>
#include <math.h>
#include <assert.h>

// # STL
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

// # 전역 변수
extern HWND			hWnd;
extern HINSTANCE	hInst;
extern bool			g_bDebug;


// # 전처리기
#define WINSTYLE			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define WINPOSX				100
#define WINPOSY				100
#define WINSIZEX			1280
#define WINSIZEY			720

	// 충돌관련 함수
#define ISCOLLPC			isCollisionPointToCircle
#define ISCOLLCR			isCollisionCircleToRect
#define ISCOLLCC			isCollisionCircleToCircle
#define ISCOLLPR			isCollisionPointToRect
#define ISCOLLRR			isCollisionRectToRect

#define COLLRR				collisionRectToRect

#define PI					3.141592

 // enum class 열거형
#define eOBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	BACKGROUND,
	FRONTGROUND,
	TILE,
	IMAGE,

	ATTACK,
	MISSILE_PLAYER,
	MISSILE_MONSTER,
	SHIELD,

	MONSTER,
	BOSS,
	PLAYER,

	EFFECT,

	TEST,

	UI,
	SIZE
};

#define eOBJNAME	OBJECT_NAME
enum class OBJECT_NAME
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLAYER,
	MONSTER,
	ATTACK,
	MISSILE_PLAYER,
	MISSILE_MONSTER,
	EFFECT,
	BOSS,
	SHIELD,
	IMAGE,

	TEST,

	SIZE
};

#define eSCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	TOOL,
	STAGE_01,
	STAGE_02,

	SIZE
};

// GDI
#define eBRUSH	TYPE_BRUSH
enum class TYPE_BRUSH
{
	HOLLOW,

	SIZE
};

#define ePEN		TYPE_PEN
enum class TYPE_PEN
{
	RED,
	GREEN,
	BLUE,

	SIZE
};

#define eFONT	TYPE_FONT
enum class TYPE_FONT
{
	COMIC24,

	SIZE
};

#define eSHAPE	COLL_SHAPE
enum class COLL_SHAPE
{
	CIRCLE,
	RECT,
	POINT,

	END
};

#define eEvent	TYPE_EVENT
enum class TYPE_EVENT
{
	CREATEOBJ,
	DELETEOBJ,
	SCENECHANGE,
	CHANGE_AI_STATE,

	END
};

#define eDIR		COLL_DIR
enum class COLL_DIR
{
	NONE,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,

	END
};



// # Util
#include "struct.h"
#include "SingleTon.h"
#include "func.h"
#include "Logger.h"

// # Core, Manager, Class
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CPathManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"

#include "CObject.h"
// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CCollider.h"
#include "CAnimator.h"

#define DT							CTimeManager::getInst()->getDT()
#define fDT							CTimeManager::getInst()->getfDT()

#define	KEY_HOLD(key)				CKeyManager::getInst()->isKeyHold(key)
#define KEY_ON(key)					CKeyManager::getInst()->isKeyOn(key)
#define KEY_OFF(key)				CKeyManager::getInst()->isKeyOff(key)
#define KEY_NONE(key)				CKeyManager::getInst()->isKeyNone(key)
#define mousePos()					CKeyManager::getInst()->getMousePos()

#define createObj(pObj, eGroup)		CEventManager::getInst()->eventCreateObject(pObj, eGroup)
#define deleteObj(pObj)				CEventManager::getInst()->eventDeleteObject(pObj)
#define changeScn(eScn)				CEventManager::getInst()->eventChangeScene(eScn)

#define checkGrp(eObj1, eObj2)		CCollisionManager::getInst()->checkGroup(eObj1, eObj2)
#define unCheckGrp(eObj1, eObj2)	CCollisionManager::getInst()->unCheckGroup(eObj1, eObj2)
#define resetGrp()					CCollisionManager::getInst()->resetGroup()

#define createAnim					getAnimator()->createAnimation
#define PLAY(name)					getAnimator()->play(name)

#define camSetFocus(fp)				CCameraManager::getInst()->setFocusOn(fp)
#define camSetFocusNow(fp)			CCameraManager::getInst()->setFocusNow(fp)
#define camSetTrace(pObj)			CCameraManager::getInst()->setTraceObj(pObj)
#define camFadeOut(fTime)			CCameraManager::getInst()->fadeOut(fTime)
#define camFadeIn(fTime)			CCameraManager::getInst()->fadeIn(fTime)
#define rendPos(pos)				CCameraManager::getInst()->getRenderPos(pos)
#define realPos(pos)				CCameraManager::getInst()->getRealPos(pos)

#define loadTex(eName, wsPath)		CResourceManager::getInst()->loadTextrue(eName, wsPath)
#define findTex(eName)				CResourceManager::getInst()->findTexture(eName)

