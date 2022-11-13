#pragma once
#include <iostream>
#include <vector> 

class TTTBoard {
private:
	char board[2] = { '\0', '\0' };
	bool checkPosition(int, int);
public:
	void updateBoard(int, int, bool);
	char threeInARow();
	void drawBoard();
};

