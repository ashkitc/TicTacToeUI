#pragma once
#include <Windows.h>
class Sign
{
protected:
	int width;
	int height;
	POINT center;
public:
	Sign(void);
	Sign(POINT newCenter,int newWidth, int newHeight);
	virtual void paint(HDC hdc) = 0;
	virtual void setCenter(POINT newCenter) { center.x = newCenter.x;  center.y = newCenter.y; };
	virtual void setWidth(int newWidth) { width = newWidth; }
	virtual void setHeight(int newHeight) { height = newHeight; }
	virtual ~Sign(void);
};

