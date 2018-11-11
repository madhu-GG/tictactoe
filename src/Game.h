/*
 * Game.h
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 */

#ifndef GAME_H_
#define GAME_H_

#include <array>

namespace tic {

const int BOARD_SIZE = 3;
const int MAX_MOVES = BOARD_SIZE * BOARD_SIZE;

enum PieceType
{
	EMPTY,
	NOUGHT,
	CROSS
};

class Game {
private:
	std::array<std::array<PieceType,BOARD_SIZE>,BOARD_SIZE> board;

	int num_moves;
	PieceType current, winner;

	void updateWinner(int row, int col);

public:
	Game();
	const PieceType getCurrentPlayer();
	const PieceType getWinner();

	void getBoard(PieceType[BOARD_SIZE][BOARD_SIZE]);

	bool isMoveValid(int row, int col);
	bool isDraw();
	void makeMove(int row, int col);

	virtual ~Game();
};

} /* namespace tic */

#endif /* GAME_H_ */
