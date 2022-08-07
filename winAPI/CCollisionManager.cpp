#include "framework.h"
#include "CCollisionManager.h"
#include "CScene.h"
#include "CPlayer.h"
#include "func.h"

CCollisionManager::CCollisionManager()
{
	m_arrCollChk[0] = 0;
}

CCollisionManager::~CCollisionManager()
{

}

// 충돌하는 OBJ그룹의 오브젝트들 모두를 비교해야 하기 때문에 오브젝트 배열 받아와야 한다.
// 현재 씬의 오브젝트들만 있으면 되고 현재 씬은 씬 매니저가 알고 있다.
void CCollisionManager::collisionGroupUpdate(eOBJ obj1, eOBJ obj2)
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	const vector<CObject*> vec1 = pCurScene->getGroupObject(obj1);
	const vector<CObject*> vec2 = pCurScene->getGroupObject(obj2);

	for (int i = 0; i < vec1.size(); i++)
	{
		if (nullptr == vec1[i]->getCollider())	continue;			// 충돌체 없는 경우

		for (int j = 0; j < vec2.size(); j++)
		{
			if (nullptr == vec2[j]->getCollider()) continue;		// 충돌체 없는 경우

			if (vec1[i] == vec2[j]) continue;						// vec[]가 CObject*니까 주소가 같은 경우(같은 객체인 경우) 예외처리

			// ID로 키값
			COLLIDER_ID id;
			id.left_id = vec1[i]->getCollider()->getID();
			id.right_id = vec2[j]->getCollider()->getID();

			map<ULONGLONG, bool>::iterator iter = m_mapIsColl.find(id.ID);	// 해당 아이디로 맵 자료형에서 찾음

			if (m_mapIsColl.end() == iter)							// 못 찾았으면 만들어주고 찾기
			{	// map.insert(make_pair(ULONGLONG, bool);
				m_mapIsColl.insert(make_pair(id.ID, false));		// 기본은 false;
				iter = m_mapIsColl.find(id.ID);
			}	// iter->second에 이전 프레임 충돌 상태값 가지고 있음



			if (isCollision(vec1[i]->getCollider(), vec1[i]->getCollider()->getShape(),
				vec2[j]->getCollider(), vec2[j]->getCollider()->getShape()))
			{	// 현재 충돌 O
				if (iter->second)
				{	// 이전 충돌 O // 각 충돌체에게 충돌상태에 따라 다르게 알려줄 필요성 (collider에 함수 추가)
					if (vec1[i]->isDead() || vec2[j]->isDead())
					{	// 유예 O : 충돌 해제
						vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
						iter->second = false;
					}
					else
					{	// 유예 X : 충돌 진행 중
						vec1[i]->getCollider()->collisionKeep(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionKeep(vec1[i]->getCollider());
					}

				}
				else
				{	// 이전 충돌 X
					if (!vec1[i]->isDead() && !vec2[j]->isDead())
					{	// 유예 X : 충돌 진입
						vec1[i]->getCollider()->collisionEnter(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionEnter(vec1[i]->getCollider());
						iter->second = true;
					}
					// 유예 O : 충돌 진입 안 함 (else는 아무 것도 할 필요없음)
				}
			}
			else
			{	// 현재 충돌 X
				if (iter->second)
				{	// 이전 충돌 O : 충돌 종료 (유예든 아니든 탈출하면 됨)
					vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
					vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
					iter->second = false;
				}
				// else 는 충돌한 적 없고 충돌하고 있지 않은 상태니까 아무것도 할 필요 없음
			}
		}
	}
}


bool CCollisionManager::isCollision(CCollider* pColl1, eSHAPE shape1, CCollider* pColl2, eSHAPE shape2)
{
	fPoint pos1 = pColl1->getPos();
	fPoint size1 = pColl1->getSize();
	fPoint pos2 = pColl2->getPos();
	fPoint size2 = pColl2->getSize();

	switch (shape1)
	{
	case eSHAPE::CIRCLE:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			return ISCOLLCC(pos1, (int)(size1.x * 0.5f), pos2, (int)(size2.x * 0.5f));
		}
		case eSHAPE::RECT:
		{
			RECT rt = { (int)(pos2.x - size2.x * 0.5f), (int)(pos2.y - size2.y * 0.5f),
						(int)(pos2.x + size2.x * 0.5f), (int)(pos2.y + size2.y * 0.5f) };
			return ISCOLLCR(pos1, (int)(size1.x * 0.5f), rt);
		}
		case eSHAPE::POINT:
		{
			return ISCOLLPC(pos2, pos1, (int)(size1.x * 0.5f));
		}
		}
		break;
		//
	case eSHAPE::RECT:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			RECT rt = { (int)(pos1.x - size1.x * 0.5f), (int)(pos1.y - size1.y * 0.5f),
						(int)(pos1.x + size1.x * 0.5f), (int)(pos1.y + size1.y * 0.5f) };
			return ISCOLLCR(pos2, (int)(size2.x * 0.5f), rt);
		}
		break;
		case eSHAPE::RECT:
		{	// obliq로 구분하지 말고 rect인데 getRad()가 둘다 0인 경우 일반 충돌함수, 아닌 경우 obb충돌함수 호출하는 식으로
			float rad1 = pColl1->getRad();
			float rad2 = pColl2->getRad();
			fPoint ofs1 = pColl1->getOffset();
			fPoint ofs2 = pColl2->getOffset();

			if (0.f == rad1 && 0.f == rad2)
				return ISCOLLRR(pos1, size1, pos2, size2);
			//else
			//{	// 좌상, 우상, 좌하 좌표(원점기준)
			//	fPoint fpArr1[3] = {
			//		fPoint(size1.x / -2.f,	size1.y / -2.f),
			//		fPoint(size1.x / 2.f,	size1.y / -2.f),
			//		fPoint(size1.x / -2.f,	size1.y / 2.f)
			//	};
			//	fPoint fpArr2[3] = {
			//		fPoint(size2.x / -2.f,	size2.y / -2.f),
			//		fPoint(size2.x / 2.f,	size2.y / -2.f),
			//		fPoint(size2.x / -2.f,	size2.y / 2.f)
			//	};

			//	if (0.f != rad1)
			//	{	// obj1 회전
			//		for (int i = 0; i < 3; i++)
			//		{	// 좌표에 회전행렬로 회전적용
			//			fpArr1[i].x = (float)(fpArr1[i].x * cos(rad1) - fpArr1[i].y * sin(rad1));
			//			fpArr1[i].y = (float)(fpArr1[i].x * sin(rad1) + fpArr1[i].y * cos(rad1));
			//		}
			//	}
			//	if (0.f != rad2)
			//	{	// obj2 회전
			//		for (int i = 0; i < 3; i++)
			//		{	// 좌표에 회전행렬로 회전적용
			//			fpArr2[i].x = (float)(fpArr2[i].x * cos(rad2) - fpArr2[i].y * sin(rad2));
			//			fpArr2[i].y = (float)(fpArr2[i].x * sin(rad2) + fpArr2[i].y * cos(rad2));
			//		}
			//	}

			//	for (int i = 0; i < 3; i++)
			//	{	// 원점에서 원래위치로
			//		fpArr1[i] += pos1 + ofs1;
			//	}
			//	for (int i = 0; i < 3; i++)
			//	{
			//		fpArr2[i] += pos2 + ofs2;
			//	}

			//	return isOBB(fpArr1, pos1, size1, rad1, fpArr2, pos2, size2, rad2);
			//}
			else
			{
				SHAPE shape1 = {
					pos1.y - size1.y * 0.5f,
					pos1.x - size1.x * 0.5f,
					size1.y,
					size1.x,
					rad1 * 180 / PI
				};

				SHAPE shape2 = {
					pos2.y - size2.y * 0.5f,
					pos2.x - size2.x * 0.5f,
					size2.y,
					size2.x,
					rad2 * 180 / PI
				};

				return OBB(shape1, shape2);
			}

		}
		case eSHAPE::POINT:
		{
			RECT rt = { (int)(pos1.x - size1.x * 0.5f), (int)(pos1.y - size1.y * 0.5f),
						(int)(pos1.x + size1.x * 0.5f), (int)(pos1.y + size1.y * 0.5f) };
			return ISCOLLPR(pos2, rt);
		}
		}
		//
	case eSHAPE::POINT:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			return ISCOLLPC(pos1, pos2, (int)(size2.x * 0.5f));
		}
		case eSHAPE::RECT:
		{
			RECT rt = { (int)(pos2.x - size2.x * 0.5f), (int)(pos2.y - size2.y * 0.5f),
						(int)(pos2.x + size2.x * 0.5f), (int)(pos2.y + size2.y * 0.5f) };
			return ISCOLLPR(pos1, rt);
		}
		case eSHAPE::POINT:
		{
			return (pos1 == pos2);
		}
		}

	}
	return false;
}

void CCollisionManager::init()
{
}

// 충돌 여부 체크된 그룹만 확인하도록 분류
void CCollisionManager::update()
{
	for (int i = 0; i < (UINT)eOBJ::SIZE; i++)
	{	// 절반은 검사 안 해도 되니까 j = i부터 시작
		for (int j = i; j < (UINT)eOBJ::SIZE; j++)
		{	// 충돌 여부 비트로 저장한 UINT m_arrCollChk[]가 1이면 판정 
			if (m_arrCollChk[i] & (0x1 << j))
			{	
				collisionGroupUpdate((eOBJ)i, (eOBJ)j);
			}
		}
	}
}

void CCollisionManager::checkGroup(eOBJ obj1, eOBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	m_arrCollChk[(UINT)groupLow] |= (0x1 << group);
}

void CCollisionManager::unCheckGroup(eOBJ obj1, eOBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	m_arrCollChk[(UINT)groupLow] &= ~(0x1 << group);
}

void CCollisionManager::resetGroup()
{	// (void* Dst, int Val,  size_t Size)
	memset(m_arrCollChk, 0, sizeof(UINT) * (UINT)eOBJ::SIZE);		// memset 속도가 매우 빠름
}
