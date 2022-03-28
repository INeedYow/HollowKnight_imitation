#pragma once

class CCollider;

static UINT g_IDNumbering = 0;

eDIR collisionRectToRect(CCollider* coll1, CCollider* coll2);
eDIR collisionRectToRectWide(CCollider* coll1, CCollider* coll2);
bool isTopCollOnly(CCollider* coll1, CCollider* coll2);
bool isBottomCollOnly(CCollider* coll1, CCollider* coll2);
bool isLeftColl(CCollider* coll1, CCollider* coll2);

bool isCollisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2);
bool isCollisionPointToRect(const fPoint& point, const RECT& rt);
bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr);
bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt);
bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2);

//bool isCollisionObliqueRect(const fPoint& cp1, int cr1, float theta1, const fPoint& cp2, int cr2, float theta2);

// createMemTex ID 생성용 (중복 이름 에러 방지)
wstring addStrIDNumber(const wstring& str);
