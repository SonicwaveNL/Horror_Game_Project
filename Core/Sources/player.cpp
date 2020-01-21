    #include <iostream>
#include <../Headers/player.hpp>

void Player::moveIfPossible(sf::Vector2f direction) {
    // sf::Vector2f position = iRect.getPosition() + direction * speed;

    // iRect.setPosition(position);
    move(iRect.getPosition() + direction * speed);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

void Player::move(sf::Vector2f position) {
        prevPosition = iRect.getPosition();

    iRect.setPosition(position);
}

void Player::setColor(sf::Color color){
    iRect.setFillColor( color );
    iRect.setOutlineColor( color );
}

bool Player::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Player::setPosition(sf::Vector2f target) {
    prevPosition = iRect.getPosition();
    iRect.setPosition(target);
}

void Player::collision(IObject & obj) {
    
    switch(obj.getType()){
        case IObject::Type::Wall:{
            iRect.setPosition(prevPosition);
        break;
        }

        case IObject::Type::Door:{
            Door * d = dynamic_cast<Door*>(&obj);
            if(d->getOpenState()){
                std::cout << "You won the game!" << std::endl;
                iRect.setPosition(prevPosition);
                win = true;
            }
        break;
        }

    }
}

void Player::draw(sf::RenderWindow & window) { window.draw(iRect); }

sf::FloatRect Player::getBounds() { return iRect.getGlobalBounds(); }

bool Player::checkWin() { return win; }
