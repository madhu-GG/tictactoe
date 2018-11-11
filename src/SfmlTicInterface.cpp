/*
 * SfmlTicInterface.cpp
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 */

#include "SfmlTicInterface.h"
#include <iostream>

namespace tic {

SfmlTicInterface::SfmlTicInterface()
{
	this->videoMode.height = 768;
	this->videoMode.width = 1024;

	this->gameBox.setSize(sf::Vector2f(600,600));
	this->gameBox.setPosition(100,100);
	this->gameBox.setFillColor(sf::Color::Green);
	this->window.create(this->videoMode, "Tic Tac Toe");
}

void SfmlTicInterface::run()
{
	while (this->window.isOpen())
	{
		this->handleEvents();
		this->updateGame();

		if (this->game.isDraw())
			std::cout << "Game is a Draw" << std::endl;

		if (this->game.getWinner() != PieceType::EMPTY)
		{
			std::cout << "The winner is " <<
			((this->game.getWinner() == PieceType::CROSS)? "CROSS" : "NOUGHT")
					<< std::endl;
		}

		if (this->game.isDraw() || this->game.getWinner() != PieceType::EMPTY)
		{
			this->window.close();
		}
	}
}

void SfmlTicInterface::handleEvents()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			std::cout << __func__ << " mouse pressed!" << std::endl;
			sf::Rect<float> gameBound = this->gameBox.getGlobalBounds();
			if (gameBound.contains(event.mouseButton.x, event.mouseButton.y))
			{
				int row = (event.mouseButton.y - gameBound.top) / int(gameBound.height/BOARD_SIZE);
				int col = (event.mouseButton.x - gameBound.left) / int(gameBound.width/BOARD_SIZE);

				std::cout << __func__ << " inside box row: " << row << ", col:" << col << std::endl;

				if (this->game.isMoveValid(row, col))
				{
					this->game.makeMove(row, col);
				}
			}
		}
	}
}

void SfmlTicInterface::updateGame()
{
	this->window.clear(sf::Color::Black);
	this->window.draw(this->gameBox);

	sf::Rect<float> gameBound = this->gameBox.getGlobalBounds();
	sf::Rect<float> boxBound;

	sf::CircleShape nought;
	sf::RectangleShape boxShape;
	this->game.getBoard(this->boardState);

	nought.setRadius((gameBound.width/BOARD_SIZE)/2 - 10);

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			float left = ((gameBound.width/BOARD_SIZE) * col) + gameBound.left;
			float top = ((gameBound.height/BOARD_SIZE) * row) + gameBound.top;
			float width = gameBound.width/BOARD_SIZE;
			float height = gameBound.height/BOARD_SIZE;

			boxShape.setPosition(left,top);
			boxShape.setSize(sf::Vector2f(width, height));
			boxShape.setOutlineThickness(10);
			boxShape.setOutlineColor(sf::Color::Red);
			boxShape.setFillColor(sf::Color::White);

			this->window.draw(boxShape);

			if (this->boardState[row][col] == PieceType::NOUGHT)
			{
				nought.setPosition(left + (width / 4), top + (height / 4));
				nought.setRadius((width/2) - 50);
				nought.setOutlineColor(sf::Color::Yellow);
				nought.setOutlineThickness(10);
				this->window.draw(nought);
			}
			else if (this->boardState[row][col] == PieceType::CROSS)
			{
				boxShape.setPosition(left + 20, top + 20);
				boxShape.rotate(45.0);
				boxShape.setSize(sf::Vector2f(width + 10, 1));
				boxShape.setOutlineColor(sf::Color::Yellow);
				boxShape.setFillColor(sf::Color::Yellow);
				boxShape.setOutlineThickness(2);
				this->window.draw(boxShape);
				boxShape.setPosition(left + 20, top + height - 20);
				boxShape.rotate(-90.0);
				this->window.draw(boxShape);

				boxShape.setRotation(0);
			}
		}
	}

	this->window.display();
}

void SfmlTicInterface::resetGame()
{

}

SfmlTicInterface::~SfmlTicInterface() {
	// TODO Auto-generated destructor stub
}

} /* namespace tic */
