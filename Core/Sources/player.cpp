#include <iostream>
#include <../Headers/player.hpp>

void Player::moveIfPossible(sf::Vector2f direction) {
    if(direction.x < 0){
        sprite.setScale(-1, 1);
        sprite.setOrigin({getBounds().width, 0});
    }else if(direction.x > 0){
        sprite.setOrigin({0,0});
        sprite.setScale(1,1);
    }
    move(direction);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

void Player::move(sf::Vector2f direction) {
    prevPosition = iRect.getPosition();
    setPosition(iRect.getPosition() + direction * speed);
}



bool Player::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Player::setPosition(sf::Vector2f target) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(target);
    sprite.setPosition(target);
}

sf::Vector2f Player :: getPosition(){
    return iRect.getPosition();
}

void Player::collision(IObject & obj) {
    
    switch(obj.getType()){
        case objectType::Wall:{
            setPosition(prevPosition);
            break;
        }

        case objectType::Door:{
            Door * d = dynamic_cast<Door*>(&obj);
            if(d->getOpenState()){
                setPosition(prevPosition);
                win = true;
            }
        break;
        }


        case objectType::Monster:{
            lose=true;
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
bool Player::checkLose(){return lose;}

void Player::reset(){win=false;lose=false;}