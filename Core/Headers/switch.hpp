#ifndef SWITCH_hpp
#define SWITCH_hpp

#include <iRectangle.hpp>
#include <player.hpp>
class Switch : public IRectangle {
 private:
    bool active = false;
  public:
    Switch(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Color color = sf::Color::Green, float speed = 0)
        : IRectangle(position, objects, color, speed) {}

    void move(sf::Vector2f direction) override;

    void moveIfPossible(sf::Vector2f direction) override;

    bool intersect(IObject & obj) override;

    void setPosition(sf::Vector2f target) override;

    void setColor(sf::Color color) override;

    void draw(sf::RenderWindow & window) override;

    void collision(IObject & obj) override;

    sf::FloatRect getBounds() override;


    bool isActive();
};

#endif // SWITCH_hpp