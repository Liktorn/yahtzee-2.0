#include <iostream>
#include <string>
#include <time.h>

#include "Board.h"

using namespace std;

void main()
{
	srand((unsigned)time(NULL));
	Board board;

////	board.makeARoll();
//
//	board.dice[0] = 2;
//	board.dice[1] = 2;
//	board.dice[2] = 3;
//	board.dice[3] = 4;
//	board.dice[4] = 5;
//
//
////	board.printDice();
//	board.sortDice(board.dice);
//
//	cout << board.testScoreCondition(13) << endl;
//	cout << board.tempScore <<endl;
//
////	cout << board.checkStraight(5) << endl;
//	board.printDice();


	board.printBoard();


	
}