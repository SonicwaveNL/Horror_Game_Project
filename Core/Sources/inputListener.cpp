#include "../Headers/inputHandler.hpp"

bool InputHandler::checkInput(sf::Keyboard::Key& input)
{
    return false;
};

bool InputHandler::checkInput(sf::Joystick::Axis& input)
{
    return false;
};

sf::Vector2f InputHandler::getMousePos(sf::RenderWindow& window)
{
    return sf::Vector2f(0.0f,0.0f);
};