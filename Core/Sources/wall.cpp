#include <../Headers/wall.hpp>

void Wall::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;
    base.setPosition(position);

    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

void Wall::jump(sf::Vector2f target) {
    prevPosition = position;
    position = target;
    base.setPosition(position);
}

bool Wall::intersect(IObject & obj) {
    return base.getGlobalBounds().intersects(obj.getBounds());
}

void Wall::collision(IObject & obj) {
    position = prevPosition;
    base.setPosition(position);
}

void Wall::draw(sf::RenderWindow & window) { window.draw(base); }

sf::FloatRect Wall::getBounds() { return base.getGlobalBounds(); }
