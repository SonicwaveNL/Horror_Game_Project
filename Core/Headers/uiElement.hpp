#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include<SFML/Graphics.hpp>
#include <string>

#include <support.hpp>

class UIElement {
  private:
    sf::Text label;
    sf::RectangleShape iRect;
    sf::Font font;
    sf::Color labelColor;
    sf::Color borderColor;
    sf::Color fontColor;

  public:
    ///\brief
    ///UIElement constructor.
    UIElement(sf::Vector2f position,
              std::string labelText = "Placeholder",
              sf::Color labelColor = sf::Color::Cyan,
              sf::Color fontColor = sf::Color::Blue,
              sf::Color borderColor = sf::Color::Magenta,
              sf::Vector2f size = sf::Vector2f(500.f, 120.f),
              objectType type = objectType::UIElement, float speed = 0)
        : labelColor(labelColor), borderColor(borderColor),
          fontColor(fontColor) {
        iRect.setPosition(position);
        iRect.setFillColor(labelColor);
        iRect.setSize(size);
        font.loadFromFile("Resources/Arial.ttf");
        label.setFont(font);
        label.setFillColor(fontColor);
        setText(labelText);
        setLabelPosition();
    }

    ///\brief
    /// Whether or not the user intersects with its parameter.
    ///@param obj
    /*The object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(sf::Vector2f position);

    ///\brief
    /// Set the position of the switch to the target.
    ///@param target
    /*sf::Vector2f containing the new position of the object.*/
    void setPosition(sf::Vector2f target) ;

    ///\brief
    ///Sets the position of the label relative to the sf::RectangleShape. 
    void setLabelPosition();

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*The window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) ;

    ///\brief
    /// Returns the outer boundaries of the switch object
    ///@return sf::FloatRect
    sf::FloatRect getBounds() ;

    ///\brief
    /// Function to get the position.
    sf::Vector2f getPosition();

    ///\brief
    ///Sets the sf::RectangleShape\'s border color.
    void setBorderColor(sf::Color color);

    ///\brief
    ///Sets the text of the label.
    void setText(std::string text);

    ///\brief
    ///Gets the text from the label.
    std::string getText();
};

#endif