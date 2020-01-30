#ifndef Floor_hpp
#define Floor_hpp

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>
///@file

///\brief
/// A Floor object.
///\details
/// A Floor is a tile over which the player can move.
class Floor : public IRectangle {
  public:
    ///\brief
    /// The constructor for the Floor object.
    Floor(sf::Vector2f position,
          std::vector<std::shared_ptr<IObject>> & objects,
          sf::Color color = sf::Color::White, float speed = 0,
          objectType type = objectType::Floor)
        : IRectangle(position, objects, color, speed, type) {}
    ///\brief
    /// The constructor for the Floor object with a texture.
    Floor(sf::Vector2f position,
          std::vector<std::shared_ptr<IObject>> & objects,
          sf::Texture * texture, sf::Color color = sf::Color::White,
          float speed = 0, objectType type = objectType::Floor)
        : IRectangle(position, objects, texture, color, speed, type) {}

    ///\brief
    /// Move the IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Move the Floor in a specific direction, if it's possible.
    ///@param direction
    /*sf::Vector2f, the direction to move in, which will get multiplied by the object's speed
     * when it moves.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    ///Set the position of the Floor to the given position.
    ///@param target
    /*The position to put the Floor.*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Whether or not the Floor intersects with the IObject given in the
    /// parameters.
    ///@param obj
    /*IObject &, the object to check if the Floor intersects with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    ///Does nothing.
    ///@param obj
    /*IObject &*/
    void collision(IObject & obj) override;

    ///\brief
    /// Draws the Floor to the window.
    ///@param window
    /*sf::RenderWindow &, the SFML renderwindow to draw the object to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Return the boundaries of the Floor object.
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;
};

#endif // Floor_hpp