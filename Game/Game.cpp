#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "windows.h"


using namespace std;

#define X 10
#define Y 10

int max_x_coord, max_y_coord;

int reversiBoard[Y][X];
int tempBoard[Y][X];
int chips[3]; //0-black 1-white 3-all

void copy_board() {
	for (int i = 1; i < 9; i++){
		for (int j = 1; j < 9; j++){
			tempBoard[i][j] = reversiBoard[i][j];
		}
	}
}


void intializeBoard(){

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			tempBoard[i][j] = 0;
			reversiBoard[i][j] = 0;
		}
	}

	//0-black 1-white 3-all
	chips[0] = 2;
	chips[1] = 2;
	chips[2] = 60;

	reversiBoard[4][4] = 176;
	reversiBoard[4][5] = 219;
	reversiBoard[5][4] = 219;
	reversiBoard[5][5] = 176;

	copy_board();
}


int calc_count_enemies(int i, int j, int i_plus, int j_plus, int enem, int team, bool reprint) {
	int enemy_count = 0;
	bool enemy = false, teammate = false;

	for (; (j < 9) && (i < 9) && (i > 0) && (j > 0); j += j_plus, i += i_plus) {
		if (tempBoard[i][j] == enem) {
			enemy = true;
			enemy_count++;
		}
		else if (tempBoard[i][j] == team) {
			if (reprint) {

				if (enem == 219) {
					chips[0] += enemy_count;
					chips[1] -= enemy_count;
				}
				else {
					chips[1] += enemy_count;
					chips[0] -= enemy_count;
				}
				for (int iter = enemy_count; iter > 0; iter--) {
					i -= i_plus;
					j -= j_plus;
					reversiBoard[i][j] = team;
				}

			}
			teammate = true;
			break;
		}
		else {
			break;
		}
	}
	if((enemy)&&(teammate))
		return enemy_count;
	else
		return 0;
}


int calculate_max(int io, int jo, int player) {
	
	int enemy_number = 0;
	int teammate_number = 0;

	vector <int> count_enemies;
	switch (player) {
	case 0:
		enemy_number = 219;
		teammate_number = 176;
		break;
	default:
		enemy_number = 176;
		teammate_number = 219;
		break;
	}

	///horizontal_right
	count_enemies.push_back(calc_count_enemies(io, jo+1, 0, 1, enemy_number, teammate_number, false));
	
	///vertical_down
	count_enemies.push_back(calc_count_enemies(io+1, jo, 1, 0, enemy_number, teammate_number, false));

	///horizontal_left
	count_enemies.push_back(calc_count_enemies(io, jo -1, 0, -1, enemy_number, teammate_number, false));

	///vertical_up
	count_enemies.push_back(calc_count_enemies(io-1, jo, -1, 0, enemy_number, teammate_number, false));

	///diag_up_right
	count_enemies.push_back(calc_count_enemies(io-1, jo +1, -1, 1, enemy_number, teammate_number, false));

	///diag_down_right
	count_enemies.push_back(calc_count_enemies(io+1, jo +1, 1, 1, enemy_number, teammate_number, false));

	///diag_down_left
	count_enemies.push_back(calc_count_enemies(io+1, jo -1, 1, -1, enemy_number, teammate_number, false));

	///diag_up_left
	count_enemies.push_back(calc_count_enemies(io-1, jo -1, -1, -1, enemy_number, teammate_number, false));

	return std::accumulate(count_enemies.begin(), count_enemies.end(), 0);
}


bool check_around(int i, int j, int player) {

	switch (player){
	case 0:
		player = 219;
		break;
	default:
		player = 176;
		break;
	}

	if ((tempBoard[i - 1][j] == player) || (tempBoard[i][j - 1] == player)
		|| (tempBoard[i + 1][j] == player) || (tempBoard[i][j + 1] == player)) {
		return true;
	}
	return false;
}


int find_max(int player) {
	vector <int> all_max;
	int max_for_computer = -1;
	for (int i = 1; i < 9; i++){
		for (int j = 1; j < 9; j++){
			if ((check_around(i, j, player))&&(tempBoard[i][j]!=219)&&(tempBoard[i][j]!=176)){
				int max_chip = calculate_max(i, j, player);


				all_max.push_back(max_chip);
				if (max_chip) {
					if (max_chip > max_for_computer) {
						max_x_coord = j;
						max_y_coord = i;
					}
					tempBoard[i][j] = max_chip;
				}
			}
		}
	}
	return *max_element(all_max.begin(), all_max.end());;
}


void displayBoard(int board[X][Y])
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
				//cout.width(3);
				//cout << board[i][j];
				break;
			}
		}
		cout << "|" << endl;
	}

	cout << "      ";
	for (int i = 0; i < 8; i++) {
		cout << "+---";
	}
	cout << "+\n\nBlack chips: " << chips[0];
	cout << "\nWhite chips: " << chips[1];
	cout << "\nChips left: " << chips[2] << "\n\n";
}


