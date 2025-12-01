//
// Created by Ben Charbonneau on 11/25/25.
//

#include "gameWindow.h"
#include <map>



//constructor
gameWindow::gameWindow(unsigned int w, unsigned int h, unsigned int m, std::string n) {
    game_rows = h;
    game_cols = w;
    game_w = w*32;
    game_h = h*32 + 100;
    game_m = m;
    game_over = false;
    gameGoing = true;
    paused = false;
    revealed_count = 0;
    game_win = false;
    name = n;
}

//bounds checking function
bool gameWindow::checkBounds(int row, int col) {
    return (0 <= col && col < game_cols && 0 <= row && row < game_rows);
}

//finds number for tile
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

// generates board
 std::vector<std::vector<int>> gameWindow::boardLayout(int r, int c) {
     std::vector<std::vector<int>> board(game_rows, std::vector<int>(game_cols, 0));
     std::vector<int> nearTiles;
     for (int x = -1; x < 2; x++) {
         for (int y = -1; y < 2; y++) {
             if (checkBounds(r + x, c + y)) {
                 nearTiles.push_back((r+x)*game_cols + c+y);
             }
         }
     }

     std::vector<int> possibleBombLocations;
     for (int index = 0; index < game_rows*game_cols; index++) {
         if (std::find(nearTiles.begin(), nearTiles.end(), index) == nearTiles.end()) {
             possibleBombLocations.push_back(index);
         }
     }
     srand(static_cast<unsigned int>(time(NULL)));
     for (int i = 0; i < game_m; i++){
         int rNum = rand() % possibleBombLocations.size();
         board[possibleBombLocations[rNum]/game_cols][possibleBombLocations[rNum] % game_cols] = -1;
         possibleBombLocations.erase(possibleBombLocations.begin() + rNum);
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

//reveals tiles around clicked tile
void gameWindow::revealAround(std::vector<std::vector<tile>> &tiles, int row, int col) {
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (checkBounds(row + x, col + y)) {
                if (tiles[row + x][col + y].getNumber() != -1 && !tiles[row + x][col + y].getClicked() && !tiles[row + x][col + y].getFlagged()) {
                    tiles[row + x][col + y].reveal();
                    revealed_count += 1;
                    if (tiles[row+x][col+y].getNumber() == 0) {
                        revealAround(tiles, row + x, col + y);
                    }
                }
            }
        }
    }
}

//returns time digits
std::vector<int> getDigits(int numbers) {
    int minutesTens = numbers/600;
    numbers -= minutesTens*600;
    int minutesSingles = numbers/60;
    numbers -= minutesSingles*60;
    int secondsTens = numbers/10;
    numbers -= secondsTens*10;
    int secondsSingles = numbers;
    return {minutesTens, minutesSingles, secondsTens, secondsSingles};
}

