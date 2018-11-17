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

SfmlTicInterface::SfmlTicInterface()
{

	this->videoMode.height = 768;
	this->videoMode.width = 1024;


	this->gameBox.setFillColor(sf::Color::Green);
	this->window.create(this->videoMode, "Tic Tac Toe");



	this->noughtTex.loadFromFile("assets/O.jpg");
	this->crossTex.loadFromFile("assets/X.jpg");
}

void SfmlTicInterface::updateGame()
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

void SfmlTicInterface::handleEvents()
{
	sf::Event event;
	sf::Vector2f sz;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			this->window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			std::cout << __func__ << " window resized!" << std::endl;
			sf::Vector2f sz;
			sz = static_cast<sf::Vector2f>(this->window.getSize());

			std::cout << __func__ << " window size: " << sz.x << ", " << sz.y << std::endl;

			sz.x = (sz.x * 3) / 4;
			sz.y = (sz.y * 3) / 4;

			std::cout << __func__ << " scaled size: " << sz.x << ", " << sz.y << std::endl;

			this->gameBox.setPosition(100,100);
			this->gameBox.setSize(sz);
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

void SfmlTicInterface::run()
{
	while (this->window.isOpen())
	{
		this->handleEvents();
		this->updateGame();

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
