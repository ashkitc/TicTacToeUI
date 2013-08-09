#include "stdafx.h"
#include "PlayBoard.h"
#include <iostream>
#include <algorithm>
#include "PlayBoardLine.h"
PlayBoard::PlayBoard(void)
{
	winner = ' '; //we haven't winner when init playboard
	int current = 0;
	for (int row = 0; row < 3; ++ row)
	{
		for (int column = 0; column < 3; ++ column)
		{
			gamefield[current].setCoordinates(row,column); //Set column's coordinates
			gamefield[current].setRating(EMPTY_CELL_RATING); //End raiting for empty cells
			++current;
		}
	}
	//when game begins center cell and corner cells are most important
	centerCell().setRating(CENTER_RATING); 
	setCorrnersRating(); 
}

void PlayBoard::reset()
{
	winner = ' ';
	for (int i = 0; i < 9; ++i)
	{
		gamefield[i].reset();
	}
	int current = 0;
	for (int row = 0; row < 3; ++ row)
	{
		for (int column = 0; column < 3; ++ column)
		{
			gamefield[current].setCoordinates(row,column); //Set column's coordinates
			gamefield[current].setRating(EMPTY_CELL_RATING); //End raiting for empty cells
			++current;
		}
	}
	//when game begins center cell and corner cells are most important
	centerCell().setRating(CENTER_RATING); 
	setCorrnersRating(); 
}
PlayBoard::PlayBoard(int boardWidth, int boardHeight, POINT topLeft)
{
	
	width = boardWidth;
	height = boardHeight;
	topLeftPoint.x = topLeft.x;
	topLeftPoint.y = topLeft.y;
	winner = ' '; //we haven't winner when init playboard
	int current = 0;
	POINT cellCenter;
	cellCenter.y = 0;
	for (int row = 0; row < 3; ++ row)
	{
		cellCenter.x = 0;
		cellCenter.y += (row * (height / 3)) + height / 6;
		for (int column = 0; column < 3; ++ column)
		{
			cellCenter.x = (column * (width / 3)) + width / 6;	
			gamefield[current].setCoordinates(row,column); //Set column's coordinates
			gamefield[current].setRating(EMPTY_CELL_RATING); //End raiting for empty cells
			gamefield[current].setHeight(height / 3);
			gamefield[current].setWidth(width / 3);
			gamefield[current].setCenter(cellCenter);
			++current;
		}
			cellCenter.y = 0;
	}
	//when game begins center cell and corner cells are most important
	centerCell().setRating(CENTER_RATING); 
	setCorrnersRating(); 
}
void PlayBoard::setWiner(char value) //For checking who wins
{
	if(value == 'x' || value == 'X' ||
	   value == 'o' || value == 'O')
	{
		winner = value;
	}
}

PlayBoardCell& PlayBoard::cellWithCoordinates(int row, int column) 
{
	PlayBoardCell *chosen = NULL; //Temporary pointer to the cell
	for(int i = 0; i <9; ++i) 
	{
		if(gamefield[i].row() == row && gamefield[i].column() == column)
		{
			chosen = &gamefield[i]; 
			break;
		}
	}
	return *chosen;
}

void PlayBoard::displayToConsole()
{
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			std::cout << cellWithCoordinates(row,column).getValue();
			if(column < 2)
			{
				std::cout<< '|'; 
			}
		}
		std::cout << std::endl;
		if(row < 2)
		{
			std::cout <<"------";
			std::cout << std::endl;
		}
	}
}

bool PlayBoard::isEmpty()
{
	for (int row = 0; row < 3; ++row) // checking if all cells are empty
	{
		for (int column = 0; column < 3; ++column)
		{
			if(!cellWithCoordinates(row,column).isEmpty())
			{
				return false;
			}
		}
	}
	return true;
}

