//
// Created by Ben Charbonneau on 11/30/25.
//

#ifndef SWEEPER_LEADERBOARD_H
#define SWEEPER_LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


class leaderBoard {
public:
    leaderBoard(int rows, int cols);
    bool getClosed();
    void setText(sf::Text &text, float x, float y);
    void addScore(std::string name, std::string t);
    void openWindow();

private:
    unsigned int width;
    unsigned int height;
    bool closed;
    std::vector<std::pair<std::string, std::string>> allScores;
};


#endif //SWEEPER_LEADERBOARD_H