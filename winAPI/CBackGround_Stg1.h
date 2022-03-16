#pragma once
#include "CObject.h"

class CTexture;

class CBackGround_Stg1 : public CObject
{
    CTexture* m_pTexFront;
    CTexture* m_pTexBack;

public:
    CBackGround_Stg1();
    virtual ~CBackGround_Stg1();

    virtual CBackGround_Stg1* clone();

    virtual void update();
    virtual void render(HDC hDC);

};

