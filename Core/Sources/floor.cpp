#include <../Headers/floor.hpp>

void Floor::moveIfPossible(sf::Vector2f direction) { return; }

void Floor::move(sf::Vector2f position) { return; }

void Floor::setPosition(sf::Vector2f target) { return; }

bool Floor::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Floor::collision(IObject & obj) { return; }

void Floor::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    window.draw(sprite);
}

sf::FloatRect Floor::getBounds() { return iRect.getGlobalBounds(); }

sf::Vector2f Floor::getPosition() { return iRect.getPosition(); }
