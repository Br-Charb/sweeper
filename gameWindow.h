//
// Created by Ben Charbonneau on 11/25/25.
//

#ifndef SWEEPER_GAMEWINDOW_H
#define SWEEPER_GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.h"

class gameWindow {
public:
    gameWindow(unsigned int w, unsigned int h, unsigned int m);
    bool checkBounds(int col, int row);
    int checkAround(std::vector<std::vector<int>> grid, int col, int row);
    std::vector<std::vector<int>> boardLayout();
    void revealAround(std::vector<std::vector<tile>> &tiles, int col, int row);
    void openGame();
private:
    unsigned int game_rows;
    unsigned int game_cols;
    unsigned int game_w;
    unsigned int game_h;
    unsigned int game_m;
    bool game_over;
    bool gameGoing;
};


#endif //SWEEPER_GAMEWINDOW_H