#pragma once
#include "Cross.h"
#include "Zero.h"
#include <Windows.h>
// Constants for cell's rating
const int CAN_WIN_RATING = 6;   //For cell where cpu can win in one step
const int CAN_LOSE_RATING = 5;  //For cell where cpu can lose in one step
const int OPPOSITE_CORNER_RATING = 4;
const int CENTER_RATING = 3;    //For center
const int CORNER_RATING = 2;    //For corners
const int EMPTY_CELL_RATING = 1;//For empty cell
const int DONT_CARE_RATING = 0; //For occupied cell
enum winType { NONE , HORIZONTAL , VERTICAL , LEFTDIAGONAL , RIGHTDIAGONAL };
class PlayBoardCell
{
public:
	PlayBoardCell(void);
    bool isEmpty(); 
	bool isCorner();
	//Accessor methods
	char getValue() { return value; };
	int getRating() { return rating; };
	void setRating(int newrating) { rating = newrating; };
	bool setValue(char newValue);
	void setCoordinates(int row, int column) { rowNumber = row; columnNumber = column; }
	int row(){ return rowNumber;}
	int column() {return columnNumber;}
	void setHeight( int newHeight ) { height = newHeight; }
	void setWidth ( int newWidth ) { width = newWidth; }
	void setCenter(POINT newCenter){ center.x = newCenter.x; center.y = newCenter.y; }
	winType getStatus() { return cellStatus; }
	void setStatus(winType newStatus) { cellStatus = newStatus; }

	void paint(HDC hdc); //Method for paint (paints sign according to cells value)
	bool hasPoint(POINT point); //Check if point passed as argument allocates inside the cell
	void reset(); //Resets cells value and raiting
private:
	Sign *sign;  //every cell has sign (cross or zero)
	char value;  //Can be x or 0
	int rating;  // cells raiting (determines if cell is critical)
	int rowNumber;
	int columnNumber;
	int height;
	int width;
	winType cellStatus; //win status (sets when cell belongs to line where somebody wins)
	POINT center;
};

