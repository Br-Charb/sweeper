//
// Created by Ben Charbonneau on 11/24/25.
//

#ifndef SWEEPER_WELCOMEWINDOW_H
#define SWEEPER_WELCOMEWINDOW_H
#include <SFML/Graphics.hpp>


class welcomeWindow {
public:
    welcomeWindow(unsigned int h, unsigned int w);
    std::string getName();
    bool getClosed();
    void setText(sf::Text &text, float x, float y);
    void openWindow();
private:
    std::string name;
    bool closed;
    unsigned int welcome_w;
    unsigned int welcome_h;
};


#endif //SWEEPER_WELCOMEWINDOW_H