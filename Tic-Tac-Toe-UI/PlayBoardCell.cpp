#include "stdafx.h"
#include "PlayBoardCell.h"


PlayBoardCell::PlayBoardCell(void)
{
	value = ' '; // By default cell inits with space (cell is empty);
	rating = 0;
	sign = NULL;
	cellStatus = winType::NONE;
}


void PlayBoardCell::reset()
{
	value = ' ';
	rating = 0;
	delete sign;
	sign = NULL;
	cellStatus = winType::NONE;
}
//Check if cell is empty
 bool PlayBoardCell::isEmpty()
{
	if (value != ' ')
	{
		return false;
	}
	return true;
}
 
//set value if cell is empty else returns false
 bool PlayBoardCell::setValue(char newValue)
 {
	 if( !isEmpty() )
	 {
		 return false;
	 }
	 value = newValue;
	 rating = DONT_CARE_RATING; //set rating for occupied cell
	 if(value == 'x' || value == 'X')
	 {
		 sign = new Cross();
		
	 } else 
	 {
		 sign = new Zero();
	 }
	  sign->setCenter(center);
		 sign->setHeight(0.7 * height);
		 sign->setWidth(0.7 * width);
	 return true;
 }

 void PlayBoardCell::paint(HDC hdc)
 {
	 if(value != ' ')
	 {
		 if(sign != NULL)
		 {
			 sign->paint(hdc);
		 }
	 }

	 //Select a brush
	HPEN hPen = CreatePen(PS_SOLID, 10, RGB(0,0,0)); 
    SelectObject(hdc, hPen);
	 switch(cellStatus) //Draw line according to game result
	 {
	 case winType::HORIZONTAL:
		 MoveToEx(hdc,center.x - width / 2, center.y,NULL);
		 LineTo(hdc,center.x +width / 2, center.y);
		 break;
	 case winType::VERTICAL:
		 MoveToEx( hdc,center.x, center.y - height / 2,NULL );
		 LineTo( hdc,center.x, center.y + height / 2 );
		 break;
	 case winType::LEFTDIAGONAL:
		 MoveToEx( hdc,center.x- width / 2, center.y - height / 2,NULL );
		 LineTo( hdc,center.x + width / 2, center.y + height / 2);
		 break;
	 case winType::RIGHTDIAGONAL:
		 MoveToEx( hdc,center.x + width / 2, center.y - height / 2,NULL );
		 LineTo( hdc,center.x- width / 2, center.y + height / 2);
		 break;
	 }
 }

 bool PlayBoardCell::hasPoint(POINT point)
 {
	 if( point.x >= (center.x - width / 2) && point.x <= (center.x + width / 2)  
		 && point.y >= ( center.y - height / 2) && point.y <= ( center.y + height / 2))
	 {
		 return true;
	 }
	 return false;
 }

 bool PlayBoardCell::isCorner()
 {
	 if(rowNumber != 1 && columnNumber != 1)
	 {
		 return true;
	 }
	 return false;
 }