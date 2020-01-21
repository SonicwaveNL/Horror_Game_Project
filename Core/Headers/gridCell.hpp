#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <string>
#include <iRectangle.hpp>

class GridCell : public IRectangle{
  private:
    // Flyweight pattern
    // sf::Texture * texture;
    // sf::Sprite sprite;
    std::string cellType = "Floor";

  public:
    // For AI
    // int row;
    // int column;
    // int dist;

    int value = 0;
    bool visited = false;
    bool isWalkAble = true;

    GridCell(sf::Vector2f position,
             std::vector<std::shared_ptr<IObject>> & objects,
             sf::Color color = sf::Color::White)
        : IRectangle(position, objects, color) {
        iRect.setSize(sf::Vector2f(20.f, 20.f));
        iRect.setOutlineColor(sf::Color::Yellow);
    };

    void draw(sf::RenderWindow & window) override;
    void move(sf::Vector2f direction) override;
    void moveIfPossible(sf::Vector2f direction) override;
    bool intersect(IObject & obj) override;
    void setPosition(sf::Vector2f position) override;
    sf::Vector2f getPosition() override;
    void collision(IObject & obj) override;
    sf::FloatRect getBounds() override;
    void setColor(sf::Color color) override;
    void setCellType(std::string type);
    std::string getCellType();
    GridCell & operator=(const GridCell & rhs) {
        if (this != &rhs) {
            this->setPosition( rhs.iRect.getPosition());
            this->setColor( rhs.color );
            this->prevPosition = rhs.prevPosition;
            this->speed = rhs.speed;
            this->iRect.setSize( rhs.iRect.getSize());
        }
        return *this;
    }
};

#endif