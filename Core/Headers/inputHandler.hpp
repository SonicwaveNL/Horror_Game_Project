#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <map>
#include <support.hpp>
#include <keyboardMouse.hpp>
#include <inputListener.hpp>
///@file

///\brief
/// Input handler class, used for translating input commands.
///\details
/*This class is used for translating arbitrary input commands to SFML keyboard
keys. It is used with the enum class actionKeyword for its input.*/
class InputHandler {
  private:
    KeyboardMouse listener;
    inputType type = inputType::keyboard;
    std::map<actionKeyword, sf::Keyboard::Key> keybMap;
    std::map<actionKeyword, sf::Joystick::Axis> contMap;

  public:
    ///\brief
    /// Constructor for inputHandler class.
    InputHandler();

    ///\brief
    /// Function to set the input type you're using (keyboard/Joystick).
    ///\details
    /*This function is used to set the input type you are currently using. The
    default input type, so if this function is not called, is keyboard.*/
    ///@param iType
    /*enum class inputType*/
    void setInputType(inputType iType);

    ///\brief
    /// Function used to check if a button is pressed.
    ///\details
    /*This function is used for translating input from the enum class
    actionKeyword to the corresponding SFML button/key. When a command like "up"
    is send. It finds the corresponding keyboard key and checks if that
    key/button is pressed.*/
    ///@param aKey
    /*enum class actionKeyword.*/
    ///@return bool
    bool checkInput(actionKeyword aKey);
};
#endif // INPUTHANDLER_HPP
