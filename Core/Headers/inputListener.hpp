#include "../SFML/Graphics.hpp"
///@file
///\brief
/// Abstract class for hardware input.
///\details
/*This class contains abstract (non implemented) functions that need to be
called by different hardware. It uses the default c++ constructor.*/
class InputListener {
 public:
 
 ///\brief
 ///Abstract function that
 ///\details
 /*detailed description*/
  virtual bool checkInput(sf::Keyboard::Key& input);
  virtual bool checkInput(sf::Joystick::Axis& input);
  virtual sf::Vector2f getMousePos();
};