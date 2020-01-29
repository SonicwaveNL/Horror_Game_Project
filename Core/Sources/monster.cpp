#include <math.h>
#include <../Headers/monster.hpp>
#include <iostream>
void Monster::moveIfPossible(sf::Vector2f direction) {
    oldDirection = direction;
     if(direction.x < 0){
        sprite.setScale(-1, 1);
        sprite.setOrigin({getBounds().width, 0});
    }else if(direction.x > 0){
        sprite.setOrigin({0,0});
        sprite.setScale(1,1);
    }
    prevPosition = getPosition();
    setPosition(getPosition() + direction * speed);
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
    prevPosition = iRect.getPosition();
    iRect.setPosition(target);
    sprite.setPosition(target);
}

void Monster::collision(IObject & obj) {
    if (obj.getType() == objectType::Player) {
        obj.collision(*this);
        return;
    }
}

void Monster::move(sf::Vector2f position) {
    prevPosition = iRect.getPosition();
    setPosition(position);
}

void Monster::moveOld() {
    setPosition(iRect.getPosition() + oldDirection * speed);
}

void Monster::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    window.draw(sprite);
}

sf::FloatRect Monster::getBounds() { return iRect.getGlobalBounds(); }

sf::Vector2f Monster::getPosition() { return iRect.getPosition(); }