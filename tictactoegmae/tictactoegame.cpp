/* Libraries and dependencies */
#include "stdafx.h"
#include <iostream>
#include <string>

/* Just to avoid writing std:: before 'cout's */
using namespace std;

// for DrawRect function
#include "RECT.h"

// for _getch() and _putch()
#include <conio.h>

/* Global Variables */
char lastchar = 's'; // last character entered. used to give players turn and they enter one letter a time
bool lastkeyisLetter = false; // is true when last entered key was a char 'x' or 'o'
int initx = 3, inity = 2; // initial cursor coordinates
struct {
	int xCordBox = 0;
	int yCordBox = 0;
} boxPos; // maps cursor to an element in matrix
// A matrix representaion of the game
int box[3][3] = { { 0,0,0},{ 0,0,0 },{ 0,0,0 } }; // 0 : blank, 1 : x and 2 : o

// holds 'x' representing X player or 'o' for O player
char winner;

/*  Functins' declartions   */

// draws the game UI
void drawUI();

// Checks if any of the players wins
bool checkWin();

void setPrintMsg();

// resets screen and all variables
void reset();


/* Main function, program executes from here */

int main()
{
	char entry; //character entered by player
	
	drawUI(); // draw the User Interface
	setxy(initx,inity); // put the cursor in the first box
	
	/* Main program loop, we basically get characters from user until they enter 'e'
	   to exit the game.
	*/

	do {
		entry = _getch();
			switch (entry) { // the real value
			case 72:
				// code for arrow up
				if (inity > 2 && boxPos.yCordBox > 0) {
					inity -= 3;
					setxy(initx, inity);
					lastkeyisLetter = false;
					boxPos.yCordBox -= 1;
				}
				break;
			case 80:
				// code for arrow down
				if (inity < 6 &&boxPos.yCordBox < 2) {
					inity += 3;
					setxy(initx, inity);
					lastkeyisLetter = false;
					boxPos.yCordBox += 1;
				}
				break;
			case 75:
				if (initx > 3 && boxPos.xCordBox>0) {
					// code for arrow left
					initx -= 6;
					setxy(initx, inity);
					lastkeyisLetter = false;
					boxPos.xCordBox -= 1;
				}
				break;
				
			case 77:
				if (initx < 11 && boxPos.xCordBox < 2) {
					// code for arrow right
					initx += 6;
					setxy(initx, inity);
					lastkeyisLetter = false;
					boxPos.xCordBox += 1;
				}
				break;
			case 'x' : //code for when user presses 'x'
			case 'X' :
				if (lastchar == 'x') {
					MessageBoxA(NULL, "Hey!It's O player's turn", "Tic Tac Toe game", MB_OK);
					break;
				}
				if (!lastkeyisLetter && lastchar != 'x') {
					_putch(entry);
					lastkeyisLetter = true;
					box[boxPos.yCordBox][boxPos.xCordBox] = 1;
					lastchar = 'x';
				}
				if (checkWin())
				{
					setPrintMsg();
				}
				break;
			case 'o': // code for when user presses 'o'
			case 'O':
				if (lastchar == 'o') {
					MessageBoxA(NULL, "Hey!It's X player's turn", "Tic Tac Toe game", MB_OK);
					break;
				}
				if (!lastkeyisLetter && lastchar!='o') {
					_putch(entry);
					lastkeyisLetter = true;
					box[boxPos.yCordBox][boxPos.xCordBox] = 2;
					lastchar = 'o';
				}
				if (checkWin())
				{
					setPrintMsg();
				}

				break;
			case 'r':
			case 'R':
				reset();
				break;
			default:
				// I will show a message to user
				//TODO
				;
			}
		//_putch(entry);
	} while (entry!='e');
	_getch();
	return 0;
}

void drawUI() {

	/* Draw 9 consecutive rectangles */
	DrawRect(1, 1, 5, 2);
	DrawRect(7, 1, 5, 2);
	DrawRect(13, 1, 5, 2);
	DrawRect(1, 4, 5, 2);
	DrawRect(7, 4, 5, 2);
	DrawRect(13, 4, 5, 2);
	DrawRect(1, 7, 5, 2);
	DrawRect(7, 7, 5, 2);
	DrawRect(13, 7, 5, 2);
	// draw the User Interface
	setxy(1, 17); // set cursor for showing a welcome message
	cout << "Instructions : ***********************" << endl << "Press \'x'\ or \'o\' to fill the boxes, press \'e\' to exit. You may press \'r\' at anytime to reset. Enjoy!";
}

bool checkWin() {
	for (size_t i = 0; i < 3; i++)
	{
		// check rows
		if (((box[i][0] == box[i][1]) && (box[i][1] == box[i][2])) && (box[i][0] != 0)) {
			if ((box[i][0] == 1) && (box[i][1] == 1) && (box[i][2] == 1))
				winner = 'x';
			if ((box[i][0] == 2) && (box[i][1] == 2) && (box[i][2] == 2))
				winner = 'o';
			return true;
		}
		// check columns
		if ((box[0][i] == box[1][i]) && (box[1][i] == box[2][i]) && (box[0][i] != 0)) {
			if ((box[0][i] == 1) && (box[1][i] == 1) && (box[2][i] == 1))
				winner = 'x';
			if ((box[0][i] == 2) && (box[1][i] == 2) && (box[2][i] == 2))
				winner = 'o';
			return true;
		}
	}
	// check diagonal
	if ((box[0][0] == box[1][1]) && (box[1][1] == box[2][2]) && (box[0][0] != 0) && (box[1][1] != 0) && (box[2][2] != 0)) {
		if ((box[0][0] == 1) && (box[1][1] == 1) && (box[2][2] == 1))
			winner = 'x';
		if ((box[0][0] == 2) && (box[1][1] == 2) && (box[2][2] == 2))
			winner = 'o';
		return true;
	}
	//check diagonal
	if ((box[0][2] == box[1][1]) && (box[1][1] == box[2][0]) && (box[2][0] != 0) && (box[1][1] != 0) && (box[0][2] != 0)) {
		if ((box[2][0] == 1) && (box[1][1] == 1) && (box[0][2] == 1))
			winner = 'x';
		if ((box[2][0] == 2) && (box[1][1] == 2) && (box[0][2] == 2))
			winner = 'o';
		return true;
	}
	return false;
}

void setPrintMsg() {
	string msg;
	if (winner == 'x')
	{
		msg = "Player X wins!\nPress \'r\' to reset game :)";
	}
	else if (winner == 'o')
	{
		msg = "Player O wins!\nPress \'r\' to reset game :)";
	}
	setxy(1, 19);
	cout << msg;
}

void reset() {
	system("cls");
	drawUI();
	initx = 3;
	inity = 2;
	setxy(initx, inity);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			box[i][j] = 0;
		}
	}
	lastkeyisLetter = false;
	lastchar = 's';
	boxPos.xCordBox = 0;
	boxPos.yCordBox = 0;
}