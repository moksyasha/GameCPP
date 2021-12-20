#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "windows.h"
#include "View.h"
#include "Model.h"

using namespace std;


void View::displayBoard(int board[X][Y])
{
	system("CLS");
	cout << "\n\n     ";
	for (int i = 1; i < 9; i++) {
		cout << "   " << i;
	}
	cout << endl;

	for (int i = 1; i < Y - 1; i++) {
		cout << "      ";
		for (int i = 0; i < 8; i++) {
			cout << "+---";
		}
		cout << '+' << endl << "    " << i << ' ';

		for (int j = 1; j < X - 1; j++) {
			switch (board[i][j])
			{
			case 176:
				cout << "| " << (char)board[i][j] << ' ';
				break;
			case 219:
				cout << "| " << (char)board[i][j] << ' ';
				break;
			case 0:
				cout << "|   ";
				break;
			default:
				cout << "| " << (char)15 << ' ';
				break;
			}
		}
		cout << "|" << endl;
	}

	cout << "      ";
	for (int i = 0; i < 8; i++) {
		cout << "+---";
	}
	cout << "+\n\nBlack chips: " << this->modelView.chips[0];
	cout << "\nWhite chips: " << this->modelView.chips[1];
	cout << "\nChips left: " << this->modelView.chips[2] << "\n\n";
}

void View::howToPlay()
{
	system("CLS");

	cout << "How to play Reversi\n" << endl;
	cout << "Players battle to finish the game with more of their own pieces on the board than their opponent.\n"
		<< "The game is classed as finished when "
		<< "there are no spaces left on the board \nor there are no more possible legal moves for either competitor." << endl;

	cout << "Please press enter to continue...";
	cin.ignore(99, '\n');
	getchar();

	system("CLS");
}


void View::print_menu() {
	system("CLS");
	cout << "Reversi" << endl << endl;
	cout << "Please choose an option" << endl;
	cout << "1 - Play Game versus the human!" << endl;
	cout << "2 - Play Game versus the computer!" << endl;
	cout << "3 - How to Play?" << endl;
	cout << "0 - Exit." << endl;
	cout << ": ";
}

void View::printWinner(int a) {

	switch (a)
	{
	case 0:
		cout << "Black's win!\n";
		break;
	case 1:
		cout << "White's win!\n";
		break;
	default:
		cout << "Draw!\n";
		break;
	}

	getchar();
	return;
}