#include <../Headers/door.hpp>

void Door::moveIfPossible(sf::Vector2f direction) {
    return;
}
void Door::setColor(sf::Color color){
    color = color;
}

void Door::move(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    sf::Vector2f position = iRect.getPosition() + direction * speed;

    iRect.setPosition(position);
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