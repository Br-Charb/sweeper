//
// Created by Ben Charbonneau on 11/30/25.
//

#include "leaderBoard.h"

std::vector<std::pair<std::string, std::string>> leaderBoard::readFile() {
    std::vector<std::pair<std::string, std::string>> nameScores;
    std::string line;
    std::ifstream scores(filePath);

    while (std::getline(scores, line)) {
        nameScores.push_back({line.substr(0, line.find(',')), line.substr(line.find(',')+2)});
    }
    return nameScores;
}

void leaderBoard::writeFile(std::vector<std::pair<std::string, std::string>> nameScores) {
    std::ofstream scores(filePath);
    scores << nameScores[0].first << ", " << nameScores[0].second << "\n";
    scores << nameScores[1].first << ", " << nameScores[1].second << "\n";
    scores << nameScores[2].first << ", " << nameScores[2].second << "\n";
    scores << nameScores[3].first << ", " << nameScores[3].second << "\n";
    scores << nameScores[4].first << ", " << nameScores[4].second;
}

leaderBoard::leaderBoard(int rows, int cols, std::string fp, bool jw) {
    height = rows*16 + 50;
    width = cols*16;
    closed = true;
    justWon = jw;
    filePath = fp;
    allScores = readFile();
    spot = 0;
}

bool leaderBoard::getClosed(){return closed;}

long long timeToInt(std::string t) {
    return (t[0] - '0')*(600) + (t[1] - '0')*(60) + (t[3] - '0')*(10) + (t[4] - '0');
}

void leaderBoard::addScore(std::string name, std::string t) {
    spot = 0;
    long long time = timeToInt(t);
    for (int i = 0; i < allScores.size(); i++) {
        if (timeToInt(allScores[i].first) < time) {
            spot += 1;
        }
    }
    for (int i = 4; spot < i; i--) {
        allScores[i].first = allScores[i-1].first;
        allScores[i].second = allScores[i-1].second;
    }
    if (spot < 5) {
        allScores[spot].first = t;
        allScores[spot].second = name;
    }
    writeFile(allScores);
}

void leaderBoard::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x/2.0f,
    textRect.position.y + textRect.size.y/2.0f});
    text.setPosition(sf::Vector2f(x, y));
}

void leaderBoard::setJustWon(bool jw) {
    justWon = jw;
}

void leaderBoard::openWindow() {
    closed = false;
    sf::RenderWindow window(sf::VideoMode({width, height}), "Minesweeper", sf::Style::Close);
    sf::Font font("files/font.ttf");

    std::string scoreBoard = "";
    for (int i = 0; i < allScores.size(); i++) {
        std::string cur = "";
        if (spot == i and justWon) cur = "*";
        scoreBoard += std::to_string(i+1) + ".\t" + allScores[i].first + "\t" + allScores[i].second + cur + "\n\n";
    }

    // welcome to minesweeper
    sf::Text welcome(font);
    welcome.setString("LEADERBOARD");
    welcome.setCharacterSize(20);
    welcome.setFillColor(sf::Color::White);
    welcome.setStyle(sf::Text::Bold);
    welcome.setStyle(sf::Text::Underlined);
    setText(welcome, width/2, (height/2)-120);

    // enter your name
    sf::Text records(font);
    records.setString(scoreBoard);
    records.setCharacterSize(18);
    records.setFillColor(sf::Color::White);
    records.setStyle(sf::Text::Bold);
    setText(records, width/2, (height/2)+20);

    while(window.isOpen()) {
        while(const auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                closed = true;
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(welcome);
        window.draw(records);
        window.display();
    }
}

