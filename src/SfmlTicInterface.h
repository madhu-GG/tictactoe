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

const std::string TEX_FILE_CROSS = "assets/X.jpg";
const std::string TEX_FILE_NOUGHT = "assets/O.jpg";

class SfmlTicInterface {
private:
	Game game;
	PieceType boardState[BOARD_SIZE][BOARD_SIZE];
	sf::RenderWindow window;
	sf::VideoMode videoMode;
	sf::RectangleShape gameBox;
	sf::Texture noughtTex, crossTex;

	sf::Vector2i convertToGameCoords(sf::Vector2f);
	sf::Vector2f convertToGUICoords(int row, int col);
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
