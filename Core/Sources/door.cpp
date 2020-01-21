#include <../Headers/door.hpp>

void Door::moveIfPossible(sf::Vector2f direction) {
    return;
}

bool Door::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Door::setPosition(sf::Vector2f target) {
    return;
}

void Door::collision(IObject & obj) {
    return;
}

void Door::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Door::getBounds() { return iRect.getGlobalBounds(); }

sf::Vector2f Door::getPosition(){
    return iRect.getPosition();
}