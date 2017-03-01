#include <iostream>
#include <time.h>
#include <string>
#include "Board.h"

using namespace std;


/******************************************************************/
// Just print the dice
void Board::printDice()
{
	// Prints the dice to the screen with "Dice no" over the dice values.
	cout << "Dice no : ";
	for (int i = 0; i < DICE; i++)
		cout << i + 1 << "   ";
	cout << endl;
	cout << "          ";
	for (int i = 0; i < DICE; i++)
		cout << Board::dice[i] << "   ";
	cout << endl;
}
/******************************************************************/
// roll all the dice
void Board::makeARoll()
{
	// randomize all the dice
	for (int i = 0; i < DICE; i++)
		Board::dice[i] = (rand() % 6) + 1;
}
/******************************************************************/
// roll only the dice containd in reRollDice
void Board::makeARoll(int *reRollDice)
{
	// randomize only the dice contained in reRollDice
	for (int i = 0; i < DICE; i++)
		if (reRollDice[i] == 1)
			Board::dice[i] = (rand() % 6) + 1;
}
/******************************************************************/
// Print the board on the screen
void Board::printBoard()
{
	cout << "här skall spelbrädet visas" << endl;




}
/******************************************************************/
// Test the score condition
bool Board::testScoreCondition(int scoreChoice)		//maybe take a value?
{
	//First check so score[scoreChoice-1] does not allready contain a value
	if (score[scoreChoice - 1] > 0)
		return false;

	// test if aces			1
	else if (scoreChoice == 1)
		return checkHowMany(1);
	//test if twos				2
	else if (scoreChoice == 2)
		return checkHowMany(2);
	//test if threes			3
	else if (scoreChoice == 3)
		return checkHowMany(3);
	//test if fours			4
	else if (scoreChoice == 4)
		return checkHowMany(4);
	// test if fives			5
	else if (scoreChoice == 5)
		return checkHowMany(5);
	//test if sixes			6
	else if (scoreChoice == 6)
		return checkHowMany(6);
	//test if 3 of a kind		7
	else if (scoreChoice == 7)
	{
		// Returns what die there is 3 of, 0 if none
		tempScore = checkIfSame(3);
		if (tempScore != 0)
		{
			tempScore *= 3;
			return true;
		}
		else
			return false;
	}
	//test if 4 of a kind		8
	else if (scoreChoice == 8)
	{
		// Returns what die there is 4 of, 0 if none
		tempScore = checkIfSame(4);
		if (tempScore != 0)
		{
			tempScore *= 4;
			return true;
		}
		else
			return false;
	}
	//test if Full House		9	//3 of one kind, 2 of another
	else if (scoreChoice == 9)
	{
		//copy the dice
		for (int i = 0; i < DICE; i++)
			dieCopy[i] = dice[i];
		//check if 3 of a kind, store what type in tmp, if 0 return false
		int tmp = checkIfSame(3);
		// if no 3 is the same
		if (tmp == 0)
		{
			//restore dice[] from dieCopy[]
			for (int i = 0; i < DICE; i++)
				dice[i] = dieCopy[i];
			return false;
		}
		// Remove the 3 dice that are the same.
		for (int i = 0; i < DICE; i++)
			if (dice[i] == tmp)
				dice[i] = 0;
		// So far so good. Now check if there also is 2 equals
		tmp = checkIfSame(2);
		// if no 2 is the same
		if (tmp == 0)
		{
			//restore dice[] from dieCopy[]
			for (int i = 0; i < DICE; i++)
				dice[i] = dieCopy[i];
			return false;
		}
		// if program comes here, that means that full house was found
		//return true and sett score to 25
		tempScore = 25;
		return true;
	}
	// test if Sm. Straight		10	eg. 1,2,3,4 in sequence
	else if (scoreChoice == 10)
	{
		sortDice(Board::dice);
		//send to method for validation.
		if (checkStraight(4))
		{
			tempScore = 30;
			return true;
		}
		else
			return false;
	}
	// test if Lg. Straight		11
	else if (scoreChoice == 11)
	{
		sortDice(Board::dice);
		//send to method for validation.
		if (checkStraight(5))
		{
			tempScore = 40;
			return true;
		}
		else
			return false;
	}
	//test if YAHTZEE (5of a kind) 12
	else if (scoreChoice == 12)
	{
		// Returns what die there is 4 of, 0 if none
		tempScore = checkIfSame(5);
		if (tempScore != 0)
		{
			tempScore *= 5;
			return true;
		}
		else
			return false;
	}
	// chance					13
	else if (scoreChoice == 13)
	{
		for (int i = 0; i < DICE; i++)
			tempScore += dice[i];
		return true;
	}
	// test if yahtzee bonus		14

	return true;
}
/******************************************************************/
//Sorts the dice
void Board::sortDice(int *pDice)
{
	for (int i = 0; i < DICE; i++)
	{
		for (int x = i+1; x < DICE; x++)
		{
			if (pDice[x] < pDice[i])
			{
				int tmp = pDice[i];
				pDice[i] = pDice[x];
				pDice[x] = tmp;

			}
		}
	}
}
/******************************************************************/
// check if straight, either 4 or 5 in a row
bool Board::checkStraight(int seq)
{
	//this is the only rows that are a small straight
	int smStraigt[3][4]{ { 1,2,3,4 }, { 2,3,4,5}, { 3,4,5,6 } };
	// this is the only large straight
	int lgStraight[]{ 1,2,3,4,5 };
	int counter = 0;
	// small straight
	if (seq == 4)
	{
		for (int i = 0; i < 3; i++)//row
		{
			for (int a = 0; a < 2; a++)		
			{

				for (int j = 0; j < 4; j++)//collomn
				{	
					int straight = smStraigt[i][j];
					int d = dice[j + a];
					// check if a row, dice by dice are the same
					if(smStraigt[i][j] == dice[j+a])
					{
						counter++;
						if (counter == 4)
							return true;
					}
					else
					{
						counter = 0;
					}
				}
				
			}
			
		}
		if (counter == 4)
			return true;
		else
		 return false;
	}
	//large straight
	else if (seq == 5)
	{
		for (int i = 0; i < DICE; i++)		//row
		{
			if (dice[i] == lgStraight[i])
				counter++;
			else
				return false;
		}
		return true;
	}
	

}
/******************************************************************/
// returns the number of same type
int Board::noOfTypes(int type)
{
	int count = 0;
	for (int i = 0; i < DICE; i++)
	{
		if (dice[i] == type)
			count++;
	}
	return count;
}
/******************************************************************/
// test if there are any of a kind. Make score and return true or false
bool Board::checkHowMany(int kind)
{
	if (noOfTypes(kind) > 0)
	{
		tempScore *= kind;
		return true;
	}
	else
		return false;
}
/******************************************************************/
// test if 3 or 4 of a kind, returns if 3 or 4 or none
int Board::checkIfSame(int kind)
{
	int theSames[]{ 0,0,0,0,0 };
	// Go throuh the dices, add the occurense of all numbers in theSames array
	for (int i = 0; i < DICE; i++)
	{
		//Do not check if dice[i] contains 0
		if (dice[i] == 0)
			break;
		int d = dice[i];	//for example if dice[3] is a 2
		theSames[d - 1]++;	//add one to the second element (index 1)
	}
	int index = 0;
	for (int i = 0; i < DICE; i++)
	{
		// check if any result is exactly the specific amount, ie. 3 or 4 of a kind
		if (theSames[i] == kind)
		{
			index = i + 1;
			break;
		}
	}
	// Return what type of die there is 3 or 4 of.
	return index;
}

/******************************************************************/
// print the choice menu
void Board::choiceMenu()
{
	cout << "Choose between: 1- Reroll all the dice.  2- Reroll some dice." << endl;
	cout << "3- Mark score.  4- Scrap a score.  5- NEW GAME.  6- QUIT" << endl;
}
/******************************************************************/
// Take input, only integers, return the input
int Board::input()
{
	int input = 0;
	// only take numbers
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	return input;
}


Board::Board()
{
}


Board::~Board()
{
}
