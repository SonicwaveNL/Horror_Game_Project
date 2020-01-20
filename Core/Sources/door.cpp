#include <../Headers/door.hpp>

void Door::moveIfPossible(sf::Vector2f direction) {
    prevPosition = iRect.getPosition();
    sf::Vector2f position = iRect.getPosition() + direction * speed;

    iRect.setPosition(position);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

bool Door::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Door::setPosition(sf::Vector2f target) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(position);
}

void Door::collision(IObject & obj) {
    iRect.setPosition(prevPosition);
}

void Door::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Door::getBounds() { return iRect.getGlobalBounds(); }