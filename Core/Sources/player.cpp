#include <iostream>
#include <../Headers/player.hpp>

void Player::moveIfPossible(sf::Vector2f direction) {
    if (direction.x < 0) {
        sprite.setScale(-1, 1);
        sprite.setOrigin({getBounds().width, 0});
    } else if (direction.x > 0) {
        sprite.setOrigin({0, 0});
        sprite.setScale(1, 1);
    }
    // if I can't move, keep moving with speed 1 until I hit the wall
    move(direction);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            fixMove(*obj, direction);
            collision(*obj);
        }
    }
}

void Player::move(sf::Vector2f direction) {
    prevPosition = getPosition();
    setPosition(getPosition() + direction * speed);
}

bool Player::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Player::setPosition(sf::Vector2f position) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(position);
    sprite.setPosition(position);
}

sf::Vector2f Player ::getPosition() { return iRect.getPosition(); }

void Player::fixMove(IObject & obj, sf::Vector2f oldDir) {
    if(obj.getType() == objectType::Wall){
    auto oldSpeed = speed;
    speed = 1.0;
    while (intersect(obj)) {
        move(-oldDir);
    }
    move(-oldDir);
    speed = oldSpeed;
    }
}

void Player::collision(IObject & obj) {

    switch (obj.getType()) {
        case objectType::Wall: {
            setPosition(prevPosition);
            break;
        }

        case objectType::Door: {
            Door * d = dynamic_cast<Door *>(&obj);
            if (d->getOpenState()) {
                setPosition(prevPosition);
                win = true;
            }
            break;
        }

        case objectType::Monster: {
            lose = true;
            break;
        }
    }
}

void Player::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() { return iRect.getGlobalBounds(); }

bool Player::checkWin() { return win; }
bool Player::checkLose() { return lose; }

void Player::reset() {
    win = false;
    lose = false;
}