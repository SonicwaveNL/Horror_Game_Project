#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <string>
#include <iRectangle.hpp>

class GridCell : public IRectangle {
private:
    // Flyweigth pattern    
    sf::Texture * texture;
    sf::Sprite * sprite;
    std::string type = "Floor";
public:
    // For AI
    // int row;
    // int column;
    // int dist;
    
    GridCell(
        sf::Vector2f position, 
        std::vector<std::shared_ptr<IObject>> & objects,
        sf::Color color = sf::Color::White
    ):
        IRectangle(
        position, 
        objects, 
        color
    ){
        iRect.setSize(sf::Vector2f(20.f,20.f));
        iRect.setOutlineColor(sf::Color::Yellow);
    };

    void draw(sf::RenderWindow & window) override;
    void moveIfPossible(sf::Vector2f direction) override;
    bool intersect(IObject & obj) override;
    void setPosition(sf::Vector2f position) override;
    void collision(IObject & obj) override;
    sf::FloatRect getBounds() override;

    void setType(std::string type);
};

#endif