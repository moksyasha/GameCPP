#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <Windows.h>
#include "Controller.h"
#include "View.h"

using namespace std;


#define BLACK_CODE 176
#define WHITE_CODE 219


int Controller::calc_count_enemies(int i, int j, int i_plus, int j_plus, int enem, int team, bool reprint) {
	int enemy_count = 0;
	bool enemy = false, teammate = false;

	for (; (j < 9) && (i < 9) && (i > 0) && (j > 0); j += j_plus, i += i_plus) {
		if (this->modelContr.tempBoard[i][j] == enem) {
			enemy = true;
			enemy_count++;
		}
		else if (this->modelContr.tempBoard[i][j] == team) {
			if (reprint) {

				if (enem == WHITE_CODE) {
					this->modelContr.chips[0] += enemy_count;
					this->modelContr.chips[1] -= enemy_count;
				}
				else {
					this->modelContr.chips[1] += enemy_count;
					this->modelContr.chips[0] -= enemy_count;
				}
				for (int iter = enemy_count; iter > 0; iter--) {
					i -= i_plus;
					j -= j_plus;
					this->modelContr.reversiBoard[i][j] = team;
				}

			}
			teammate = true;
			break;
		}
		else {
			break;
		}
	}
	if ((enemy) && (teammate))
		return enemy_count;
	else
		return 0;
}


int Controller::calculate_max(int io, int jo, int player) {

	int enemy_number = 0;
	int teammate_number = 0;

	vector <int> count_enemies;
	switch (player) {
	case 0:
		enemy_number = WHITE_CODE;
		teammate_number = BLACK_CODE;
		break;
	default:
		enemy_number = BLACK_CODE;
		teammate_number = WHITE_CODE;
		break;
	}

	///horizontal_right
	count_enemies.push_back(calc_count_enemies(io, jo + 1, 0, 1, enemy_number, teammate_number, false));

	///vertical_down
	count_enemies.push_back(calc_count_enemies(io + 1, jo, 1, 0, enemy_number, teammate_number, false));

	///horizontal_left
	count_enemies.push_back(calc_count_enemies(io, jo - 1, 0, -1, enemy_number, teammate_number, false));

	///vertical_up
	count_enemies.push_back(calc_count_enemies(io - 1, jo, -1, 0, enemy_number, teammate_number, false));

	///diag_up_right
	count_enemies.push_back(calc_count_enemies(io - 1, jo + 1, -1, 1, enemy_number, teammate_number, false));

	///diag_down_right
	count_enemies.push_back(calc_count_enemies(io + 1, jo + 1, 1, 1, enemy_number, teammate_number, false));

	///diag_down_left
	count_enemies.push_back(calc_count_enemies(io + 1, jo - 1, 1, -1, enemy_number, teammate_number, false));

	///diag_up_left
	count_enemies.push_back(calc_count_enemies(io - 1, jo - 1, -1, -1, enemy_number, teammate_number, false));

	return accumulate(count_enemies.begin(), count_enemies.end(), 0);
}


void Controller::reprint(int x, int y, int enemy_number, int teammate_number) 
{
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


bool Controller::check_around(int i, int j, int player) {

	switch (player) {
	case 0:
		player = WHITE_CODE;
		break;
	default:
		player = BLACK_CODE;
		break;
	}

	if ((this->modelContr.tempBoard[i - 1][j] == player) || (this->modelContr.tempBoard[i][j - 1] == player)
		|| (this->modelContr.tempBoard[i + 1][j] == player) || (this->modelContr.tempBoard[i][j + 1] == player)) {
		return true;
	}
	return false;
}


int Controller::find_max(int player) {
	vector <int> all_max;
	int max_for_computer = -1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if ((check_around(i, j, player)) 
				&& (this->modelContr.tempBoard[i][j] != WHITE_CODE)
				&& (this->modelContr.tempBoard[i][j] != BLACK_CODE))
			{

				int max_chip = calculate_max(i, j, player);

				all_max.push_back(max_chip);
				if (max_chip) {
					if (max_chip > max_for_computer) {
						this->max_x_coord = j;
						this->max_y_coord = i;
					}
					this->modelContr.tempBoard[i][j] = max_chip;
				}
			}
		}
	}
	return *max_element(all_max.begin(), all_max.end());
}

void Controller::play(int versus_comp)
{
	//vs_comp == 1 if versus comp
	// Black = 0; White = 1
	int player = 0;
	int max = 0;

	while (1) {
		viewContr.SetView(this->modelContr);
		if (!(this->modelContr.chips[2])) {
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

			this->viewContr.displayBoard(this->modelContr.tempBoard);
			cout << "[Black](" << (char)BLACK_CODE << ") Enter a coordinate [X Y]: ";
			while (1) {
				cin >> x >> y;
				if ((y < 9) && (x < 9) && (x > 0) && (y > 0)
					&& (this->modelContr.tempBoard[y][x] != WHITE_CODE)
					&& (this->modelContr.tempBoard[y][x] != BLACK_CODE)
					&& (this->modelContr.tempBoard[y][x] != 0)) {
					this->modelContr.reversiBoard[y][x] = BLACK_CODE;
					reprint(y, x, WHITE_CODE, BLACK_CODE);
					this->modelContr.chips[2]--;
					this->modelContr.chips[0]++;
					break;
				}
				else {
					this->viewContr.displayBoard(this->modelContr.tempBoard);
					cout << "[Black](" << (char)BLACK_CODE << ") Enter a coordinate [X Y]: ";
					continue;
				}
			}
			this->modelContr.copy_board();
			break;

		case 1:

			if (!versus_comp) {	//versus human
				this->viewContr.displayBoard(this->modelContr.tempBoard);
				cout << "[White](" << (char)219 << ") Enter a coordinate [X Y]: ";
				while (1) {
					cin >> x >> y;
					if ((y < 9) && (x < 9) && (x > 0) && (y > 0) 
						&& (this->modelContr.tempBoard[y][x] != WHITE_CODE)
						&& (this->modelContr.tempBoard[y][x] != BLACK_CODE)
						&& (this->modelContr.tempBoard[y][x] != 0)) {
						this->modelContr.reversiBoard[y][x] = WHITE_CODE;
						reprint(y, x, BLACK_CODE, WHITE_CODE);
						this->modelContr.chips[2]--;
						this->modelContr.chips[1]++;
						break;
					}
					else {
						this->viewContr.displayBoard(this->modelContr.tempBoard);
						cout << "[White](" << (char)WHITE_CODE << ") Enter a coordinate [X Y]: ";
						continue;
					}
				}
			}
			else { //versus computer
				this->viewContr.displayBoard(this->modelContr.reversiBoard);
				Sleep(500);
				this->modelContr.reversiBoard[this->max_y_coord][this->max_x_coord] = WHITE_CODE;

				this->viewContr.displayBoard(this->modelContr.reversiBoard);
				Sleep(500);
				reprint(this->max_y_coord, this->max_x_coord, BLACK_CODE, WHITE_CODE);
				this->modelContr.chips[2]--;
				this->modelContr.chips[1]++;
			}
			this->modelContr.copy_board();
			break;
		}
		if (!player)
			player = 1;
		else
			player = 0;
	}
	winner();
	return;
}


void Controller::winner() {
	this->viewContr.displayBoard(this->modelContr.reversiBoard);
	
	if (this->modelContr.chips[0] > this->modelContr.chips[1]) {
		this->viewContr.printWinner(0);
	}
	else if (this->modelContr.chips[0] < this->modelContr.chips[1]) {
		this->viewContr.printWinner(1);
	}
	else this->viewContr.printWinner(2);

	return;
}