bool PlayBoard::allCellsAreOccupied() 
{
	for (int row = 0; row < 3; ++ row) // checking if all cells are occupied
	{
		for (int column = 0; column < 3; ++column)
		{
			if( cellWithCoordinates(row,column).isEmpty() ) 
			{
				return false;
			}
		}
	}
	return true;
}

bool PlayBoard::isEndOfGame() // cheking if the game ends
{
	if(allCellsAreOccupied()) //cheking if all cells are occupied
	{
		return true;
	}  else 
	{
		checkWinner(); //checking if somebody wins
		if (winner != ' ')
		{
			return true;
		}
	}
	return false;
}

void PlayBoard::checkWinner()
{

	//Checking rows
	for (int i = 0; i < 9; i +=3)
	{
		PlayBoardLine line; //Playboard lines is a support class who can check winner in one line
	    line.initWithLine( (gamefield + i) ); //Init Playboard lines with current row
		if(line.hasWinner())
		{
			setWiner(gamefield[i].getValue());
			line.setCellStatuses(winType::HORIZONTAL);
		}
	}
	//Checking columns
    for (int i = 0; i < 3; ++i)
	{
		PlayBoardLine line;
		for (int j = 0; j < 3; ++j) 
		{
			line.addCellPtr( &cellWithCoordinates(j,i) ); //add to the line the next cell from current column
		}
		if(line.hasWinner()) 
		{
			setWiner(gamefield[i].getValue());
			line.setCellStatuses(winType::VERTICAL);
		}
	}


	PlayBoardLine leftDiagonal;
	PlayBoardLine rightDiagonal;
	for(int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(i == j)
			{
				leftDiagonal.addCellPtr( &cellWithCoordinates(i,j) );
			}
		}
	}

	if(leftDiagonal.hasWinner())
	{
		setWiner(cellWithCoordinates(1,1).getValue());
		leftDiagonal.setCellStatuses(winType::LEFTDIAGONAL);
	}

	for(int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(i + j == 2)
			{
				rightDiagonal.addCellPtr( &cellWithCoordinates(i,j) );
			}
		}
	}
	if(rightDiagonal.hasWinner())
	{
		setWiner(cellWithCoordinates(1,1).getValue());
		rightDiagonal.setCellStatuses(winType::RIGHTDIAGONAL);
	}

}

bool PlayBoard::setValueOfCellWithCoordinates( char newValue, int row, int column)
{
	if( cellWithCoordinates(row,column).isEmpty() )
	{
		cellWithCoordinates(row,column).setValue(newValue); 
		return true;
	}
	return false;
}

void PlayBoard::setCorrnersRating() // sets raiting for all corners
{
	cellWithCoordinates(0,0).setRating(CORNER_RATING);
	cellWithCoordinates(2,2).setRating(CORNER_RATING);
	cellWithCoordinates(0,2).setRating(CORNER_RATING);
	cellWithCoordinates(2,0).setRating(CORNER_RATING);
}

void PlayBoard::resetRating(char sign)
{
	for (int i = 0; i < 9; ++i) //reset raiting on occupied cells
	{
		if(!gamefield[i].isEmpty())
		{
			gamefield[i].setRating(DONT_CARE_RATING);
			if(gamefield[i].isCorner() && gamefield[i].getValue() != sign )
			{
				if(oppositeCorner(gamefield[i]).isEmpty() )
				{	
					if(gamefield[i].getValue() != centerCell().getValue())
					{
						oppositeCorner(gamefield[i]).setRating(OPPOSITE_CORNER_RATING);
					}
				}
			}
		}
	}
	resetRatingOnRows(sign); //fing critical rows (rows where cpu can win or lose by one step)
	resetRatingOnColumns(sign);//fing critical columns 
	resetRaitingOnDiagonals(sign);
}

void PlayBoard::resetRatingOnRows(char sign)
{
	/*
	Looking for row where sign can win or lose and set priority 
			of this row's empty cells 
	*/
	for (int i = 0; i < 9; i +=3)
	{
		PlayBoardLine line;
	    line.initWithLine( (gamefield + i) );
		line.setRatingForSign(sign);
	}
}

