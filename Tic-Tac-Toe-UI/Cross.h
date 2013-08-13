#pragma once
#include "Sign.h" //Class of cross sign
class Cross :
	public Sign
{
public:
	Cross(void);
	virtual ~Cross(void);
	void paint(HDC hdc);
};

