#include "framework.h"
#include "func.h"

class CCollider;

// == COLLRR
eDIR collisionRectToRect(CCollider* coll1, CCollider* coll2)
{	// 이미 충돌인 상태에서 적당히 검사(COLL exit() 상태에서 검사할 때 쓸 듯)
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	if (pos2.y - size2.y / 2 <= pos1.y && 
		pos1.y <= pos2.y + size2.y / 2)
	{
		if (pos1.x <= pos2.x - size2.x / 2) return eDIR::LEFT;
		if (pos1.x >= pos2.x + size2.x / 2) return eDIR::RIGHT;
	}
	else
	{
		if (pos1.y <= pos2.y - size2.y / 2) return eDIR::TOP;
		if (pos1.y >= pos2.y + size2.y / 2) return eDIR::BOTTOM;
	}
	return eDIR::NONE;
}

// == COLLRRW
eDIR collisionRectToRectWide(CCollider* coll1, CCollider* coll2)
{ // 타일, 땅과 좌우 검사에 대쉬 속도 감안해서 좀 더 여유롭게 판정(COLL enter(), keep() 상태에서 검사할 때 쓸 듯)
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size1 = coll1->getOwner()->getSize();
	fPoint size2 = coll2->getOwner()->getSize();

	if (pos2.y - size2.y / 2.f - size1.y / 2.f < pos1.y && 
		pos1.y < pos2.y + size2.y / 2.f + size1.y / 2.f)
	{
		if (pos1.x < pos2.x) return eDIR::LEFT;
		else return eDIR::RIGHT;
	}
	else
	{
		if (pos1.y <= pos2.y) return eDIR::TOP;
		else return eDIR::BOTTOM;
	}
	//return eDIR::NONE;
}

// == ISTOPEXIT
// 마리오에서 했던 것처럼 leftSpd, rightSpd 나누면 쉽게 해결할 수 있을 듯
bool isTopColl(CCollider* coll1, CCollider* coll2)
{	// 땅과 exit() 상태에서 조금만 내려가도 left, right판정나면 x위치 고정돼서 
	// exit()에서 땅타일과 위아래 충돌 검사만 할 목적으로
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	return pos1.y <= pos2.y - size2.y / 2.f;
}

bool isLeftColl(CCollider* coll1, CCollider* coll2)
{
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();

	if (pos1.x < pos2.x)
		return true;
	return false;
}

bool isCollisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2)
{	// == ISCOLLRR					// 사각형1 좌표, 사이즈				// 사각형2 좌표, 사이즈
	return ((abs(pos1.x - pos2.x) < (size1.x + size2.x) / 2.f) &&
		(abs(pos1.y - pos2.y) < (size1.y + size2.y) / 2.f));
}

bool isCollisionPointToRect(const fPoint& point, const RECT& rt)
{	// == ISCOLLPR						// 좌표		// 사각형
	return ((rt.left <= point.x && point.x <= rt.right) &&
		(rt.top <= point.y && point.y <= rt.bottom));
}	// 좌표범위가 사각형에 포함되는지 확인

bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)
{	// == ISCOLLPC						// 좌표 //	원 중심좌표,	 원 반지름 길이
	// x, y 길이
	float x = point.x - cp.x;
	float y = point.y - cp.y;

	// 좌표와 원 중심까지 거리
	float distance = (float)sqrt((double)x * x + (double)y * y);

	// 거리가 반지름보다 작거나 같으면 충돌
	return (distance <= cr);
}

bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)
{	// == ISCOLLCR				// 원 중심좌표, 원 반지름 길이 // 사각형
	// 원의 반지름 만큼 확장시킨 사각형을 새로 만듦
	RECT rect = {
		(int)rt.left - cr,
		(int)rt.top - cr,
		(int)rt.right + cr,
		(int)rt.bottom + cr };

	// 확장한 사각형 안에 원의 중심이 있다면 충돌 (꼭지점 충돌은 제외)
	if ((rect.left <= cp.x && cp.x <= rect.right) && (rect.top <= cp.y && cp.y <= rect.bottom))
		return true;

	// 꼭지점 충돌 확인 (확장한 사각형의 각 꼭지점 좌표가 원 안에 있는지 확인)
	else
	{
		if (ISCOLLPC(fPoint((float)rect.left, (float)rect.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rect.right, (float)rect.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rect.right, (float)rect.bottom), cp, cr))		return true;
		if (ISCOLLPC(fPoint((float)rect.left, (float)rect.bottom), cp, cr))			return true;
	}
	return false;
}

bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)
{	// == ISCOLLCC					// 원1 중심좌표, 반지름		// 원2 중심좌표, 반지름
	// 원 중심끼리 거리 구해서 반지름의 합보다 작으면 충돌
	float x = cp1.x - cp2.x;
	float y = cp1.y - cp2.y;

	float distance = (float)sqrt((double)x * x + (double)y * y);

	return (distance <= cr1 + cr2);
}