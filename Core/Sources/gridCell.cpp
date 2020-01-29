#include <gridCell.hpp>

void GridCell::moveIfPossible(sf::Vector2f direction) { return; }

void GridCell::move(sf::Vector2f direction) { return; }

bool GridCell::intersect(IObject& obj) {
  return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void GridCell::collision(IObject& obj) {
  // If gridcell collides with anything: do nothing
  return;
}

void GridCell::setPosition(sf::Vector2f position) {
  iRect.setPosition(position);
}

sf::Vector2f GridCell::getPosition() { return iRect.getPosition(); }

void GridCell::setCellType(objectType type) {
  if (type == objectType::Floor) {
    setColor(sf::Color::White);
  } else if (type == objectType::Wall) {
    setColor(sf::Color::Red);
  } else if (type == objectType::Switch) {
    setColor(sf::Color::Green);
  } else if (type == objectType::Door) {
    setColor(sf::Color::Magenta);
  } else if (type == objectType::Player) {
    setColor(sf::Color::Yellow);
  } else if (type == objectType::Monster) {
    setColor(sf::Color::Blue);
  }
  cellType = type;
}

void GridCell::setCellType(objectType type, sf::Texture* texture) {
  if (type == objectType::Floor) {
    setColor(sf::Color::Transparent);
    setTexture(texture);
  } else if (type == objectType::Wall) {
    setColor(sf::Color::Red);
    setTexture(texture);
  } else if (type == objectType::Switch) {
    setColor(sf::Color::Green);
    setTexture(texture);
  } else if (type == objectType::Door) {
    setColor(sf::Color::Magenta);
    setTexture(texture);
  } else if (type == objectType::Player) {
    setColor(sf::Color::Transparent);
    setTexture(texture);
  } else if (type == objectType::Monster) {
    setColor(sf::Color::Transparent);
    setTexture(texture);
  }
  cellType = type;
}

objectType GridCell::getCellType() { return cellType; }

sf::FloatRect GridCell::getBounds() { return iRect.getGlobalBounds(); }

void GridCell::setTexture(sf::Texture* _texture) {
  texture = _texture;
  sprite.setTexture(*texture);
}

bool GridCell::isWalkable() { return cellType != objectType::Wall; }

void GridCell::draw(sf::RenderWindow& window) {
  window.draw(iRect);
  if (cellType != objectType::Floor) {
    window.draw(sprite);
  }
}

std::shared_ptr<IObject> GridCell::getMyDrawable(){
    return myDrawable;
}

void GridCell::setMyDrawable(std::shared_ptr<IObject> iPointer){
    myDrawable = iPointer;
}
