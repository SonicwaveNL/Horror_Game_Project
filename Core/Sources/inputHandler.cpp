#include "../Headers/inputHandler.hpp"

enum class inputType;
enum class actionKeyword;

InputHandler::InputHandler(){
  keybMap[actionKeyword::escape] = sf::Keyboard::Escape;
  keybMap[actionKeyword::action1] = sf::Keyboard::H;
  keybMap[actionKeyword::action2] = sf::Keyboard::J;
  keybMap[actionKeyword::action3] = sf::Keyboard::K;
  keybMap[actionKeyword::action4] = sf::Keyboard::L;
  keybMap[actionKeyword::select] = sf::Keyboard::Space;
  keybMap[actionKeyword::up] = sf::Keyboard::Up;
  keybMap[actionKeyword::down] = sf::Keyboard::Down;
  keybMap[actionKeyword::left] = sf::Keyboard::Left;
  keybMap[actionKeyword::right] = sf::Keyboard::Right;
}
void InputHandler::setInputType(inputType iType) { type = iType; };

bool InputHandler::checkInput(actionKeyword aKey) {
  if (type == inputType::keyboard) {
    return listener.checkInput(keybMap[aKey]);
  }
}