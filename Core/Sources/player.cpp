#include "../Headers/player.hpp"
#include <iostream>
void Player::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;

    base.setPosition(position);
    for (std::shared_ptr<IObject> obj : objects) {
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
    if (obj.getType() == "Wall") {
        position = prevPosition;
        base.setPosition(position);

        return;
    }

    if (obj.getType() == "Door") {
        std::cout << "You won the game!" << std::endl;
        position = prevPosition;
        base.setPosition(position);
        win = true;
        return;
    }
}

void Player::draw(sf::RenderWindow & window) {
    window.draw(base);
}

sf::FloatRect Player::getBounds() { return base.getGlobalBounds(); }

bool Player::checkWin(){
    return win;
}