void reprint(int x, int y, int enemy_number, int teammate_number) {

	///horizontal_right
	calc_count_enemies(x, y + 1, 0, 1, enemy_number, teammate_number, true);

	///vertical_down
	calc_count_enemies(x + 1, y, 1, 0, enemy_number, teammate_number, true);

	///horizontal_left
	calc_count_enemies(x, y - 1, 0, -1, enemy_number, teammate_number, true);

	///vertical_up
	calc_count_enemies(x - 1, y, -1, 0, enemy_number, teammate_number, true);

	///diag_up_right
	calc_count_enemies(x - 1, y + 1, -1, 1, enemy_number, teammate_number, true);

	///diag_down_right
	calc_count_enemies(x + 1, y + 1, 1, 1, enemy_number, teammate_number, true);

	///diag_down_left
	calc_count_enemies(x + 1, y - 1, 1, -1, enemy_number, teammate_number, true);

	///diag_up_left
	calc_count_enemies(x - 1, y - 1, -1, -1, enemy_number, teammate_number, true);

}

void play(int versus_comp)
{	
	//vs_comp 1 if versus comp
	// Black = 0; White = 1
	int player = 0;
	int max = 0; 
	
	while (1) {
		if (!chips[2]) {
			break;
		}
		
		max = find_max(player);
		if (!max) {
			if (!player)
				player = 1;
			else
				player = 0;

			continue;
		}

		
		int x, y;
		switch (player) {
		case 0:
			displayBoard(tempBoard);
			cout << "[Black](" << (char)176 << ") Enter a coordinate [X Y]: ";
			while (1) {
				cin >> x >> y;
				if ((y < 9) && (x < 9) && (x > 0) && (y > 0) && (tempBoard[y][x] != 219) && (tempBoard[y][x] != 176) && (tempBoard[y][x] != 0)) {
					reversiBoard[y][x] = 176;
					reprint(y, x, 219, 176);
					chips[2]--;
					chips[0]++;
					break;
				}
				else {
					displayBoard(tempBoard);
					cout << "[Black](" << (char)176 << ") Enter a coordinate [X Y]: ";
					continue;
				}
			}
			copy_board();
			break;

		case 1:

			if (!versus_comp) {	//versus human
				displayBoard(tempBoard);
				cout << "[White](" << (char)219 << ") Enter a coordinate [X Y]: ";
				while (1) {
					cin >> x >> y;
					if ((y < 9) && (x < 9) && (x > 0) && (y > 0) && (tempBoard[y][x] != 219) && (tempBoard[y][x] != 176) && (tempBoard[y][x] != 0)) {
						reversiBoard[y][x] = 219;
						reprint(y, x, 176, 219);
						chips[2]--;
						chips[1]++;
						break;
					}
					else {
						displayBoard(tempBoard);
						cout << "[White](" << (char)219 << ") Enter a coordinate [X Y]: ";
						continue;
					}
				}
			}
			else { //versus computer
				displayBoard(reversiBoard);
				Sleep(500);
				reversiBoard[max_y_coord][max_x_coord] = 219;

				displayBoard(reversiBoard);
				Sleep(500);
				reprint(max_y_coord, max_x_coord, 176, 219);
				chips[2]--;
				chips[1]++;
			}
			copy_board();
			break;
		}
		if (!player)
			player = 1;
		else
			player = 0;
	}

	return;
}


void winner() {
	displayBoard(reversiBoard);

	if (chips[0] > chips[1]) {
		cout << "Black's win!\n";
	}
	else if (chips[0] < chips[1]) {
		cout << "White's win!\n";
	}
	else cout << "Draw!\n";
	getchar();
	return;
}


void howToPlay()
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


void print_menu() {
	system("CLS");
	cout << "Reversi" << endl << endl;
	cout << "Please choose an option" << endl;
	cout << "1 - Play Game versus the human!" << endl;
	cout << "2 - Play Game versus the computer!" << endl;
	cout << "3 - How to Play?" << endl;
	cout << "0 - Exit." << endl;
	cout << ": ";
}


int main()
{

	int choice = 0;

	do{

		int choice = 2;
		print_menu();
		cin >> choice;

		switch (choice){
		case 1:

			intializeBoard();
			displayBoard(reversiBoard);
			play(0);
			winner();
			getchar();
			break;

		case 2:

			intializeBoard();
			displayBoard(reversiBoard);
			play(1);
			winner();
			getchar();
			break;


		case 3: howToPlay();
			break;

			// Exit
		case 0: break;

			// Error
		default: 
			choice = 228;
			break;
		}

		if (choice == 0)
		{
			break;
		}

	} while (1);

	return 0;
}
