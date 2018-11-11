//============================================================================
// Name        : TicTacToe.cpp
// Author      : Madhu
// Version     :
// Copyright   : MIT License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFML/Graphics.hpp>
#include <iostream>

#include "SfmlTicInterface.h"

using namespace std;

int main(int argc, char **argv)
{
	tic::SfmlTicInterface tictactoe;
	tictactoe.run();
	return 0;
}
