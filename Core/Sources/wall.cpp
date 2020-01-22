#include <../Headers/wall.hpp>

void Wall::moveIfPossible(sf::Vector2f direction) { return; }

void Wall::move(sf::Vector2f position) { return; }



void Wall::setPosition(sf::Vector2f target) { return; }

bool Wall::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Wall::collision(IObject & obj) { return; }

void Wall::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Wall::getBounds() { return iRect.getGlobalBounds(); }

sf::Vector2f Wall::getPosition(){
    return iRect.getPosition();
}
