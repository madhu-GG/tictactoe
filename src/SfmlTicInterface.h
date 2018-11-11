/*
 * SfmlTicInterface.h
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 */

#ifndef SFMLTICINTERFACE_H_
#define SFMLTICINTERFACE_H_

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace tic {

class SfmlTicInterface {
private:
	Game game;
	PieceType boardState[BOARD_SIZE][BOARD_SIZE];
	sf::RenderWindow window;
	sf::VideoMode videoMode;
	sf::RectangleShape gameBox;
public:
	SfmlTicInterface();
	void resetGame();
	void handleEvents();
	void updateGame();
	void run();
	virtual ~SfmlTicInterface();
};

} /* namespace tic */

#endif /* SFMLTICINTERFACE_H_ */
