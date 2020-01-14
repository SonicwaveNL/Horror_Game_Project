#include "wall.hpp"
//Todo - sprite has to become a rectngle
//update sfml path to sfml-master
//IObject sprite to rectangle
//IObject interact to void
//interact to the interact like we used here
void Wall::move(sf::Vector2f direction) override {
    position = position + direction * speed;
}

void Wall::jump(sf::Vector2f target) override { position = target; }

bool Wall::isColliding(IObject & obj) override {
    return sprite.getGlobalBounds().intersects(obj.getBounds());
}

// calls isColliding and does something if the user presses the interact button
void interact(IObject & obj) override { 
    if(isColliding(obj) == false){
        return;
    }

    return 
    }

void Wall::draw(sf::RenderWindow & window) override {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

sf::FloatRect Wall::getBounds() override { return sprite.getGlobalBounds(); }
