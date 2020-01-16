
#include "IObject.hpp"

void IObject::move(sf::Vector2f direction) {
  prevPosition = position;
  position = position + direction * speed;
  base.setPosition(position);
}


std::string IObject::getType(){
  return type;
}