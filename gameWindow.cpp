//
// Created by Ben Charbonneau on 11/25/25.
//

#include "gameWindow.h"

gameWindow::gameWindow(unsigned int w, unsigned int h, unsigned int m) {
    game_rows = w;
    game_cols = h;
    game_w = w*32;
    game_h = h*32 + 100;
    game_m = m;
}


void gameWindow::openGame() {
    sf::RenderWindow window(sf::VideoMode({game_w, game_h}), "Minesweeper", sf::Style::Close);
    std::vector<std::vector<sf::Sprite>> sprites;
    sf::Texture tile_hidden("files/images/tile_hidden.png", false, sf::IntRect({0, 0}, {32, 32}));
    for (int col = 0; col < game_cols; col++) {
        std::vector<sf::Sprite> sprite_row;
        for (int row = 0; row < game_rows; row++) {
            sf::Sprite tile(tile_hidden);
            tile.setPosition({row*32.0f, col*32.0f});
            sprite_row.push_back(tile);
        }
        sprites.push_back(sprite_row);
    }

    // sf::Texture tile_hidden("files/images/tile_hidden.png", false, sf::IntRect({0, 0}, {32, 32}));
    // sf::Sprite tile(tile_hidden);
    // tile.setPosition({40, 40});

    while(window.isOpen()) {
        while(const auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (int col = 0; col < game_cols; col += 1) {
            for (int row = 0; row < game_rows; row += 1) {
                std::cout << col << " " << row << std::endl;
                window.draw(sprites[col][row]);
            }
        }
        window.display();
    }
}