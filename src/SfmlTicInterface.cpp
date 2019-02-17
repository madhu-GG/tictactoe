/*
 * SfmlTicInterface.cpp
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 */

#include "SfmlTicInterface.h"
#include <iostream>
#include <string>

namespace tic {

/*** private begin ***/

/* function name: SfmlTicInterface::convertToGUICoords (int row, int col)
 *
 * description:   converts game coordinates to the (top,left) coordinates
 *                of boxes in the TicTacToe 3x3 grid as represented in the GUI.
 *                If the game coordinates are out of bounds, then (-1,-1) is returned.
 *
 * arguments:
 *     row, col - the index of the box in the TicTacToe grid to convert to game coordinates
 *
 * returns:
 *     sf::Vector2f - the (x, y) pair in the screen where this
 *                    grid's (top,left) pixel is located.
 *     (-1,-1)        If the game coordinates are out of bounds.
 *
 * */
sf::Vector2f SfmlTicInterface::convertToGUICoords (int row, int col)
{
	sf::Vector2f vec = {-1, -1};
	sf::Rect<float> gameBound = this->gameBox.getGlobalBounds();

	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
	{
		std::cout << __func__ << " game coordinates are out of bounds!"
				<< std::endl;
	}
	else
	{
		vec.y = row * (gameBound.height/BOARD_SIZE) + gameBound.top;
		vec.x = col * (gameBound.width/BOARD_SIZE) + gameBound.left;
	}

	return vec;
}

/* function name: SfmlTicInterface::convertToGameCoords (sf::Vector2f)
 *
 * description:   converts screen coordinates to (column,row)
 *                of the boxes in the TicTacToe 3x3 grid. If the screen
 *                coordinates are out of bounds, then (-1,-1) is returned.
 *
 * arguments:
 *     sf::Vector2f - the x,y coordinate to convert to game coordinates
 *
 * returns:
 *     sf::Vector2i - the (column, row) pair in the TicTacToe grid where this
 *                    screen coordinate falls.
 *     (-1,-1)        If the screen coordinate is out of bounds.
 *
 * */
sf::Vector2i SfmlTicInterface::convertToGameCoords(sf::Vector2f wvec)
{
	sf::Vector2i gvec;
	sf::Rect<float> gameBound = this->gameBox.getGlobalBounds();

	if (gameBound.contains(wvec))
	{
		gvec.y = (wvec.y - gameBound.top) / int(gameBound.height/BOARD_SIZE);
		gvec.x = (wvec.x - gameBound.left) / int(gameBound.width/BOARD_SIZE);

	} else
	{
		gvec = {-1,-1};
	}

	return gvec;
}

/*** private end ***/

/*** public begin ***/

void SfmlTicInterface::resetGame()
{

}

/* function name: SfmlTicInterface::SfmlTicInterface()
 *
 * description:   Constructor for the SfmlTicInterface class. Loads the textures
 *                required to draw the game to the window. Initializes and creates
 *                the RenderWindow for the game.
 *
 * arguments:     Nil.
 *
 * returns:       Nil.
 * */
SfmlTicInterface::SfmlTicInterface()
{

	this->videoMode.height = 768;
	this->videoMode.width = 1024;

	this->gameBox.setFillColor(sf::Color::Green);
	this->window.create(this->videoMode, "Tic Tac Toe");

	this->noughtTex.loadFromFile("assets/O.jpg");
	this->crossTex.loadFromFile("assets/X.jpg");
}

/* function name: SfmlTicInterface::updateGUI()
 *
 * description:   updates the RenderWindow to reflect the state
 *                of the Game. Checks the grid of the game and
 *                draws the crosses and noughts in each box.
 *
 * arguments:     Nil.
 *
 * returns:       void
 * */
void SfmlTicInterface::updateGUI()
{
	this->window.clear(sf::Color::Black);
	this->window.draw(this->gameBox);

	sf::Rect<float> gameBound = this->gameBox.getGlobalBounds();
	sf::Rect<float> boxBound;

	sf::RectangleShape boxShape;

	sf::Sprite nought;
	sf::Sprite cross;

	sf::Vector2u curSize;
	sf::Vector2f scaleFactor;

	sf::Vector2f gridSize(gameBound.width/BOARD_SIZE, gameBound.height/BOARD_SIZE);

	this->game.getBoard(this->boardState);

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			sf::Vector2f boxPos = this->convertToGUICoords(row, col);

			boxShape.setPosition(boxPos);
			boxShape.setSize(gridSize);
			boxShape.setOutlineThickness(10);
			boxShape.setOutlineColor(sf::Color::Red);
			boxShape.setFillColor(sf::Color::White);
			this->window.draw(boxShape);

			if (this->boardState[row][col] == PieceType::NOUGHT)
			{
				nought.setPosition(boxPos);
				nought.setTexture(noughtTex);
				curSize = noughtTex.getSize();
				scaleFactor.x = gridSize.x / curSize.x;
				scaleFactor.y = gridSize.y / curSize.y;
				nought.setScale(scaleFactor);
				this->window.draw(nought);
			}
			else if (this->boardState[row][col] == PieceType::CROSS)
			{
				cross.setPosition(boxPos);
				cross.setTexture(crossTex);
				curSize = crossTex.getSize();
				scaleFactor.x = gridSize.x / curSize.x;
				scaleFactor.y = gridSize.y / curSize.y;
				cross.setScale(scaleFactor);
				this->window.draw(cross);
			}
		}
	}

	this->window.display();
}

