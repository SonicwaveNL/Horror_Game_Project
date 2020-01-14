#ifndef WindowHandler_hpp
#define WindowHandler_hpp

#include <SFML/Graphics.hpp>
#include "Objects.hpp"

class WindowHandler {
  private:
    void draw(sf::RenderWindow & window, std::vector<object *> & objects);

  public:
}

#endif // WindowHandler_hpp