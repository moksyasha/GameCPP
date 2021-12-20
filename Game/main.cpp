#include <iostream>
#include "view.h"
#include "model.h"
#include "controller.h"


int main()
{
	Model game_main;
	View view(game_main);
	int choice = 0;
	
	do {

		int choice = 2;
		view.print_menu();
		cin >> choice;

		switch (choice) {
		case 1: {

			game_main.initializeBoard();
			Controller contrGame(game_main);
			view.displayBoard(game_main.reversiBoard);
			contrGame.play(0);
			getchar();
			break;
		}
		case 2: {

			game_main.initializeBoard();
			Controller contrGame(game_main);
			view.displayBoard(game_main.reversiBoard);
			contrGame.play(1);
			getchar();
			break;

		}
		case 3: view.howToPlay();
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
