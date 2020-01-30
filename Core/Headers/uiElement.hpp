#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include <support.hpp>

///@file
///\brief
/// UiElement class
///\details
/*class to create UIElements that can be used in menus*/
class UIElement {
  private:
    sf::Text label;
    sf::RectangleShape iRect;
    sf::Font font;
    sf::Color labelColor;
    sf::Color borderColor;
    sf::Color fontColor;
    sf::Texture texture;
  public:
    ///\brief
    /// UIElement constructor.
    UIElement(sf::Vector2f position, std::string labelText = "Placeholder",
              sf::Color labelColor = sf::Color::Cyan,
              sf::Color fontColor = sf::Color::Blue,
              sf::Color borderColor = sf::Color::Magenta,
              sf::Vector2f size = sf::Vector2f(500.f, 120.f),
              objectType type = objectType::UIElement, float speed = 0)
        : labelColor(labelColor), borderColor(borderColor),
          fontColor(fontColor) {
        if (size == sf::Vector2f(500.f, 120.f)) {
          sf::Image buttonSource;
            buttonSource.loadFromFile("Resources/Textures/boohButton.png");
            texture.loadFromImage(
                buttonSource, sf::IntRect{sf::Vector2i{0, 0},
                                      sf::Vector2i{500,120} });
            iRect.setTexture(&texture);
        }else{

        iRect.setFillColor(labelColor);
        }
        iRect.setPosition(position);
        iRect.setSize(size);
        font.loadFromFile("Resources/winlose.ttf");
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
    void setPosition(sf::Vector2f target);

    ///\brief
    /// Sets the position of the label relative to the sf::RectangleShape.
    ///\details
    /*function that sets the text inside the sf::RectangleShape*/
    void setLabelPosition();

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*The window the object should be drawn to.*/
    void draw(sf::RenderWindow & window);

    ///\brief
    /// Returns the outer boundaries of the switch object
    ///@return sf::FloatRect
    sf::FloatRect getBounds();

    ///\brief
    /// Function to get the position.
    ///@return sf::vector2f
    sf::Vector2f getPosition();

    ///\brief
    /// setBorderColor
    ///\details
    /*sets the rectangle around the text to the given color*/
    ///@param color
    /*sf::Color*/
    void setBorderColor(sf::Color color);

    ///\brief
    /// setText function
    ///\details
    /*sets the text of the element to the given string*/
    ///@param text
    /*std::string*/
    void setText(std::string text);

    ///\brief
    /// getText function
    ///\details
    /*returns the text of the element*/
    ///@return std::string
    std::string getText();

    ///\brief
    /// Sets the font size of the text within the UI element
    ///@param size
    /*The size in pixels of the font*/
    void setTextSize(int size);

    ///\brief
    /// Set the font of the text within the UI element
    ///@param _font
    /*the sf::Font the new font should be*/
    void setFont(sf::Font * _font);
};

#endif