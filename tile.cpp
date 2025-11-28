//
// Created by Ben Charbonneau on 11/26/25.
//

#include "tile.h"

tile::tile(std::map<std::string, sf::Texture*> tex, int n) : sprt(sf::Sprite(*tex["tile_hidden"])), flag(sf::Sprite(*tex["flag"])) {
    number = n;
    clicked = false;
    flagged = false;
    if (n == -1) {
        mine = true;
    } else {
        mine = false;
    }
    textures = tex;
}

bool tile::getFlagged() {
    return flagged;
}

sf::Sprite& tile::getTile() {
    return sprt;
}

sf::Sprite& tile::getFlag() {
    return flag;
}


void tile::becomeFlag() {
    flagged = !flagged;
}

int tile::getNumber() {
    return number;
}

bool tile::getMine() {
    return mine;
}

bool tile::getClicked() {
    return clicked;
}

void tile::reveal() {
    sprt.setTexture(*textures["0"]);
    flagged = true;
    clicked = true;
    if (mine) {
        flag.setTexture(*textures["mine"]);
    }
    else {
        flag.setTexture(*textures[std::to_string(number)]);
    }
}