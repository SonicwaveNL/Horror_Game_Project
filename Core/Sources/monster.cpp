#include <math.h>
#include <../Headers/monster.hpp>
#include <iostream>
void Monster::moveIfPossible(sf::Vector2f direction) {
  prevPosition = iRect.getPosition();
  
  
  oldDirection = direction;
  iRect.setPosition(iRect.getPosition() + direction * speed);
  for (std::shared_ptr<IObject> obj : objects) {
    if (obj->intersect(*this)) {
      collision(*obj);
    }
  }
}

bool Monster::intersect(IObject& obj) {
  return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Monster::setPosition(sf::Vector2f target) {
  prevPosition = iRect.getPosition();
  // position = target;
  iRect.setPosition(target);
}

void Monster::collision(IObject& obj) {
  if (obj.getType() == objectType::Player) {
    std::cout << "Monster attacked player" << std::endl;
    // position = prevPosition;
    // iRect.setPosition(position);
    // win = False;
    return;
  }
}

void Monster::moveOld(){
  iRect.setPosition(iRect.getPosition() + oldDirection * speed);
}

void Monster::move(sf::Vector2f position) {
  prevPosition = iRect.getPosition();
  iRect.setPosition(position);
}

void Monster::draw(sf::RenderWindow& window) { window.draw(iRect); }

sf::FloatRect Monster::getBounds() { return iRect.getGlobalBounds(); }

sf::Vector2f Monster::getPosition() { return iRect.getPosition(); }