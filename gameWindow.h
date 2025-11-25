//
// Created by Ben Charbonneau on 11/25/25.
//

#ifndef SWEEPER_GAMEWINDOW_H
#define SWEEPER_GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>


class gameWindow {
public:
    gameWindow(unsigned int w, unsigned int h, unsigned int m);
    void openGame();
private:
    unsigned int game_rows;
    unsigned int game_cols;
    unsigned int game_w;
    unsigned int game_h;
    unsigned int game_m;
};


#endif //SWEEPER_GAMEWINDOW_H