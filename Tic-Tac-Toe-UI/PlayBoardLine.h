#pragma once
#include "PlayBoardCell.h"
class PlayBoardLine
{
	PlayBoardCell** cellsPtrs; //array of pointers to cell 

public:
	PlayBoardLine();
	~PlayBoardLine();
	void initWithLine(PlayBoardCell *linePtr); //takes a pointer of row begining
	void addCellPtr(PlayBoardCell *ptr); //adds new cell pointer to cellsPtrs array
	int countOfSigns(char sign); //calculates counts of sign ('x','o' or ' ') in this line 
	void setRatingForSign(char sign); //search critical cell (depending on sign) and sets rating for this cell
	bool hasCellWithValue(char sign); // look if line has cell where value equals sign
	bool hasWinner(); // looks if line has winner
	PlayBoardCell* emptyCell(); // returns first leine's empty cell
	void setCellStatuses(winType newStatus);
	
	
};

