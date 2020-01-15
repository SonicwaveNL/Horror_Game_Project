#include "player.hpp"

void Player::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;

    for (IObject * obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

bool Player::intersect(IObject & obj) {
    return base.getGlobalBounds().intersects(obj.getBounds());
}

void Player::jump(sf::Vector2f target) {
    prevPosition = position;
    position = target;
}

void Player::collision(IObject & obj) {
    if (dynamic_cast<Wall *>(obj) != nullptr) {
        position = prevPosition;
        return;
    }

    if (dynamic_cast<Door *>(obj) != nullptr) {
        std::cout << "You won the game!" << std::endl;
        position = prevPosition;
        return;
    }
}

void Player::draw(sf::RenderWindow & window) {
    base.setPosition(position);
    window.draw(base);
}

sf::FloatRect Player::getBounds() { return base.getGlobalBounds(); }