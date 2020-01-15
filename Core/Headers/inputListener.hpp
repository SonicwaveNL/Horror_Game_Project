#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP
#include "../../SFML-master/include/SFML/Graphics.hpp"
///@file
///\brief
/// Abstract class for hardware input.
///\details
/*This class contains abstract (non implemented) functions that need to be
called by different hardware. It uses the default c++ constructor.*/
class InputListener {
 public:
  ///\brief
  /// Abstract function that checks if a button (keyboard) is pressed.
  ///@param input
  /*sf::Keyboard::Key &*/
  ///@return
  /*bool*/
  virtual bool checkInput(sf::Keyboard::Key& input);

  ///\brief
  /// Abstract function that checks for the axis (and buttons) of joysticks
  ///@param input
  /*sf::Joystick::Axis &*/
  ///@return
  /*bool*/
  virtual bool checkInput(sf::Joystick::Axis& input);

  ///\brief
  /// Abstract function that checks the position of the mouse and returns it.
  ///@param window
  /*sf::RenderWindow &*/
  ///@return
  /*sf::Vector2f*/
  virtual sf::Vector2f getMousePos(sf::RenderWindow& window);
};
#endif  // INPUTLISTENER_HPP
