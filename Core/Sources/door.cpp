#include "door.hpp"

void Door::moveIfPossible(sf::Vector2f direction) {
  prevPosition = position;
  position = position + direction * speed;

  for (IObject* obj : objects) {
    if (obj->intersect(*this)) {
      collision(*obj);
    }
  }
}

bool Door::intersect(IObject& obj) {
  return base.getGlobalBounds().intersects(obj.getBounds());
}

void Door::jump(sf::Vector2f target) {
  prevPosition = position;
  position = target;
}

void Door::collision(IObject& obj) {
  position = prevPosition;
}

void Door::draw(sf::RenderWindow& window) {
  base.setPosition(position);
  window.draw(base);
}

sf::FloatRect Door::getBounds() {
  return base.getGlobalBounds();
}