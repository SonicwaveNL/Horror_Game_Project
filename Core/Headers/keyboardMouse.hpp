#ifndef KEYBOARDMOUSE_HPP
#define KEYBOARDMOUSE_HPP
#include <SFML/Graphics.hpp>
#include <inputListener.hpp>
///@file

///\brief
/// KeyboardMouseclass for recording keyboardpresses and mouse position.
class KeyboardMouse : public InputListener {
  public:
    ///\brief
    /// Check if sf::Keyboard::Key is pressed.
    ///@param input
    /*sf::Keyboard::Key &*/
    ///@return bool
    bool checkInput(sf::Keyboard::Key & input) override;

    ///\brief
    /// Gets the position of the mouse.
    ///\details
    /*getMousepos returns the current mouseposition on the screen in
     * sf::Vector2f format*/
    ///@param Name of parameter
    /*sf::RenderWindow& window*/
    ///@return sf::vector2f
    sf::Vector2f getMousePos(sf::RenderWindow & window) override;
};
#endif // KEYBOARDMOUSE_HPP