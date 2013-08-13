#include "stdafx.h"
#include "Zero.h"


Zero::Zero(void)
{
}


Zero::~Zero(void)
{
}

void Zero::paint(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 20, RGB(0,0,255)); //select a brush
    SelectObject(hdc, hPen); 
	Arc(hdc,center.x - width / 2,center.y - height / 2,center.x + width / 2,center.y + height / 2,center.x+width/2,center.y,center.x+width/2,center.y); //draw circle
}