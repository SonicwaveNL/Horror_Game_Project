#include <../Headers/iObject.hpp>

objectType IObject::getType() { return type; }

void IObject::setSpeed(float newSpeed) { speed = newSpeed; }

float IObject::getSpeed(){return speed;}