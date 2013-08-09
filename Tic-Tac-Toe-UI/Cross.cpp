#include "stdafx.h"
#include "Cross.h"


Cross::Cross(void)
{
}


Cross::~Cross(void)
{
}

void Cross::paint(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 20, RGB(255,0,0)); //Создаётся объект
    SelectObject(hdc, hPen); //Объект делается текущим
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, center.x + width / 2 , center.y + height / 2);
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, center.x - width / 2 , center.y - height / 2);
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, center.x + width / 2 , center.y - height / 2);
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, center.x - width / 2 , center.y + height / 2);
}