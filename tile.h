//
// Created by Ben Charbonneau on 11/26/25.
//

#ifndef SWEEPER_TILE_H
#define SWEEPER_TILE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>


class tile {
public:
    tile(std::map<std::string, sf::Texture*> tex, int n);
    bool getFlagged();
    sf::Sprite& getTile();
    sf::Sprite& getFlag();
    int getNumber();
    bool getMine();
    bool getClicked();
    void becomeFlag();
    void reveal();

private:
    int number;
    bool clicked;
    bool flagged;
    bool mine;
    sf::Sprite sprt;
    sf::Sprite flag;
    std::map<std::string, sf::Texture*> textures;
};


#endif //SWEEPER_TILE_H