//
// Created by Ben Charbonneau on 11/25/25.
//

#include "gameWindow.h"
#include <map>

gameWindow::gameWindow(unsigned int w, unsigned int h, unsigned int m) {
    game_rows = h;
    game_cols = w;
    game_w = w*32;
    game_h = h*32 + 100;
    game_m = m;
    game_over = false;
    gameGoing = true;
}

bool gameWindow::checkBounds(int row, int col) {
    return (0 <= col && col < game_cols && 0 <= row && row < game_rows);
}

int gameWindow::checkAround(std::vector<std::vector<int>> grid, int row, int col) {
    int minesCount = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (checkBounds(row + x, col + y)) {
                if (grid[row + x][col + y] == -1) {
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
            board[rNum/game_cols][rNum % game_cols] = -1; //maybe issue
        }
    }


    for (int row = 0; row < game_rows; row++) {
        for (int col = 0; col < game_cols; col++) {
            if (board[row][col] != -1) {
                board[row][col] = checkAround(board, row, col);
            }
        }
    }

    return board;

}

void gameWindow::revealAround(std::vector<std::vector<tile>> &tiles, int row, int col) {
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (checkBounds(row + x, col + y)) {
                if (tiles[row + x][col + y].getNumber() != -1 && !tiles[row + x][col + y].getClicked()) {
                    std::cout << row + x << " " << col + y << std::endl;
                    tiles[row + x][col + y].reveal();
                    if (tiles[row+x][col+y].getNumber() == 0) {
                        revealAround(tiles, row + x, col + y);
                    }
                }
            }
        }
    }
}

void gameWindow::openGame() {

    //create window
    sf::RenderWindow window(sf::VideoMode({game_w, game_h}), "Minesweeper", sf::Style::Close);
    while (gameGoing) {
        game_over = false;

        //Generate board with mines
        std::vector<std::vector<int>> board = gameWindow::boardLayout();

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

        //render buttons
        //happy button
        sf::Texture happyFace("files/images/face_happy.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Sprite happyFaceButton(happyFace);
        happyFaceButton.setPosition({((game_cols/2.0f)*32)-32, 32*(game_rows+0.5f)});

        //debug button
        sf::Texture debug("files/images/debug.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Sprite debugButton(debug);
        debugButton.setPosition({(game_cols*32.0f)-304, 32*(game_rows+0.5f)});

        //pause/play button
        sf::Texture pause("files/images/pause.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture play("files/images/play.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Sprite pausePlay(pause);
        pausePlay.setPosition({(game_cols*32.0f)-240, 32*(game_rows+0.5f)});


        //leaderboard button
        sf::Texture leadBoardTexture("files/images/leaderboard.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Sprite leaderBoardSprite(leadBoardTexture);
        leaderBoardSprite.setPosition({(game_cols*32.0f)-176, 32*(game_rows+0.5f)});



        //counter


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
        for (int row = 0; row < game_rows; row++) {
            std::vector<tile> sprite_row;
            for (int col = 0; col < game_cols; col++) {
                tile t(textures, board[row][col]);
                t.getTile().setPosition({col*32.0f, row*32.0f});
                t.getFlag().setPosition({col*32.0f, row*32.0f});
                sprite_row.push_back(t);
            }
            tiles.push_back(sprite_row);
        }
        bool resetBoard = true;
        //run window
        while(window.isOpen() && resetBoard) {
            while(const auto event = window.pollEvent()) {
                if(event->is<sf::Event::Closed>()) {
                    gameGoing = false;
                    resetBoard = false;
                }
                if (!game_over) {
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                            auto mousePos = sf::Mouse::getPosition(window);
                            for (int row = 0; row < game_rows; row += 1) {
                                for (int col = 0; col < game_cols; col += 1) {
                                    if (tiles[row][col].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                                        tiles[row][col].becomeFlag();
                                    }
                                }
                            }
                        }
                    }

                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            auto mousePos = sf::Mouse::getPosition(window);
                            for (int row = 0; row < game_rows; row += 1) {
                                for (int col = 0; col < game_cols; col += 1) {
                                    if (tiles[row][col].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                                        tiles[row][col].reveal();
                                        if (tiles[row][col].getNumber() == 0) {
                                            revealAround(tiles, row, col);
                                        }
                                        else if (tiles[row][col].getNumber() == -1) {
                                            game_over = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(happyFaceButton);
            window.draw(debugButton);
            window.draw(pausePlay);
            window.draw(leaderBoardSprite);

            for (int row = 0; row < game_rows; row += 1) {
                for (int col = 0; col < game_cols; col += 1) {
                    window.draw(tiles[row][col].getTile());
                    if (game_over && tiles[row][col].getNumber() == -1) {
                        tiles[row][col].reveal();
                    }
                    if (tiles[row][col].getFlagged()) {window.draw(tiles[row][col].getFlag());}
                }
            }
            window.display();
        }
    }
    window.close();
}