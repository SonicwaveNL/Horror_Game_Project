#include <../Headers/wall.hpp>

void Wall::moveIfPossible(sf::Vector2f direction) {
    prevPosition = iRect.getPosition();
    sf::Vector2f position = iRect.getPosition() + direction * speed;

    iRect.setPosition(position);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

void Wall::setPosition(sf::Vector2f target) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(target);
}

bool Wall::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Wall::collision(IObject & obj) {
    iRect.setPosition(prevPosition);
}

void Wall::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Wall::getBounds() { return iRect.getGlobalBounds(); }
