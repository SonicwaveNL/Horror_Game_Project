#include "WindowHandler.hpp"

void WindowHandler::draw(sf::RenderWindow & window, std::vector<object*> & objects){
    window.clear();
    for(object* obj : objects){
        obj.draw(window);
    }
}