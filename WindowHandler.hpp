#ifndef WindowHandler_hpp
#define WindowHandler_hpp

#include <SFML/Graphics.hpp>
#include "Objects.hpp"

class WindowHandler {
  private:
    void draw(std::vector<IObject *> & objects);
    sf::RenderWindow & window;

  public:
    WindowHandler(sf::RenderWindow & window) : window(window) {}
};

#endif // WindowHandler_hpp