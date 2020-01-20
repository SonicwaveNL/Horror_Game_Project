#include <iostream>
#include <../Headers/player.hpp>
void Player::moveIfPossible(sf::Vector2f direction) {
    prevPosition = position;
    position = position + direction * speed;

    iCirc.setPosition(position);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

bool Player::intersect(IObject & obj) {
    return iCirc.getGlobalBounds().intersects(obj.getBounds());
}

void Player::jump(sf::Vector2f target) {
    prevPosition = position;
    position = target;
    iCirc.setPosition(position);
}

void Player::collision(IObject & obj) {
    std::shared_ptr<IObject> object = std::make_shared<IObject>(obj);
    //        player = std::static_pointer_cast<Player>(drawables[0]);
    // If the pointer cast returns a nullptr, it failed.
    if(std::static_pointer_cast<Wall>(object) != nullptr){
        ICirc.setPosition(prevPosition);
        return;
    }


    if(std::static_pointer_cast<Door>(object) != nullptr){
        std::cout << "You won the game!" << std::endl;
    }

    if (obj.getType() == "Door") {
        std::cout << "You won the game!" << std::endl;
        position = prevPosition;
        iCirc.setPosition(position);
        win = true;
        return;
    }
}

void Player::draw(sf::RenderWindow & window) { window.draw(iCirc); }

sf::FloatRect Player::getBounds() { return iCirc.getGlobalBounds(); }

bool Player::checkWin() { return win; }
