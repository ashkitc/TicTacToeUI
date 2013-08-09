#pragma once
#include "PlayBoard.h"
class GameBrain
{
public:
	GameBrain(void);
	~GameBrain(void);
	void startPlaying(); // call for begin playing

private:
	PlayBoard playBoard;
	bool isCorrectCoordinates(int row, int column); //checks if user entered correct coordinates
	void play();  // runs queue of user's and cpu's chois until somebody wins
	void choseSign(); // ask a sign and chek it
	void userChoice(); // ask user to make choice
	void cpuChoice(); // cpu makes choice
	bool isCorrectSign(char sign); //checks if user entered correct sign
	char usersSign;
};

