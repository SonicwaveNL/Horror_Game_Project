#include <iostream>
#include <../Headers/Monster.hpp>
void Monster::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;

    iRect.setPosition(position);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

bool Monster::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Monster::setPosition(sf::Vector2f target) {
    prevPosition = position;
    position = target;
    iRect.setPosition(position);
}

void Monster::collision(IObject & obj) {
    if (std::static_pointer_cast<Player>(object) != nullptr) {
        std::cout << "Monster attacked player" << std::endl;
        return;
    }
}

void Monster::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Monster::getBounds() { return iRect.getGlobalBounds(); }