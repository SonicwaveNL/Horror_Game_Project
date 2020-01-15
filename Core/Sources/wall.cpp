#include "wall.hpp"

void Wall::moveIfPossible(sf::Vector2f direction)  {
    prevPosition = position;

    position = position + direction * speed;
    for (IObject * obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

void Wall::jump(sf::Vector2f target) {
    prevPosition = position;
    position = target;
}

bool Wall::intersect(IObject & obj)  {
    return base.getGlobalBounds().intersects(obj.getBounds());
}

void Wall::collision(IObject & obj)  {
    position = prevPosition;
}

void Wall::draw(sf::RenderWindow & window)  {
    base.setPosition(position);
    window.draw(base);
}

sf::FloatRect Wall::getBounds()  { return base.getGlobalBounds(); }
