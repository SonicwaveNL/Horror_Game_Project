#include "inputListener.hpp"

///@file
///\brief
/// KeyboardMouseclass for recording keyboardpresses and mouse position.
///\details
/*Keyboardclass has no private members. The class had three functions. one for
checkin the if a given key is pressed on the ketboard, one for use of the
joystick and for returning the mouse position.*/
class KeyboardMouse : public InputListener {
 public:
  ///\brief
  /// checkInput( sf::Keyboard::Key & input ) function.
  ///\details
  /*checkinput function that returns a bool that gives if the key was
   * pressed.*/
  ///@param input
  /*sf::Keyboard::Key &*/
  ///@return
  /*bool*/
  bool checkInput(sf::Keyboard::Key& input) override;

  // void checkInput(sf::Joystick::Axis & input) override;

  ///\brief
  /// getMousePos() function
  ///\details
  /*getMousepos returns the current mouseposition on the screen in
   * sf::Vector2f format*/
  ///@param Name of parameter
  /*sf::RenderWindow& window*/
  ///@return
  /*sf::vector2f*/
  sf::Vector2f getMousePos(sf::RenderWindow& window) override;
};
