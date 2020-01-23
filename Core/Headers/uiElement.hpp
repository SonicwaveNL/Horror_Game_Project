#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <string>
#include <iRectangle.hpp>

class UIElement {
  private:
    sf::Text label;
    sf::RectangleShape IRect;
    sf::Font font;
    sf::Color labelColor;
    sf::Color borderColor;
    sf::Color fontColor;

  public:
    UIElement(sf::Vector2f position,
              std::string labelText = "Placeholder",
              sf::Color labelColor = sf::Color::Cyan,
              sf::Color fontColor = sf::Color::Blue,
              sf::Color borderColor = sf::Color::Magenta,
              sf::Vector2f size = sf::Vector2f(500.f, 120.f),
              objectType type = objectType::UIElement, float speed = 0)
        : labelColor(labelColor), borderColor(borderColor),
          fontColor(fontColor) {
        IRect.setPosition(position);
        IRect.setFillColor(labelColor);
        IRect.setSize(size);
        std::cout << "constructor called\n";
        font.loadFromFile("Resources/Arial.ttf");
        label.setFont(font);
        label.setFillColor(fontColor);
        setText(labelText);
        setLabelPosition();
    }

    ///\brief
    /// Move the switch, regardless of what object is in the new location.
    ///\details
    /*The switch's move isn't implemented, because we don't want it to move.*/
    ///@param direction
    /*The direction the switch should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) ;

    ///\brief
    /// Only moves the switch if the new location is empty.
    ///\details
    /*The switch's moveIfPossible does nothing, because we don't want it to
     * move.*/
    ///@param direction
    /*The direction the switch should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void moveIfPossible(sf::Vector2f direction) ;

    ///\brief
    /// Whether or not the user intersects with its parameter.
    ///@param obj
    /*The object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(IObject & obj);

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

    void setLabelPosition();

    ///\brief
    /// Set the color of the object.
    ///@param color
    /*sf::Color the new color of the object.*/

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*The window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) ;

    ///\brief
    /// What the object does when the user collides or interacts with it.
    ///\details
    /*Should only be called by the action1 keyword. This then flips the
     * switch.*/
    ///@param obj
    /*The object that is colliding with the switch*/
    void collision(IObject & obj) ;

    ///\brief
    /// Returns the outer boundaries of the switch object
    ///@return sf::FloatRect
    sf::FloatRect getBounds() ;

    ///\brief
    /// Function to get the position.
    sf::Vector2f getPosition();

    void setBorderColor(sf::Color color);

    void setText(std::string text);
};

#endif