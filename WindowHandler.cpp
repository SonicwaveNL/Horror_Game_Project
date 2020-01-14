#include "WindowHandler.hpp"

void WindowHandler::draw(std::vector<IObject*> & objects){
    window.clear();
    for(IObject* obj : objects){
        obj->draw(window);
    }
}