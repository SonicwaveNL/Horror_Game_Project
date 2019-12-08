#include "wall.hpp"

void Wall::moveIfPossible(sf::Vector2f direction) override {
    prevPosition = position;

    position = position + direction * speed;
    for (IObject * obj : objects) {
        if (obj->intersect(this)) {
            collision(obj);
        }
    }
}

void Wall::jump(sf::Vector2f target) override {
    prev_position = position;
    position = target;
}

bool Wall::intersect(IObject & obj) override {
    return base.getGlobalBounds().intersects(obj.getBounds());
}

void Wall::collision(IObject & obj) override {
    position = prevPosition;
}

void Wall::draw(sf::RenderWindow & window) override {
    base.setPosition(position);
    window.draw(base);
}

sf::FloatRect Wall::getBounds() override { return base.getGlobalBounds(); }
