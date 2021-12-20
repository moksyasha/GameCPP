#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "view.h"
#include "model.h"


#define X 10
#define Y 10

class Controller {
public:
	Controller(Model& model) {
		this->SetModel(model);
	}

	void SetModel(Model& model) {
		this->modelContr = model;
	}

	int max_x_coord, max_y_coord;

	int reversiBoard[Y][X];
	int tempBoard[Y][X];
	int chips[3]; //0-black 1-white 3-all

	int calc_count_enemies(int i, int j, int i_plus, int j_plus, int enem, int team, bool reprint);
	int calculate_max(int io, int jo, int player);
	bool check_around(int i, int j, int player);
	int find_max(int player);
	void reprint(int x, int y, int enemy_number, int teammate_number);
	void play(int versus_comp);
	void winner();

private:
	Model modelContr;
	View viewContr;
};