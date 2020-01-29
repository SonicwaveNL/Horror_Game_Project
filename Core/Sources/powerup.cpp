#include <../Headers/Powerup.hpp>

void Powerup::buff(BuffType type, int magnitude = 0){
    return;
}

void Powerup::move(sf::Vector2f direction){
    return;
}

void Powerup::moveIfPossible(sf::Vector2f direction){
    return;
}

bool Powerup::intersect(IObject & obj){
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Powerup::setPosition(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    iRect.setPosition(iRect.getPosition());
}


void Powerup::draw(sf::RenderWindow & window){
    window.draw(iRect); 
    window.draw(sprite);
}

void Powerup::collision(IObject & obj){ 
    return;
}

sf::FloatRect Powerup::getBounds(){
    return iRect.getGlobalBounds();
}