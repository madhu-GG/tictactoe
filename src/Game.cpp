/*
 * Game.cpp
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 */

#include "Game.h"

namespace tic {

Game::Game() {
	this->current = PieceType::CROSS;
	this->winner = PieceType::EMPTY;
	this->num_moves = 0;
	for (auto &row : this->board)
	{
		row.fill(PieceType::EMPTY);
	}
}

const PieceType Game::getCurrentPlayer()
{
	return this->current;
}

const PieceType Game::getWinner()
{
	return this->winner;
}

void Game::getBoard(PieceType resultBoard[BOARD_SIZE][BOARD_SIZE])
{
	int i=0;
	for (auto &row: this->board)
	{
		int j=0;
		for (auto &col: row)
		{
			resultBoard[i][j] = col;
			j++;
		}
		i++;
	}
}

void Game::updateWinner(int r, int c)
{
	PieceType lastMove = board[r][c];
	bool isDifferent;

	/*
	 * check row
	 * */
	isDifferent = false;
	for (auto &col: board[r])
	{
		if(col != lastMove)
		{
			isDifferent = true;
		}
	}

	if (isDifferent == false)
	{
		this->winner = lastMove;
		return;
	}

	/*
	 * check column
	 * */
	isDifferent = false;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		if (lastMove != board[row][c])
		{
			isDifferent = true;
		}
	}

	if (isDifferent == false)
	{
		this->winner = lastMove;
		return;
	}

	/*
	 * check main diagonal
	 * */
	if (r == c)
	{
		isDifferent = false;
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			if (lastMove != board[row][row])
			{
				isDifferent = true;
			}
		}

		if (isDifferent == false)
		{
			this->winner = lastMove;
			return;
		}
	}

	/*
	 * check the other diagonal
	 * */
	if (r + c + 1 == BOARD_SIZE)
	{
		isDifferent = false;
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			if (lastMove != board[row][BOARD_SIZE - row - 1])
			{
				isDifferent = true;
			}
		}

		if (isDifferent == false)
		{
			this->winner = lastMove;
			return;
		}
	}
}

bool Game::isMoveValid(int row, int col)
{
	if (row >= BOARD_SIZE || col >= BOARD_SIZE || row < 0 || col < 0)
	{
		return false;
	}

	if (this->num_moves >= MAX_MOVES)
	{
		return false;
	}

	if (this->winner != PieceType::EMPTY)
	{
		return false;
	}

	if (this->board[row][col] != PieceType::EMPTY)
	{
		return false;
	}

	if (this->current == PieceType::EMPTY)
	{
		return false;
	}

	return true;
}

bool Game::isDraw()
{
	return ((this->winner == PieceType::EMPTY) &&
			(this->num_moves >= MAX_MOVES));
}

void Game::makeMove(int row, int col)
{
	if (!this->isMoveValid(row, col))
	{
		return;
	}
	else
	{
		this->board[row][col] = this->current;
		this->num_moves++;

		if (this->current == PieceType::CROSS)
		{
			this->current = PieceType::NOUGHT;
		}
		else
		{
			this->current = PieceType::CROSS;
		}

		this->updateWinner(row, col);
		return;
	}

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

} /* namespace tic */
