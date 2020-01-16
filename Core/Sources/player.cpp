#include "player.hpp"

void Player::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;
    base.setPosition(position);
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
    base.setPosition(position);

}

void Player::collision(IObject & obj) {
    if (dynamic_cast<Wall *>(obj) != nullptr) {
        position = prevPosition;
        base.setPosition(position);

        return;
    }

    if (dynamic_cast<Door *>(obj) != nullptr) {
        std::cout << "You won the game!" << std::endl;
        position = prevPosition;
        base.setPosition(position);
        
        return;
    }
}

void Player::draw(sf::RenderWindow & window) {
    window.draw(base);
}

sf::FloatRect Player::getBounds() { return base.getGlobalBounds(); }