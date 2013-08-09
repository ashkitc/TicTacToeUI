#include "stdafx.h"
#include "PlayBoardLine.h"
#include <iostream>
#include <cstddef>

PlayBoardLine::PlayBoardLine() //allocate mamory and init pointers with null
{
	cellsPtrs = new PlayBoardCell*[3];
	for (int i = 0; i < 3; ++i)
	{
		cellsPtrs[i] = NULL;
	}
}
 
PlayBoardLine::~PlayBoardLine() // dealocate memory
{
	delete cellsPtrs;
}

void PlayBoardLine::initWithLine(PlayBoardCell *linePtr) // here you pass a begin of some row
{
	for (int i = 0; i < 3; ++i)
	{
		cellsPtrs[i] = &linePtr[i];
	}
}

int PlayBoardLine::countOfSigns(char sign) 
{
	int count = 0;
	for (int i = 0; i < 3; ++i)
	{
		if(cellsPtrs[i]->getValue() == sign)
		{
			++count;
		}
	}
	return count;
}
bool PlayBoardLine::hasCellWithValue(char sign)
{
	for ( int i = 0; i < 3; ++ i)
	{
		if( cellsPtrs[i]->getValue() == sign)
		{
			return true;
		}
	}
	return false;
}

PlayBoardCell* PlayBoardLine::emptyCell()
{
	for ( int i = 0; i < 3; ++ i)
	{
		if( cellsPtrs[i]->isEmpty())
		{
			return cellsPtrs[i];
		}
	}
	return NULL;
}
void PlayBoardLine::setRatingForSign(char sign)
{
	if(countOfSigns(' ') == 1) // look if line can be critical
	{ 
			if(countOfSigns(sign) == 2) // check if cpu can win
			{
				if(emptyCell() != NULL &&  emptyCell()->getRating() < CAN_WIN_RATING)
				{
					emptyCell()->setRating(CAN_WIN_RATING);
				}
			}
		else 
		{
			if(countOfSigns(sign) == 0) // check if cpu can lose
			{
				if(emptyCell() != NULL && emptyCell()->getRating() < CAN_LOSE_RATING)
				{
					emptyCell()->setRating(CAN_LOSE_RATING);
				}
			}
		}
	}
}

void PlayBoardLine::addCellPtr(PlayBoardCell *cellPtr) //add cell pointer to line
{
	for(int i = 0; i < 3; ++i)
	{
		if (cellsPtrs[i] == NULL)
		{
			cellsPtrs[i] = cellPtr;
			break;
		}
	}
}

bool PlayBoardLine::hasWinner() //check if somebody wins
{
	for (int i = 0; i < 2; ++i)
	{ 
		if( cellsPtrs[i]->isEmpty() )
		{
			return false;
		} else 
		{
			if ( cellsPtrs[i]->getValue() != cellsPtrs[i+1]->getValue() )
			{
				return false;
			}
		}
	}
	return true;
}

void PlayBoardLine::setCellStatuses(winType newStatus)
{
	for (int i = 0; i < 3; ++i)
	{
		cellsPtrs[i]->setStatus(newStatus);
	}
}