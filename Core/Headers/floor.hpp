#ifndef Floor_hpp
#define Floor_hpp

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>
///@file

///\brief
/// A Floor object, through which a user can't move
///\details
/// A Floor blocks a player from walking somewhere.
class Floor : public IRectangle {
  public:
    ///\brief
    /// The constructor for the Floor object
    ///\details
    /// It takes in a color, texture and position, to initialize the IObject
    /// instance.
    ///@param size
    /*The size the Floor will be.*/
    ///@param position
    /*The location the top left corner of the Floor will be on.*/
    ///@param color
    /*An SFML colour, which the Floor will be when the texture isn't loaded.
    Defaults to black.*/
    Floor(
      sf::Vector2f position, 
      std::vector<std::shared_ptr<IObject>> & objects,
      sf::Color color = sf::Color::White, float speed = 0,objectType type = objectType::Floor
    ): 
      IRectangle(
        position, 
        objects, 
        color,
        speed,
        type
      ) {}

    Floor(
      sf::Vector2f position, 
      std::vector<std::shared_ptr<IObject>> & objects,
      sf::Texture * texture,
      sf::Color color = sf::Color::White, float speed = 0,objectType type = objectType::Floor
    ): 
      IRectangle(
        position, 
        objects, 
        texture,
        color,
        speed,
        type
      ) {}


    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param directionGame::l
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Move the Floor in a specific direction, if it's possible
    ///\details
    /// The Floor gets moved, if and only if the location it moves to does NOT
    /// contain any other IObjects. The direction gets multiplied by the 'speed'
    /// member. If you move the Floor 5 in the X direction, the Floor moves
    /// 5*speed in the X direction.
    ///@param direction
    /*The direction to move in, which will get multiplied by the object's speed
     * when it moves.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    ///Sets the new color of the object.
    ///@param color
    /*The new sf::Color of the object*/

    ///\brief
    ///'Teleport' the Floor to a specific location.
    ///\details
    /*This function is not affected by the 'speed' member, as it teleports to
     * the specific location.*/
    ///@param target
    /*The new position to put the Floor.*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Whether or not the Floor collides with the object given in the
    /// parameters.
    ///@param obj
    /*The object to check if the Floor collides with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Moves the Floor to its previous position, if it collides with anything.
    ///@param obj
    /*The object that is colliding with the Floor.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Draws the Floor to the window.
    ///@param window
    /*The SFML renderwindow to draw the object to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Return the boundaries of the Floor object.
    ///\details
    /*Returns the rectangle the object is surrounded by.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;
    ///\brief
    ///Function to get the position.
    sf::Vector2f getPosition() override;
};

#endif // Floor_hpp