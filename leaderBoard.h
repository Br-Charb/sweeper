//
// Created by Ben Charbonneau on 11/30/25.
//

#ifndef SWEEPER_LEADERBOARD_H
#define SWEEPER_LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>


class leaderBoard {
public:
    leaderBoard(std::string n, std::string t);

private:
    std::string name;
    std::string time;
};


#endif //SWEEPER_LEADERBOARD_H