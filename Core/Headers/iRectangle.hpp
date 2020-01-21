#ifndef IRECTANGLE_HPP
#define IRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

class IRectangle : public IObject {
  protected:
    sf::RectangleShape iRect;

  public:
    IRectangle(sf::Vector2f position,
               std::vector<std::shared_ptr<IObject>> & objects,
               sf::Color color = sf::Color::Transparent, float speed = 0,
               Type type = Type::Abstract)
        : IObject(objects, color, speed, type) {
        iRect.setPosition(position);
        iRect.setSize(sf::Vector2f(20.f, 20.f));
    }

    void setSize(sf::Vector2f size);
};

#endif