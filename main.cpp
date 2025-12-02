#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "gameWindow.h"
#include "welcomeWindow.h"

int main() {
    std::ifstream file("files/config.cfg");

    unsigned int rows; unsigned int cols; unsigned int mines;
    file >> cols >> rows >> mines;
    welcomeWindow w(rows, cols);
    w.openWindow();

    if (w.getClosed()) {
        if (w.getMode() == "easy") {
            gameWindow game(12, 22, 40, w.getName(), "files/easyLeaderboard.txt");
            game.openGame();
        }
        if (w.getMode() == "hard") {
            gameWindow game(20, 30, 150, w.getName(), "files/hardLeaderboard.txt");
            game.openGame();
        }
        if (w.getMode() == "load") {
            gameWindow game(rows, cols, mines, w.getName(), "files/leaderboard.txt");
            game.openGame();
        }
    }

    return 0;
}