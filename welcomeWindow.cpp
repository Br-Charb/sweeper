//
// Created by Ben Charbonneau on 11/24/25.
//

#include "welcomeWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>


welcomeWindow::welcomeWindow(unsigned int h, unsigned int w) {
    name = "";
    closed = false;
    welcome_w = w*32;
    welcome_h = h*32+100;
    mode = "load";
}

std::string welcomeWindow::getName() {
    return name;
}

bool welcomeWindow::getClosed() {
    return closed;
}

void welcomeWindow::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x/2.0f,
    textRect.position.y + textRect.size.y/2.0f});
    text.setPosition(sf::Vector2f(x, y));
}

std::string welcomeWindow::getMode() {
    return mode;
}

void welcomeWindow::openWindow() {
    closed = false;
    sf::RenderWindow window(sf::VideoMode({welcome_w, welcome_h}), "Minesweeper", sf::Style::Close);
    sf::Font font("files/font.ttf");

    // welcome to minesweeper
    sf::Text welcome(font);
    welcome.setString("WELCOME TO MINESWEEPER!");
    welcome.setCharacterSize(24);
    welcome.setFillColor(sf::Color::White);
    welcome.setStyle(sf::Text::Bold);
    welcome.setStyle(sf::Text::Underlined);
    setText(welcome, welcome_w/2, (welcome_h/2)-150);

    // enter your name
    sf::Text enter(font);
    enter.setString("Enter your name:");
    enter.setCharacterSize(20);
    enter.setFillColor(sf::Color::White);
    enter.setStyle(sf::Text::Bold);
    setText(enter, welcome_w/2, (welcome_h/2)-75);

    // name input
    sf::Text name_input(font);
    name_input.setString(name + "|");
    name_input.setCharacterSize(18);
    name_input.setFillColor(sf::Color::Yellow);
    name_input.setStyle(sf::Text::Bold);
    setText(name_input, welcome_w/2, (welcome_h/2)-45);

    //Extra credit: difficulty buttons
    sf::Text easy(font);
    easy.setString("Easy Mode");
    easy.setCharacterSize(20);
    easy.setFillColor(sf::Color::White);
    easy.setStyle(sf::Text::Bold);
    setText(easy, welcome_w/4, (welcome_h*3/4) - 100);

    sf::Text hard(font);
    hard.setString("Hard Mode");
    hard.setCharacterSize(20);
    hard.setFillColor(sf::Color::White);
    hard.setStyle(sf::Text::Bold);
    setText(hard, welcome_w/2, (welcome_h*3/4) - 102);

    sf::Text load(font);
    load.setString("Load Setup");
    load.setCharacterSize(20);
    load.setFillColor(sf::Color::White);
    load.setStyle(sf::Text::Bold);
    setText(load, 3*welcome_w/4, (welcome_h*3/4) - 100);

    sf::Texture easyIcon("files/images/face_happy.png", false, sf::IntRect({0, 0}, {64, 64}));
    sf::Texture hardIcon("files/images/face_lose.png", false, sf::IntRect({0, 0}, {64, 64}));
    sf::Texture loadIcon("files/images/face_win.png", false, sf::IntRect({0, 0}, {64, 64}));

    sf::Sprite easyButton(easyIcon);
    easyButton.setPosition({welcome_w/4.0f - 32, ((welcome_h*3)/4.0f) - 80});

    sf::Sprite hardButton(hardIcon);
    hardButton.setPosition({(welcome_w)/2.0f - 32, ((welcome_h*3)/4.0f) - 80});

    sf::Sprite loadButton(loadIcon);
    loadButton.setPosition({(3*welcome_w)/4.0f - 32, ((welcome_h*3)/4.0f) - 80});



    while(window.isOpen()) {
        while(const auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>() || closed) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                char c = static_cast<char>(keyPressed->unicode);
                if (c == 8) {
                    if (!(name.empty())) {
                        name.pop_back();
                        name_input.setString(name + "|");                    }
                } else if (std::isalpha(c) && name.length() < 10) {
                    if (!(name.empty())) {
                        name += std::tolower(c);
                    } else {
                        name += std::toupper(c);
                    }
                    name_input.setString(name + "|");
                } else if (c == 10 && !(name.empty())) {
                    closed = true;
                }
                setText(name_input, welcome_w/2, (welcome_h/2)-45);
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!(name.empty()))) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (easyButton.getGlobalBounds().contains(sf::Vector2f(mousePos))){
                        closed = true;
                        mode = "easy";
                    }
                    if (hardButton.getGlobalBounds().contains(sf::Vector2f(mousePos))){
                        closed = true;
                        mode = "hard";
                    }
                    if (loadButton.getGlobalBounds().contains(sf::Vector2f(mousePos))){
                        closed = true;
                    }
                }
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(welcome);
        window.draw(enter);
        window.draw(name_input);
        window.draw(easy);
        window.draw(hard);
        window.draw(load);
        window.draw(easyButton);
        window.draw(hardButton);
        window.draw(loadButton);
        window.display();
    }
}
