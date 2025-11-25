//
// Created by Ben Charbonneau on 11/24/25.
//

#include "welcomeWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>


welcomeWindow::welcomeWindow(unsigned int w, unsigned int h) {
    std::cout<<"Welcome Window"<<std::endl;
    name = "";
    closed = false;
    welcome_w = w*32;
    welcome_h = h*32+100;
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
                } else if (std::isalpha(c) && name.length() < 11) {
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
        }

        window.clear(sf::Color::Blue);
        window.draw(welcome);
        window.draw(enter);
        window.draw(name_input);
        window.display();
    }
}
