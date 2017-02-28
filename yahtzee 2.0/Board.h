#pragma once
class Board
{
public:
	// max amount of rolls and rounds
	const int MAX_ROLLS = 3;
	const int MAX_ROUNDS = 13;
	const int DICE = 5;
	// rolls and rounds left
	int rolls = 1;
	int rounds = 1;
	// Contains the rolled dice
	int dice[5]{1,1,2,2,2};
	// a workable copy of dice
	int dieCopy[5];
	// contains the dice to reroll
	int reRollDice[5];
	// contains the score board
	int score[14];
	int tempScore = 0;
	// contains the choices that are left too choose
	int choiceLeft[14];



public:
	// print the dice
	void printDice();
	// roll all the dice
	void makeARoll();
	// roll only the dice containd in reRollDice
	void makeARoll(int *reRollDice);
	// Print the board on the screen
	void printBoard();
	// Test the score condition
	bool testScoreCondition(int scoreChoice);		//maybe take a value?
	// print the choice menu
	void choiceMenu();
	// Take input, depending on intOrStr
	int input();
	// returns the number of same type
	int Board::noOfTypes(int type);
	// test if there are any of a kind. Make score and return true or false
	bool Board::checkHowMany(int kind);
	// test if 3 or 4 of a kind, returns if 3 or 4 or none
	int checkIfSame(int kind);
	//Sorts the dice
	void Board::sortDice(int *dice);
	// check if straight, either 4 or 5 in a row
	bool Board::checkStraight(int seq);

	Board();
	~Board();

};

