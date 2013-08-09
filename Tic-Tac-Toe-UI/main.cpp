#include <iostream>
#include <conio.h>
#include "GameBrain.h"
using namespace std;
int main (int argc, char **argv)
{
	

    int userChoice = 1;
	while (true)
	{
		GameBrain game;
		cout << "1 - New game" << endl;
		cout << "0 - exit" << endl;
		cin >> userChoice;
		if(userChoice == 0)
		{
			break;
		}
		game.startPlaying();
	}
	cout << "Thank you for playing!!!" << endl;
	_getch();
	return 0;
}
