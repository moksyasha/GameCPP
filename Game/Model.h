#pragma once
#include <string>
using namespace std;

#define X 10
#define Y 10

// Model is responsible for data get and set
class Model {
public:
    Model() {
        this->SetData();
    }
    

    void SetData() {
        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                this->tempBoard[i][j] = 0;
                this->reversiBoard[i][j] = 0;
            }
        }
    }

    void initializeBoard() {
        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                this->tempBoard[i][j] = 0;
                this->reversiBoard[i][j] = 0;
            }
        }

        //0-black 1-white 3-all
        this->chips[0] = 2;
        this->chips[1] = 2;
        this->chips[2] = 60;

        this->reversiBoard[4][4] = 176;
        this->reversiBoard[4][5] = 219;
        this->reversiBoard[5][4] = 219;
        this->reversiBoard[5][5] = 176;

        this->tempBoard[4][4] = 176;
        this->tempBoard[4][5] = 219;
        this->tempBoard[5][4] = 219;
        this->tempBoard[5][5] = 176;
    }

    void copy_board() {
        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                this->tempBoard[i][j] = this->reversiBoard[i][j];
            }
        }
    }

    int reversiBoard[Y][X];
    int tempBoard[Y][X];
    int chips[3]; //0-black 1-white 3-all
};