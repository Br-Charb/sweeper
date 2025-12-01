#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "gameWindow.h"
#include "welcomeWindow.h"

int main() {
    std::ifstream file("files/config.cfg");

    unsigned int rows; unsigned int cols; unsigned int mines;
    file >> rows >> cols >> mines;
    welcomeWindow w(rows, cols);
    w.openWindow();

    if (w.getClosed()) {
        gameWindow game(rows, cols, mines, w.getName());
        game.openGame();
    }

    return 0;
}