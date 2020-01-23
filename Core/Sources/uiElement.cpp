#include <uiElement.hpp>

void UIElement::move(sf::Vector2f direction){
    return;
}

void UIElement::moveIfPossible(sf::Vector2f direction){
    return;
}

bool UIElement::intersect(IObject & obj){
    return iRect.getGlobalBounds().intersects(obj.getBounds());
}

bool UIElement::intersect(sf::Vector2f position){
    return iRect.getGlobalBounds().contains(position);
}

void UIElement::setPosition(sf::Vector2f direction){
    prevPosition = iRect.getPosition();
    iRect.setPosition(iRect.getPosition());
    setLabelPosition();
}

void UIElement::setLabelPosition(){
    auto rectBounds = iRect.getGlobalBounds();
    auto textBounds = label.getGlobalBounds();
    label.setPosition(
        rectBounds.left + (rectBounds.width /2) - (textBounds.width/2),
        rectBounds.top + (rectBounds.height/2) - (textBounds.height/2)
    );
}

void UIElement::draw(sf::RenderWindow & window){
    window.draw(iRect); 
    window.draw(label);
}

void UIElement::collision(IObject & obj){ 
    if(!intersect(obj)){
        return;
    }
}

sf::FloatRect UIElement::getBounds(){
    return iRect.getGlobalBounds();
}

sf::Vector2f UIElement::getPosition(){
    return iRect.getPosition();
}

void UIElement::setBorderColor(sf::Color color){
    iRect.setOutlineColor(color);
}

void UIElement::setText(std::string text){
    label.setString(text);
}