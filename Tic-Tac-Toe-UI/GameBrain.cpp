#include "stdafx.h"
#include "GameBrain.h"
#include <iostream>
using namespace std;
GameBrain::GameBrain(void)
{
	usersSign = ' ';
}


GameBrain::~GameBrain(void)
{
}

void GameBrain::startPlaying()
{
	bool choseDone = false;
	cout << "Welcome to the Tic - Tac - Toe" << endl;
	choseSign();
	play();
}

void GameBrain::play()
{
	volatile bool endOfGame = false;
	while(!endOfGame) //checks if game isn't over
	{
		
		if(usersSign == 'X' || usersSign == 'x') // checks who make choise first
		{
			userChoice();
			cpuChoice();
		} else 
		{
			cpuChoice();
			userChoice();
		}
		endOfGame = playBoard.isEndOfGame();
	}
		if(playBoard.getWinner() == usersSign)
	{
		cout << "Congratulations you WON!!!!" << endl;
	} else 
		if (playBoard.getWinner() == ' ')
		{
			cout << "Not bad, frendship won" << endl;
		}
		else 
		{
			cout << "Sorry, but this time you LOSER"  << endl;
		}
}

bool GameBrain::isCorrectCoordinates(int row, int column)
{
	if(row >= 3 || row < 0 || column >= 3 || column < 0)
	{ 
		return false;
	}
	return true;
}
void GameBrain::userChoice()
{
	if(!playBoard.isEndOfGame()) 
	{
		int row = -1, column = -1;
		bool choiceDone = false;
		while (!choiceDone) ///ask user to make choice until he'll enter correct coordinates
		{
			while ( !isCorrectCoordinates(row,column) )
			{
				cout << "Enter a coordinates of cell for choice" << endl;
				cin >> row >> column;
			}
		choiceDone = playBoard.setValueOfCellWithCoordinates(usersSign, row, column);
		row = -1;
		column = -1;
		}
		cout << "Game field: " << endl;
	    playBoard.displayToConsole();
	}
}



void GameBrain::cpuChoice()
{
	if(!playBoard.isEndOfGame())
	{
		char cpuSign;
		if(usersSign == 'X' || usersSign == 'x')
		{
			cpuSign = 'O';
		} else 
		{
			cpuSign = 'X';
		}
		cout << "After CPU choice" << endl;
		playBoard.maxRaitedCell(cpuSign).setValue(cpuSign);
		playBoard.displayToConsole();
	}
}

void GameBrain::choseSign()
{
	while ( !isCorrectSign (usersSign) )
	{
	   cout << "For begin playing chose your sign (type X or O)" << endl;
	   cin >> usersSign;
	}
}

bool GameBrain::isCorrectSign(char sign)
{
	if (sign == 'X' || sign == 'x' || sign == 'O' || sign == 'o')
	{
		return true;
	}
	return false;
}