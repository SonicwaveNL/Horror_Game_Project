#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <string>
#include <iRectangle.hpp>

class UIElement : public IRectangle {
private:
    sf::Text label;
    sf::Font font;
    sf::Color labelColor;
    sf::Color borderColor;
    sf::Color fontColor;
public:
    UIElement(
        sf::Vector2f position,
        std::vector<std::shared_ptr<IObject>> & objects,
        std::string labelText = "Placeholder",
        sf::Color labelColor = sf::Color::Cyan,
        sf::Color borderColor = sf::Color::Magenta,
        sf::Color fontColor = sf::Color::Blue,
        sf::Vector2f size = sf::Vector2f(500.f, 120.f),
        objectType type = objectType::UIElement,
        float speed = 0
    ):
        IRectangle(position,objects,labelColor,speed,type,size),
        labelColor(labelColor),
        borderColor(borderColor),
        fontColor(fontColor)
    {
        std::cout << "constructor called\n";
        font.loadFromFile("Resources/Arial.ttf");
        label.setFont(font);
        label.setFillColor(fontColor);
        setText(labelText);
        setLabelPosition();
    }

    ///\brief
    ///Move the switch, regardless of what object is in the new location.
    ///\details
    /*The switch's move isn't implemented, because we don't want it to move.*/
    ///@param direction
    /*The direction the switch should move in. Passing a 1 will move the door at its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    ///Only moves the switch if the new location is empty.
    ///\details
    /*The switch's moveIfPossible does nothing, because we don't want it to move.*/
    ///@param direction
    /*The direction the switch should move in. Passing a 1 will move the door at its default speed, passing a 2 will move it twice as fast etc.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    ///Whether or not the user intersects with its parameter.
    ///@param obj
    /*The object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    ///Whether or not the user intersects with its parameter.
    ///@param obj
    /*The object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(sf::Vector2f position);


    ///\brief
    ///Set the position of the switch to the target.
    ///@param target
    /*sf::Vector2f containing the new position of the object.*/
    void setPosition(sf::Vector2f target) override;

    void setLabelPosition();

    ///\brief
    ///Set the color of the object.
    ///@param color
    /*sf::Color the new color of the object.*/

    ///\brief
    ///Draw the object to the given window.
    ///@param window
    /*The window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    ///What the object does when the user collides or interacts with it.  
    ///\details
    /*Should only be called by the action1 keyword. This then flips the switch.*/
    ///@param obj
    /*The object that is colliding with the switch*/
    void collision(IObject & obj) override;

    ///\brief
    ///Returns the outer boundaries of the switch object
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    ///Function to get the position.
    sf::Vector2f getPosition();

    void setBorderColor(sf::Color color);

    void setText(std::string text);
};

#endif