void gameWindow::openGame() {

    //create window
    sf::RenderWindow window(sf::VideoMode({game_w, game_h}), "Minesweeper", sf::Style::Close);

    //create leaderboard
    leaderBoard leadBoard(game_rows, game_cols);

    //load all textures
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
        sf::Texture happyFace("files/images/face_happy.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture winFace("files/images/face_win.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture loseFace("files/images/face_lose.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture debug("files/images/debug.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture pause("files/images/pause.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture play("files/images/play.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture leadBoardTexture("files/images/leaderboard.png", false, sf::IntRect({0, 0}, {64, 64}));
        sf::Texture digits("files/images/digits.png", false, sf::IntRect({0, 0}, {231, 32}));

        //load textures for tile
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

    //allows for the game to be restarted
    while (gameGoing) {

        //initalizes variables
        game_over = false;
        int flag_count = 0;
        int pause_time = 0;
        long long time = 0;
        paused = false;
        bool justWon = true;

        std::chrono::time_point<std::chrono::steady_clock> pausedTime;


        //gets time
        std::chrono::time_point<std::chrono::steady_clock> start;

        //buttons
        //restart button
        sf::Sprite restartButton(happyFace);
        restartButton.setPosition({((game_cols/2.0f)*32)-32, 32*(game_rows+0.5f)});

        //debug button
        sf::Sprite debugButton(debug);
        debugButton.setPosition({(game_cols*32.0f)-304, 32*(game_rows+0.5f)});

        //pause/play button
        sf::Sprite pausePlay(pause);
        pausePlay.setPosition({(game_cols*32.0f)-240, 32*(game_rows+0.5f)});

        //leaderboard button
        sf::Sprite leaderBoardSprite(leadBoardTexture);
        leaderBoardSprite.setPosition({(game_cols*32.0f)-176, 32*(game_rows+0.5f)});

        //timer buttons
        sf::Sprite t1(digits);
        t1.setPosition({game_cols*32.0f-97, 32*(game_rows+0.5f)+16});
        t1.setTextureRect(sf::IntRect({0, 0}, {21, 32}));
        sf::Sprite t2(digits);
        t2.setPosition({game_cols*32.0f-76, 32*(game_rows+0.5f)+16});
        t2.setTextureRect(sf::IntRect({0, 0}, {21, 32}));
        sf::Sprite t3(digits);
        t3.setPosition({game_cols*32.0f-54, 32*(game_rows+0.5f)+16});
        t3.setTextureRect(sf::IntRect({0, 0}, {21, 32}));
        sf::Sprite t4(digits);
        t4.setPosition({game_cols*32.0f-33, 32*(game_rows+0.5f)+16});
        t4.setTextureRect(sf::IntRect({0, 0}, {21, 32}));

        //mine counter
        sf::Sprite c1(digits);
        c1.setPosition({33.0f, 32*(game_rows+0.5f)+16});
        sf::Sprite c2(digits);
        c2.setPosition({54, 32*(game_rows+0.5f)+16});
        sf::Sprite c3(digits);
        c3.setPosition({75, 32*(game_rows+0.5f)+16});
        sf::Sprite cn(digits);
        cn.setPosition({12, 32*(game_rows+0.5f)+16});
        cn.setTextureRect(sf::IntRect({210, 0}, {21, 32}));


        int tempMines = game_m;
        c1.setTextureRect(sf::IntRect({(tempMines/100)*21, 0}, {21, 32}));
        tempMines -= (tempMines/100)*100;
        c2.setTextureRect(sf::IntRect({(tempMines/10)*21, 0}, {21, 32}));
        tempMines -= (tempMines/10)*10;
        c3.setTextureRect(sf::IntRect({tempMines*21, 0}, {21, 32}));

        //generate grid
        std::vector<std::vector<tile>> tiles;
        for (int row = 0; row < game_rows; row++) {
            std::vector<tile> sprite_row;
            for (int col = 0; col < game_cols; col++) {
                tile t(textures, 0);
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
                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        auto mousePos = sf::Mouse::getPosition(window);

                        if (restartButton.getGlobalBounds().contains(sf::Vector2f(mousePos))){
                            resetBoard = false;
                            game_over = false;
                            revealed_count = 0;
                        }

                        if (leaderBoardSprite.getGlobalBounds().contains(sf::Vector2f(mousePos))){
                            if (!paused && revealed_count > 0) pausedTime = std::chrono::high_resolution_clock::now();
                            leadBoard.openWindow();
                            if (!paused && revealed_count > 0) pause_time += std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - pausedTime).count();
                        }

                        for (int r = 0; r < game_rows; r += 1) {
                            for (int c = 0; c < game_cols; c += 1) {
                                if (tiles[r][c].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos)) && revealed_count == 0 && !tiles[r][c].getFlagged()) {
                                    start = std::chrono::high_resolution_clock::now();
                                    //generate game with first click in mind
                                    std::vector<std::vector<int>> board = gameWindow::boardLayout(r, c);
                                    for (int row = 0; row < game_rows; row++) {
                                        for (int col = 0; col < game_cols; col++) {
                                            tiles[row][col].setNumber(board[row][col]);
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
                if (!game_over && revealed_count > 0) {
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                        auto mousePos = sf::Mouse::getPosition(window);
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            if (pausePlay.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                                paused = !paused;
                                if (paused) {
                                    pausePlay.setTexture(play);
                                    pausedTime = std::chrono::high_resolution_clock::now();
                                }
                                else {
                                    pausePlay.setTexture(pause);
                                    pause_time += std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - pausedTime).count();
                                }
                            }
                        }
                    }
                }
                if (!game_over && !paused) {
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                        auto mousePos = sf::Mouse::getPosition(window);
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                            for (int row = 0; row < game_rows; row += 1) {
                                for (int col = 0; col < game_cols; col += 1) {
                                    if (tiles[row][col].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos)) && tiles[row][col].getClicked() == false) {
                                        tiles[row][col].becomeFlag();
                                        if (tiles[row][col].getFlagged()) {flag_count += 1;}
                                        else{flag_count -= 1;}
                                        int minesLeft = std::abs(game_m-flag_count +0.0f);
                                        std::cout << minesLeft << std::endl;
                                        c1.setTextureRect(sf::IntRect({(minesLeft/100)*21, 0}, {21, 32}));
                                        minesLeft -= (minesLeft/100)*100;
                                        c2.setTextureRect(sf::IntRect({(minesLeft/10)*21, 0}, {21, 32}));
                                        minesLeft -= (minesLeft/10)*10;
                                        c3.setTextureRect(sf::IntRect({minesLeft*21, 0}, {21, 32}));
                                    }
                                }
                            }
                        }
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            if (debugButton.getGlobalBounds().contains(sf::Vector2f(mousePos)) && !game_over){
                                for (int row = 0; row < game_rows; row += 1) {
                                    for (int col = 0; col < game_cols; col += 1) {
                                        if (tiles[row][col].getNumber() == -1) {
                                            if (tiles[row][col].getClicked()) {
                                                tiles[row][col].unreveal();
                                            } else {
                                                tiles[row][col].reveal();
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                for (int row = 0; row < game_rows; row += 1) {
                                    for (int col = 0; col < game_cols; col += 1) {
                                        if (tiles[row][col].getTile().getGlobalBounds().contains(sf::Vector2f(mousePos)) && tiles[row][col].getFlagged() == false) {
                                            tiles[row][col].reveal();
                                            revealed_count += 1;
                                            if (tiles[row][col].getNumber() == 0) {
                                                revealAround(tiles, row, col);
                                            }
                                            else if (tiles[row][col].getNumber() == -1) {
                                                revealed_count -= 1;
                                                game_over = true;
                                                restartButton.setTexture(loseFace);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color::White);

            window.draw(restartButton);
            window.draw(debugButton);
            window.draw(pausePlay);
            window.draw(leaderBoardSprite);


            if (revealed_count != 0 && !game_over) {
                if (paused) {
                    time = std::chrono::duration_cast<std::chrono::seconds>(pausedTime - start).count() - pause_time;
                } else {
                    time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() - pause_time;
                }
                if (time > 5999) {
                    t1.setTextureRect(sf::IntRect({21*9, 0}, {21, 32}));
                    t2.setTextureRect(sf::IntRect({21*9, 0}, {21, 32}));
                    t3.setTextureRect(sf::IntRect({21*5, 0}, {21, 32}));
                    t4.setTextureRect(sf::IntRect({21*9, 0}, {21, 32}));
                } else {
                    std::vector<int> digits = getDigits(time);
                    t1.setTextureRect(sf::IntRect({21*digits[0], 0}, {21, 32}));
                    t2.setTextureRect(sf::IntRect({21*digits[1], 0}, {21, 32}));
                    t3.setTextureRect(sf::IntRect({21*digits[2], 0}, {21, 32}));
                    t4.setTextureRect(sf::IntRect({21*digits[3], 0}, {21, 32}));
                }
            }

            window.draw(t1);
            window.draw(t2);
            window.draw(t3);
            window.draw(t4);

            if (revealed_count == (game_cols*game_rows-game_m) && justWon) {
                game_over = true;
                game_win = true;

                c1.setTextureRect(sf::IntRect({0, 0}, {21, 32}));
                c2.setTextureRect(sf::IntRect({0, 0}, {21, 32}));
                c3.setTextureRect(sf::IntRect({0, 0}, {21, 32}));

                for (int row = 0; row < game_rows; row += 1) {
                    for (int col = 0; col < game_cols; col += 1) {
                        if (tiles[row][col].getNumber() == -1) {
                            tiles[row][col].unreveal();
                            tiles[row][col].becomeFlag();
                        }
                    }
                }
                restartButton.setTexture(winFace);
            }

            for (int row = 0; row < game_rows; row += 1) {
                for (int col = 0; col < game_cols; col += 1) {
                    window.draw(tiles[row][col].getTile());
                    if (game_over && tiles[row][col].getNumber() == -1 && !game_win) {
                        tiles[row][col].reveal();
                    }
                    if (tiles[row][col].getFlagged() || tiles[row][col].getClicked()) {window.draw(tiles[row][col].getFlag());}
                }
            }

            window.draw(c1);
            window.draw(c2);
            window.draw(c3);
            if (((int) game_m)-flag_count < 0) window.draw(cn);

            if (paused) {
                for (int row = 0; row < game_rows; row++) {
                    for (int col = 0; col < game_cols; col++) {
                        sf::Sprite tempTile(*textures["0"]);
                        tempTile.setPosition({col*32.0f, row*32.0f});
                        window.draw(tempTile);
                    }
                }
            }

            window.display();

            if (revealed_count == (game_cols*game_rows-game_m) && justWon) {
                std::vector<int> timeString = getDigits(time);
                leadBoard.addScore(name, std::to_string(timeString[0]) + std::to_string(timeString[1]) + ":" + std::to_string(timeString[2]) + std::to_string(timeString[3]));
                leadBoard.openWindow();
                justWon = false;
            }
        }
    }
    window.close();
}