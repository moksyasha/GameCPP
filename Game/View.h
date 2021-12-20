#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Model.h"


#define X 10
#define Y 10

class View {
public:

	View(Model& model) {
		this->SetView(model);
	}
	View() {}

	void SetView(Model& model) {
		this->modelView = model;
	}
	void winner();
	void print_menu();
	void howToPlay();
	void displayBoard(int board[X][Y]);
	void printWinner(int a);

private:
	Model modelView;
};