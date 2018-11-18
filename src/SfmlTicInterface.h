/*
 * SfmlTicInterface.h
 *
 *  Created on: 11-Nov-2018
 *      Author: madhu
 *
 *      SfmlTicInterface holds a Game instance and uses the Game API to display the GUI and read
 *      User Input using SFML.
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
	sf::Vector2i convertToGameCoords(sf::Vector2f);

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
	sf::Vector2f convertToGUICoords(int row, int col);

public:

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
	SfmlTicInterface();
	void resetGame();

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
	void handleEvents();

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
	void updateGUI();

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
	void run();
	virtual ~SfmlTicInterface();
};

} /* namespace tic */

#endif /* SFMLTICINTERFACE_H_ */
