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
    std::vector<std::pair<std::string, std::string>> readFile();
    void writeFile(std::vector<std::pair<std::string, std::string>> nameScores);
    leaderBoard(int rows, int cols, std::string fp, bool jw);
    bool getClosed();
    void setText(sf::Text &text, float x, float y);
    void addScore(std::string name, std::string t);
    void setJustWon(bool jw);
    void openWindow();

private:
    unsigned int width;
    unsigned int height;
    bool closed;
    bool justWon;
    std::vector<std::pair<std::string, std::string>> allScores;
    int spot;
    std::string filePath;
};


#endif //SWEEPER_LEADERBOARD_H