//
// Created by Ben Charbonneau on 11/25/25.
//

#include "gameWindow.h"
#include <map>

gameWindow::gameWindow(unsigned int w, unsigned int h, unsigned int m) {
    game_rows = w;
    game_cols = h;
    game_w = w*32;
    game_h = h*32 + 100;
    game_m = m;
    game_over = false;
}

bool gameWindow::checkBounds(int col, int row) {
    return (0 <= col && col < game_cols && 0 <= row && row < game_rows);
}

int gameWindow::checkAround(std::vector<std::vector<int>> grid, int col, int row) {
    int minesCount = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (checkBounds(col + x, row + y)) {
                if (grid[col + x][row + y] == -1) {
                    minesCount++;
                }
            }
        }
    }
    return minesCount;
}

std::vector<std::vector<int>> gameWindow::boardLayout() {
    std::vector<std::vector<int>> board(game_rows, std::vector<int>(game_cols, 0));
    std::vector<int> bombLocations;
    srand(static_cast<unsigned int>(time(NULL)));

    while (bombLocations.size() < game_m) {
        int rNum = (rand() % ((game_rows * game_cols)));
        bool duplicate = false;
        for (int i = 0; i < bombLocations.size(); i++) {
            if (bombLocations[i] == rNum) {
                duplicate = true;
            }
        }
        if (!duplicate) {
            bombLocations.push_back(rNum);
            board[rNum/game_cols][rNum % game_cols] = -1;
        }
    }


    for (int i = 0; i < game_cols; i++) {
        for (int j = 0; j < game_rows; j++) {
            if (board[i][j] != -1) {
                board[i][j] = checkAround(board, i, j);
            }
        }
    }

    return board;

}

void gameWindow::revealAround(std::vector<std::vector<tile>> &tiles, int col, int row) {
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (checkBounds(col + x, row + y)) {
                if (tiles[col + x][row + y].getNumber() != -1 && !tiles[col + x][row + y].getClicked()) {
                    std::cout << col + x << " " << row + y << std::endl;
                    tiles[col + x][row + y].reveal();
                    if (tiles[col+x][row+y].getNumber() == 0) {
                        revealAround(tiles, col + x, row + y);
                    }
                }
            }
        }
    }
}

void gameWindow::openGame() {
    //Generate board with mines
    std::vector<std::vector<int>> board = gameWindow::boardLayout();

    //create window
    sf::RenderWindow window(sf::VideoMode({game_w, game_h}), "Minesweeper", sf::Style::Close);

    //load textures into map
    sf::Texture tile_hidden("files/images/tile_hidden.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture tile_revealed("files/images/tile_revealed.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture flag("files/images/flag.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture mine("files/images/mine.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture one("files/images/number_1.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture two("files/images/number_2.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture three("files/images/number_3.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture four("files/images/number_4.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture five("files/images/number_5.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture six("files/images/number_6.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture seven("files/images/number_7.png", false, sf::IntRect({0, 0}, {32, 32}));
    sf::Texture eight("files/images/number_8.png", false, sf::IntRect({0, 0}, {32, 32}));

    std::map<std::string, sf::Texture*> textures;

    textures["tile_hidden"] = &tile_hidden;
    textures["flag"] = &flag;
    textures["mine"] = &mine;
    textures["0"] = &tile_revealed;
    textures["1"] = &one;
    textures["2"] = &two;
    textures["3"] = &three;
    textures["4"] = &four;
    textures["5"] = &five;
    textures["6"] = &six;
    textures["7"] = &seven;
    textures["8"] = &eight;

    //generate grid
    std::vector<std::vector<tile>> tiles;
    for (int col = 0; col < game_cols; col++) {
        std::vector<tile> sprite_row;
        for (int row = 0; row < game_rows; row++) {
            tile t(textures, board[col][row]);
            t.getTile().setPosition({row*32.0f, col*32.0f});
            t.getFlag().setPosition({row*32.0f, col*32.0f});
            sprite_row.push_back(t);
        }
        tiles.push_back(sprite_row);
    }

    //run window
    while(window.isOpen()) {
        while(const auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    for (int col = 0; col < game_cols; col += 1) {
                        for (int row = 0; row < game_rows; row += 1) {
                            if (tiles[col][row].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                                tiles[col][row].becomeFlag();
                            }
                        }
                    }
                }
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    for (int col = 0; col < game_cols; col += 1) {
                        for (int row = 0; row < game_rows; row += 1) {
                            if (tiles[col][row].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                                tiles[col][row].reveal();
                                if (tiles[col][row].getNumber() == 0) {
                                    revealAround(tiles, col, row);
                                }
                                else if (tiles[col][row].getNumber() == -1) {
                                    game_over = true;
                                }
                            }
                        }
                    }
                }
            }

        }

        window.clear(sf::Color::White);
        for (int col = 0; col < game_cols; col += 1) {
            for (int row = 0; row < game_rows; row += 1) {
                window.draw(tiles[col][row].getTile());
                if (game_over && tiles[col][row].getNumber() == -1) {
                    tiles[col][row].reveal();
                }
                if (tiles[col][row].getFlagged()) {window.draw(tiles[col][row].getFlag());}
            }
        }
        window.display();
    }
}