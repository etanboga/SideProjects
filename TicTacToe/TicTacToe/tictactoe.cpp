#include <iostream>
using namespace std;

class Gameboard
{
public:Gameboard()
{
	for (int i = 0; i < 9; i++)
		pos[i] = '0' + i + 1; //converting to character
	drawBoard();
}
	   void drawBoard() //draws the gameboard
	   {
		   cout << endl
			   << pos[0] << " | " << pos[1] << " | " << pos[2]
			   << "\n--|---|--\n"
			   << pos[3] << " | " << pos[4] << " | " << pos[5]
			   << "\n--|---|--\n"
			   << pos[6] << " | " << pos[7] << " | " << pos[8]
			   << endl;
	   }
	   void getHumanMove() //gets input from player
	   {
		   cout << endl << "Enter the position you want to put O to: ";
		   int move;
		   cin >> move;
		   if (move > 0 && move < 10 && (pos[move] != 'X' || pos[move] != 'O'))
			   pos[move - 1] = 'O';
	   }

	   void getComputerMove()
	   {
		   int a = pickMoveForX();
		   pos[a] = 'X';
	   }

	   int gameIsOverint()
	   {
		   int board[8][3] = { { 0,1,2 },
		   { 3,4,5 },
		   { 6,7,8 },
		   { 0,3,6 },
		   { 1,4,7 },
		   { 2,5,8 },
		   { 0,4,8 },
		   { 2,4,6 } }; // winning possibilities

		   for (int i = 0; i < 8; i++) // scroll through possibilities
		   {
			   if ((pos[board[i][0]] == pos[board[i][1]])
				   && (pos[board[i][1]] == pos[board[i][2]]) && (pos[board[i][0]] == 'X'))
				   return 1;
			   if ((pos[board[i][0]] == pos[board[i][1]])
				   && (pos[board[i][1]] == pos[board[i][2]]) && (pos[board[i][0]] == 'O'))
				   return 2;
		   }
		   if (isGridFull())
			   return 3;
		   return 4;
	   }
	   int gameIsOverTemppos()
	   {
		   int board[8][3] = { { 0,1,2 },
		   { 3,4,5 },
		   { 6,7,8 },
		   { 0,3,6 },
		   { 1,4,7 },
		   { 2,5,8 },
		   { 0,4,8 },
		   { 2,4,6 } }; // winning possibilities

		   for (int i = 0; i < 8; i++) // scroll through possibilities
		   {
			   if ((temppos[board[i][0]] == temppos[board[i][1]])
				   && (temppos[board[i][1]] == temppos[board[i][2]]) && (temppos[board[i][0]] == 'X'))
				   return 1;
			   if ((temppos[board[i][0]] == temppos[board[i][1]])
				   && (temppos[board[i][1]] == temppos[board[i][2]]) && (temppos[board[i][0]] == 'O'))
				   return 2;
		   }
		   if (isTempposFull())
			   return 3;
		   return 4;
	   }

	   bool isGridFull()  //checks if the grid is fully occupied
	   {
		   int tempcount = 0;
		   for (int i = 0; i < 9; i++)
			   if (pos[i] != 'O'&&pos[i] != 'X')
				   tempcount++;
		   if (tempcount == 0)
			   return true;
		   return false;
	   }

	   bool isTempposFull()
	   {
		   int tempcount = 0;
		   for (int i = 0; i < 9; i++)
			   if (temppos[i] != 'O'&&temppos[i] != 'X')
				   tempcount++;
		   if (tempcount == 0)
			   return true;
		   return false;
	   }

	   bool gameIsOver()
	   {
		   int Over = gameIsOverint();
		   if (Over == 1)
		   {
			   cout << "Computer wins!" << endl; //return true when computer wins 
			   return true;
		   }
		   else if (Over == 2)
		   {
			   cout << "Player wins!" << endl; //return true when player wins
			   return true;
		   }
		   else if (Over == 3)
		   {
			   cout << "TIE GAME! WELL PLAYED!" << endl;
			   return true;
		   }
		   else
			   return false;
	   }
	   int pickMoveForX()
	   {
		   int b = 10;  //make this a non member of the pos array to spot errors easier, will be useful later
		   int minSum = 100000; //starting of with a big value so that we know there is an actual min. minimum sum of result+outcome in loop
		   for (int i = 0; i < 9; i++) //goes through every available position
		   {
			   if (pos[i] != 'X'&&pos[i] != 'O')
			   {
				   temporarilyTryTheMove(i, 'X'); //tries a move at the first available position
				   int outcome = gameIsOverTemppos();
				   int xStatus = 0;
				   if (outcome == 1)  //if X wins, assigns 1 to xstatus
					   xStatus = 1;
				   else if (outcome == 3) //assign different numbers to outcome depending on what happened with the tried move, if tie game assign 2 to xstatus
					   xStatus = 2;
				   else
					   xStatus = 3;  //otherwise, moves will be equally unimportant for x so will assign 3
				   int result = howMuchOCouldHurtMeIfIMadeThisMove(); //result of how much O could do if you made this move, returns big number if hurts a lot, small if it doesn't hurt much
				   if ((result + xStatus) < minSum)
				   {
					   minSum = result + xStatus; //if result+xStatus of this iteration of the loop is smaller than minSum, assigns that as minSum because that is the lowest risk/best outcome
					   b = i;
				   }

				   temporarilyTryTheMove(i, i + '0');
			   }//to return back to initial position
		   }
		   return b;  //returns the position to put X for the best outcome
	   }

	   int howMuchOCouldHurtMeIfIMadeThisMove()
	   {
		   if (!(gameIsOverTemppos() == 4))  //breaking condition
			   return 0;
		   for (int c = 0; c < 9; c++)
		   {
			   if (temppos[c] != 'X'&&temppos[c] != 'O')
			   {
				   changeTempTry(c, 'O');
				   int score = howMuchXCouldHurtMeIfIMadeThisMove();
				   changeTempTry(c, c + '0');	//to return back to initial position
			   }
		   }
		
		   //return 1;
	   }
	   int howMuchXCouldHurtMeIfIMadeThisMove()
	   {
		   if (!(gameIsOverTemppos() == 4))  //breaking condition
			   return 0;
		   int maxSum = 0;; //starting of with a big value so that we know there is an actual min. minimum sum of result+outcome in loop
		   for (int b = 0; b < 9; b++)
		   {
			   if (temppos[b] != 'X'&&temppos[b] != 'O')
			   {
				   changeTempTry(b, 'X');
				   int score = howMuchOCouldHurtMeIfIMadeThisMove();
				   changeTempTry(b, b + '0');	//to return back to initial position
			   }
		   }
		  
	   }
	   void temporarilyTryTheMove(const int& i, char c)
	   {
		   for (int k = 0; k < 9; k++)
			   temppos[k] = pos[k];
		   temppos[i] = c;
	   }

	   void changeTempTry(const int& i, char c)
	   {
		   temppos[i] = c;
	   }

private:
	char pos[9];
	char temppos[9]; //copy of our actual Tic-Tac-Toe grid for the temporarilyTryTheMove function
};


int main()
{
	Gameboard b;

	while (!(b.gameIsOver()))
	{
		b.getComputerMove();
		b.drawBoard();
		if (b.gameIsOver())
			break;
		b.getHumanMove();
		b.drawBoard();
	}
}