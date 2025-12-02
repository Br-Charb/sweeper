//
// Created by Ben Charbonneau on 11/25/25.
//

#ifndef SWEEPER_GAMEWINDOW_H
#define SWEEPER_GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.h"
#include "leaderBoard.h"
#include <cstdlib>

class gameWindow {
public:
    gameWindow(unsigned int h, unsigned int w, unsigned int m, std::string n, std::string ptl);
    bool checkBounds(int col, int row);
    int checkAround(std::vector<std::vector<int>> grid, int col, int row);
    std::vector<std::vector<int>> boardLayout(int r, int c);
    void revealAround(std::vector<std::vector<tile>> &tiles, int col, int row);
    void openGame();
private:
    unsigned int game_rows;
    unsigned int game_cols;
    unsigned int game_w;
    unsigned int game_h;
    int game_m;
    std::string pathToLeaderboard;
    bool game_over;
    bool gameGoing;
    bool paused;
    int revealed_count;
    bool first_click;
    bool game_win;
    bool started;
    std::string name;
};


#endif //SWEEPER_GAMEWINDOW_H