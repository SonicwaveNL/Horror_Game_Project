#include <gridCell.hpp>

void GridCell::moveIfPossible(sf::Vector2f direction) { return; }

void GridCell::move(sf::Vector2f direction) { return; }

bool GridCell::intersect(IObject & obj) {
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void GridCell::collision(IObject & obj) {
    // If gridcell collides with anything: do nothing
    return;
}

void GridCell::setType(std::string type) { type = type; }

sf::FloatRect GridCell::getBounds() { return iRect.getGlobalBounds(); }

void GridCell::setColor(sf::Color color) {
    iRect.setFillColor(color);
    iRect.setOutlineColor(color);
}

void GridCell::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    window.draw(sprite);
}
