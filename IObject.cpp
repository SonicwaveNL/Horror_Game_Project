
#include "IObject.hpp"

void IObject::move(sf::Vector2f direction) {
  prevPosition = position;
  position = position + direction * speed;
}
