#include <switch.hpp>

void Switch::move(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    sf::Vector2f position = iRect.getPosition() + direction * speed;

    iRect.setPosition(position);
}

void Switch::moveIfPossible(sf::Vector2f direction){
    move(direction);
    for (std::shared_ptr<IObject> obj : objects) {
        if (obj->intersect(*this)) {
            collision(*obj);
        }
    }
}

bool Switch::intersect(IObject & obj){
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

void Switch::setPosition(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    iRect.setPosition(iRect.getPosition());
}

void Switch::setColor(sf::Color color){
    color = color;
}

void Switch::draw(sf::RenderWindow & window){
    window.draw(iRect); 
}

void Switch::collision(IObject & obj){
    std::shared_ptr<IObject> object = std::make_shared<IObject>(obj);

    // If the player interacts with the switch, 'switch' the on-state
    if(std::static_pointer_cast<Player>(object) != nullptr){
        active = !active;
    }

    // Set position to previous position if switch collides with an object
    iRect.setPosition(prevPosition);
}

sf::FloatRect Switch::getBounds(){
    return iRect.getGlobalBounds();
}

bool Switch::isActive(){
    return active;
}