#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include <support.hpp>

///@file
///\brief
/// UiElement class.
///\details
/*class to create UIElements.*/
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
                buttonSource,
                sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{500, 120}});
            iRect.setTexture(&texture);
        } else if (size == sf::Vector2f(PIXEL16, PIXEL16)) {
            if (labelText == "P") {
                // use points texture
                sf::Image buttonSource;
                buttonSource.loadFromFile(
                    "Resources/Textures/scoreDisplay.png");
                texture.loadFromImage(
                    buttonSource,
                    sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{PIXEL16, PIXEL16}});
                iRect.setTexture(&texture);
                iRect.setScale(sf::Vector2f{2.f, 2.f});
            } else if (labelText == "J") {
                // use player speed
                sf::Image buttonSource;
                buttonSource.loadFromFile(
                    "Resources/Textures/ppSpeedDisplay.png");
                texture.loadFromImage(
                    buttonSource,
                    sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{PIXEL16, PIXEL16}});
                iRect.setTexture(&texture);
                iRect.setScale(sf::Vector2f{2.f, 2.f});

            } else if (labelText == "K") {
                // use enemy stop
                sf::Image buttonSource;
                buttonSource.loadFromFile(
                    "Resources/Textures/peSpeedDisplay.png");
                texture.loadFromImage(
                    buttonSource,
                    sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{PIXEL16, PIXEL16}});
                iRect.setTexture(&texture);
                iRect.setScale(sf::Vector2f{2.f, 2.f});
            }
            labelText = "";
        } else {
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
    /// Check if the given position intersects with the UIElement.
    ///@param position
    /*sf::Vector2f, the position to check intersection with.*/
    ///@return bool
    bool intersect(sf::Vector2f position);

    ///\brief
    /// Set the position of the UIElement to the position.
    ///@param position
    /*sf::Vector2f, containing the new position of the object.*/
    void setPosition(sf::Vector2f position);

    ///\brief
    /// Sets the position of the label relative to the sf::RectangleShape.
    void setLabelPosition();

    ///\brief
    /// Draw the UIElement to the given window.
    ///@param window
    /*sf::RenderWindow &, the window the UIElement should be drawn to.*/
    void draw(sf::RenderWindow & window);

    ///\brief
    /// Returns the outer boundaries of the UIElement.
    ///@return sf::FloatRect
    sf::FloatRect getBounds();

    ///\brief
    /// Function to get the position of the UIElement.
    ///@return sf::vector2f
    sf::Vector2f getPosition();

    ///\brief
    /// Sets the border color of the UIElement.
    ///@param color
    /*sf::Color*/
    void setBorderColor(sf::Color color);

    ///\brief
    /// Sets the text of the UIElement.
    ///@param text
    /*std::string, the text that should be shown.*/
    void setText(std::string text);

    ///\brief
    /// Gets the text of the UIElement.
    ///@return std::string
    std::string getText();

    ///\brief
    /// Sets the font size of the text within the UIElement.
    ///@param size
    /*int, the size in pixels of the font.*/
    void setTextSize(int size);

    ///\brief
    /// Set the font of the text within the UIElement.
    ///@param _font
    /*sf::Font * , a pointer to the font of the text.*/
    void setFont(sf::Font * _font);

    ///\brief
    ///Sets the font style to italic.
    void setItalic();
};

#endif