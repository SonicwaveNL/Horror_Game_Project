#include <switch.hpp>

void Switch::move(sf::Vector2f direction){
    return;
}

void Switch::moveIfPossible(sf::Vector2f direction){
    return;
}

bool Switch::intersect(IObject & obj){
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Switch::setPosition(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    iRect.setPosition(iRect.getPosition());
}

void Switch::setColor(sf::Color color){
    color = color;
}

void Switch::draw(sf::RenderWindow & window){
    window.draw(iRect); 
}

void Switch::collision(IObject & obj){ 
    if(!intersect(obj)){
        return;
    }

    // If the player interacts with the switch, turn it ON
    if(obj.getType() == objectType::Player){
        active = true;
    }
}

sf::FloatRect Switch::getBounds(){
    return iRect.getGlobalBounds();
}

bool Switch::isActive(){
    return active;
}

sf::Vector2f Switch::getPosition(){
    return iRect.getPosition();
}
