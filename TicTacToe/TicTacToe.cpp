#include <iostream>
#include "TTTBoard.h"


int main() {
	TTTBoard a;
	int x, y;
	bool XO = true;
	char win;
	std::cout << "You are playing tic tac toe.\nFirst player to get tree in a row, wins.\nX starts\n\n";
	while (true) {
		a.drawBoard();
		std::cout << "It's: ";
		if (!XO) std::cout << "O";
		if (XO) std::cout << "X";
		std::cout << "'s turn\nWrite two numbers from 1 to 3 to decide where to place it\n";
		std::cin >> x >> y;
		try {
			a.updateBoard(x, y, XO);
		} catch (std::string e) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n" << e << " Try again\n";
			continue;
		}
		XO = !XO;
		std::cout << "\n";
		win = a.threeInARow();
		if (win) {
			a.drawBoard();
			if (win == 'D') std::cout << '\n' << "It's a Draw";
			if (win != 'D') std::cout << '\n' << win << " WINS!!!!";
			break;
		}
	}
}