/* function name: SfmlTicInterface::updateView (sf::Vector2f resz)
 *
 * description:   scales the SFML view to a fraction of the width and height stored in resz vector.
 *
 * arguments:
 *                resz - the vector containing width and height to use for scaling.
 *
 * returns:       Nil.
 *
 * */
void SfmlTicInterface::updateView(sf::Vector2f resz)
{
	sf::Vector2f sz;
	this->window.setView(sf::View(sf::FloatRect(0, 0, resz.x, resz.y)));
	sz = static_cast<sf::Vector2f>(this->window.getSize());

	std::cout << __func__ << " window size: " << sz.x << ", " << sz.y << std::endl;

	sz.x = (sz.x * 3) / 4;
	sz.y = (sz.y * 3) / 4;

	std::cout << __func__ << " scaled size: " << sz.x << ", " << sz.y << std::endl;

	this->gameBox.setPosition(100,100);
	this->gameBox.setSize(sz);

}

/* function name: SfmlTicInterface::handleEvents()
 *
 * description:   polls the RenderWindow for events: mouse click,
 *                window resize, or player quit. If player clicks
 *                inside the game area, then the Game instance is
 *                invoked to make the player's move if it is considered
 *                valid.
 *
 * arguments:     Nil.
 *
 * returns:       void
 * */
void SfmlTicInterface::handleEvents()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			std::cout << __func__ << " window resized!" << std::endl;
			this->updateView(sf::Vector2f(event.size.width,event.size.height));
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			std::cout << __func__ << " mouse: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")"
					<< std::endl;
			sf::Vector2i gvec = this->convertToGameCoords(
					sf::Vector2f (
							event.mouseButton.x,
							event.mouseButton.y));
			if (gvec.x != -1 && gvec.y != -1)
			{
				std::cout << __func__ << "clicked inside the box - "
						  << "row: "  << gvec.y
						  << ", col:" << gvec.x
						  << std::endl;

				if (this->game.isMoveValid(gvec.y, gvec.x))
				{
					this->game.makeMove(gvec.y, gvec.x);
				}
				else
				{
					std::cout << __func__ << "Move is invalid!" << std::endl;
				}
			}
		}
	}
}

/* function name: SfmlTicInterface::run()
 *
 * description:   entry point for the TicTacToe game and also the
 *                main loop. This call only returns when the game window
 *                is closed, due to the player quitting or the game ending
 *                due to a draw or victory.
 *
 * arguments:     Nil.
 *
 * returns:       void
 * */
void SfmlTicInterface::run()
{
	this->updateView(static_cast<sf::Vector2f>(this->window.getSize()));
	while (this->window.isOpen())
	{
		this->handleEvents();
		this->updateGUI();

		if (this->game.isGameOver())
		{
			if (this->game.isDraw())
			{
				std::cout << "Game is a Draw" << std::endl;
			}
			else if (this->game.getWinner() != PieceType::EMPTY)
			{
				std::cout << "The winner is " <<
				((this->game.getWinner() == PieceType::CROSS)? "CROSS" : "NOUGHT")
						<< std::endl;
			}

			this->window.close();
		}
	}
}

SfmlTicInterface::~SfmlTicInterface() {
	// TODO Auto-generated destructor stub
}

/*** public end ***/

} /* namespace tic */
