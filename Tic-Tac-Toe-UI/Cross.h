#pragma once
#include "Sign.h"
class Cross :
	public Sign
{
public:
	Cross(void);
	virtual ~Cross(void);
	void paint(HDC hdc);
};

