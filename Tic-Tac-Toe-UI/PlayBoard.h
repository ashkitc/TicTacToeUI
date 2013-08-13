#pragma once
#include "PlayBoardCell.h"
#include <Windows.h>
class PlayBoard
{
public:
	PlayBoard(void);
    PlayBoard(int boardWidth, int boardHeight,POINT topLeft);
	bool isEndOfGame(); //Check if somebody wins or if all cells are occupied
	bool setValueOfCellWithCoordinates(char newValue, int row, int column); 
	PlayBoardCell& maxRaitedCell(char sign); //Search the best cell for next cpu step
	char getWinner() { return winner; }
	void setWidth(int newWidth) {width = newWidth;}
	void setHeight(int newHeight) {height = newHeight; }
	void setTopLeft(POINT newTopLeft){ topLeftPoint.x = newTopLeft.x; topLeftPoint.y = newTopLeft.y; }
	void paint(HDC hdc);
	bool handlePress(int x, int y);
	void checkWinner();//Check if somebody wins and sets winner
	bool allCellsAreOccupied(); //cheks if all cells are occupied
	void reset();
	
private:
	PlayBoardCell gamefield[9]; //Stores all cells on the playboard
	void setWiner(char value);
	void setCorrnersRating(); //Sets rating to all corners
	PlayBoardCell& oppositeCorner(PlayBoardCell &cell);
	PlayBoardCell& centerCell() {return cellWithCoordinates(1,1); } //returns center cell
	void resetRating(char sign); //recalculate rating for each cells
	void resetRatingOnRows(char sign); //recalculate rating for each cells (only on rows)
	void resetRatingOnColumns(char sign);// //recalculate rating for each cells (only on columns)
	void resetRaitingOnDiagonals(char sign);
	bool isEmpty(); //Check if all cells are empty
	PlayBoardCell& cellWithCoordinates(int row, int column); //returns cell with coordinates
	char winner; //stores who win (x or 0);
	int width;
	int height;
	POINT topLeftPoint;
};

