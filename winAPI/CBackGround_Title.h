#pragma once
#include "CObject.h"

class CTexture;

class CBackGround_Title : public CObject
{
    CTexture* m_pTex;

public:
    CBackGround_Title();
    virtual ~CBackGround_Title();

    virtual CBackGround_Title* clone();

    void update();
    void render(HDC hDC);
};

