#include "player.hpp"

void Player::move( sf::Vector2f direction ){
    position = position + direction * speed;
}

bool Player::isColliding( IObject & obj ){
    auto playerBounds = sprite.getBounds();
    auto targetBounds = obj.getBounds();
}

void Player::jump( sf::Vector2f target ){
    position = target;
}

void Player::interact( IObject & obj ){
}

void Player::draw( sf::RenderWindow & window ){
    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

sf::FloatRect Player::getBounds(){ return sprite.getGlobalBounds(); }