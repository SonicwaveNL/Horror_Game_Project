#ifndef Wall_hpp
#define Wall_hpp

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>
///@file

///\brief
/// Wall class. 
///\details
/// Wall class through which the player typically can't move.
class Wall : public IRectangle {
  public:
    ///\brief
    /// Wall constructor.
    Wall(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Color color = sf::Color::White, float speed = 0,
         objectType type = objectType::Wall)
        : IRectangle(position, objects, color, speed, type) {}

    ///\brief
    /// Wall constructor, supports texture.
    Wall(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Texture * texture, sf::Color color = sf::Color::White,
         float speed = 0, objectType type = objectType::Wall)
        : IRectangle(position, objects, texture, color, speed, type) {}

    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Move the wall in a specific direction, if it's possible.
    ///\details
    /// The wall gets moved, if and only if the location it moves to does NOT
    /// contain any other IObjects. The direction gets multiplied by the 'speed'
    /// member. If you move the wall 5 in the X direction, the wall moves
    /// 5*speed in the X direction.
    ///@param direction
    /*sf::Vector2f, the direction to move in, which will get multiplied by the object's speed
     * when it moves.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Set the position of the IObject to the given position.
    ///\details
    /*The position to put the IObject.*/
    ///@param position
    /*sf::Vector2f*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Whether or not the wall collides with the object given in the
    /// parameters.
    ///@param obj
    /*IObject &, the object to check if the wall collides with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Handles collision for the wall.
    ///\details
    ///Moves the wall to its previous position, if it collides with anything
    ///@param obj
    /*The object that is colliding with the wall.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Draws the wall to the window.
    ///@param window
    /*sf::RenderWindow &, the SFML RenderWindow to draw the object to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Return the boundaries of the wall object.
    ///\details
    /*Returns the rectangle the object is surrounded by.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    ///Gets the position of the wall.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;
};

#endif // Wall_hpp