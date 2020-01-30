#include <uiElement.hpp>

bool UIElement::intersect(sf::Vector2f position){
    return iRect.getGlobalBounds().contains(position);
}

void UIElement::setPosition(sf::Vector2f position){
    iRect.setPosition(position);
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

std::string UIElement::getText(){
    return label.getString();
};

void UIElement::setTextSize(int size){
    label.setCharacterSize((unsigned)size);
}

void UIElement::setFont(sf::Font* _font){
    font = *_font;
    label.setFont(*_font);
}

    void UIElement::setItalic(){
        label.setStyle(sf::Text::Italic);
    }
