#include "door.hpp"

void Door::moveIfPossible(sf::Vector2f direction) {
  prevPosition = position;
  position = position + direction * speed;
  base.setPosition(position);

  for (std::shared_ptr<IObject> obj : objects) {
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
  base.setPosition(position);
}

void Door::collision(IObject& obj) {
  position = prevPosition;
  base.setPosition(position);
}

void Door::draw(sf::RenderWindow& window) {
  window.draw(base);
}

sf::FloatRect Door::getBounds() {
  return base.getGlobalBounds();
}