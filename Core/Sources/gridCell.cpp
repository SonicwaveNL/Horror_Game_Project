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

void GridCell::setPosition(sf::Vector2f position){
    iRect.setPosition( position );
}

sf::Vector2f GridCell::getPosition(){
    return iRect.getPosition();
}

void GridCell::setCellType(std::string type) { 
    if(type == "Floor"){
        setColor(sf::Color::White);
    }else if(type == "Wall"){
        setColor(sf::Color::Red);
    }else if(type == "Switch"){
        setColor(sf::Color::Green);
    }else if(type == "Door"){
        setColor(sf::Color::Yellow);
    }else if(type == "Player"){
        setColor(sf::Color::Green);
    }else if(type == "Enemy"){
        setColor(sf::Color::Blue);
    }    
    type = type;
}

std::string GridCell::getCellType(){
    return cellType;
}

sf::FloatRect GridCell::getBounds() { return iRect.getGlobalBounds(); }

void GridCell::setColor(sf::Color color) {
    iRect.setFillColor(color);
    iRect.setOutlineColor(color);
}

void GridCell::draw(sf::RenderWindow & window) {
    window.draw(iRect);
    // window.draw(sprite);
}
