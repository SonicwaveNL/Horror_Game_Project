#include <iRectangle.hpp>

void IRectangle::setSize(sf::Vector2f size) { iRect.setSize(size); }

void IRectangle::setColor(sf::Color color){
    iRect.setFillColor(color);
}


sf::Vector2f IRectangle::getPosition(){
    return iRect.getPosition();
}