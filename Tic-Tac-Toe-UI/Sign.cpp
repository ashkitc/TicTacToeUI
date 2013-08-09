#include "stdafx.h"
#include "Sign.h"


Sign::Sign(void)
{
	center.x = 0;
	center.y = 0;
	width = 0;
	height = 0;
}

Sign::Sign(POINT newCenter,int newWidth, int newHeight)
{
	center.x = newCenter.x;
	center.y = newCenter.y;
	width = newWidth;
	height = newHeight;
}

Sign::~Sign(void)
{
}