void PlayBoard::resetRatingOnColumns(char sign)
{

	/*
	Looking for column where sign can win or lose and set priority 
			of this colums's empty cells 
	*/
	for (int i = 0; i < 3; ++i)
	{
		PlayBoardLine line;
		for (int j = 0; j < 3; ++j)
		{
			line.addCellPtr(&cellWithCoordinates(j,i) );
		}
		line.setRatingForSign(sign);
	}
}

void PlayBoard::resetRaitingOnDiagonals(char sign)
{
	PlayBoardLine leftDiagonal;
	PlayBoardLine rightDiagonal;
	for(int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(i == j)
			{
				leftDiagonal.addCellPtr( &cellWithCoordinates(i,j) );
			}
		}
	}
    leftDiagonal.setRatingForSign(sign);

	for(int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(i + j == 2)
			{
				rightDiagonal.addCellPtr( &cellWithCoordinates(i,j) );
			}
		}
	}
	rightDiagonal.setRatingForSign(sign);
}

PlayBoardCell& PlayBoard::maxRaitedCell(char sign)
{
	resetRating(sign); //recalculate rating for all cells
	PlayBoardCell *maxRatedCell = new PlayBoardCell();
	for(int i = 0; i < 9; ++i)
	{
		if(gamefield[i].getRating() > maxRatedCell->getRating())
		{
			maxRatedCell = &gamefield[i]; //search cell with max raiting
		}
	}
	return *maxRatedCell;
}

void PlayBoard::paint(HDC hdc)
{
	RECT r; 
	r.left=topLeftPoint.x; 
	r.top=topLeftPoint.y; 
	r.right=topLeftPoint.x+width; 
	r.bottom=topLeftPoint.y+height;
    FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(255,239,219)));

	 HPEN hPen = CreatePen(PS_SOLID, 1, RGB(126,192,238)); //Создаётся объект
    SelectObject(hdc, hPen); //Объект делается текущим
	for (int i = topLeftPoint.x; i < topLeftPoint.x + width; i += 20)
	{
		MoveToEx(hdc,i,0,NULL);
		LineTo(hdc,i,height);
	}

	for (int i = topLeftPoint.y; i < topLeftPoint.y + height; i += 20)
	{
		MoveToEx(hdc,0,i,NULL);
		LineTo(hdc,width,i);
	}

	 hPen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); //Создаётся объект
    SelectObject(hdc, hPen); //Объект делается текущим
	for(int i = topLeftPoint.x + width / 3; i <  topLeftPoint.x + width; i +=width / 3)
	{
		MoveToEx(hdc,i,0,NULL);
		LineTo(hdc,i,height);
	}

	for (int i = topLeftPoint.y + height / 3; i < topLeftPoint.y + height; i += height / 3)
	{
		MoveToEx(hdc,0,i,NULL);
		LineTo(hdc,width,i);
	}

	for( int i = 0; i < 9; ++i)
	{
		gamefield[i].paint(hdc);
	}
	
}

bool PlayBoard::handlePress(int x, int y)
{
	for(int i = 0; i < 9; ++i)
	{
		POINT o;
		o.x = x;
		o.y = y;
		if(gamefield[i].isEmpty() && gamefield[i].hasPoint(o))
		{
			return (gamefield[i].setValue('X'));
		}
	}
	return false;
}


PlayBoardCell& PlayBoard::oppositeCorner(PlayBoardCell& cell)
{

	if(cell.isCorner())
	{
		if(cell.row() == cell.column())
		{
			if(cell.row() == 2)
			{
				return cellWithCoordinates(cell.row() - 2, cell.column() - 2);
			}
			else 
			{
				return cellWithCoordinates(cell.row() + 2, cell.column() + 2);
			}
		}
		else 
		{
			return cellWithCoordinates(cell.column(),cell.row());
		}
	}
	
}