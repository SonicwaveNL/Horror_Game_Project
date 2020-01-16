#ifndef Wall_hpp
#define Wall_hpp

#include "IObject.hpp"
#include <SFML/Graphics.hpp>
///@file
///\brief
/// A wall object, through which a user can't move
///\details
/// A wall blocks a player from walking somewhere.
class Wall : public IObject {
  public:
    ///\brief
    /// The constructor for the Wall object
    ///\details
    /// It takes in a color, texture and position, to initialize the IObject
    /// instance.
    ///@param size
    /*The size the wall will be.*/
    ///@param position
    /*The location the top left corner of the wall will be on.*/
    ///@param color
    /*An sfml colour, which the wall will be when the texture isn't loaded.
    Defaults to black.*/
    Wall(sf::Vector2f position, sf::Vector2f size, 
         std::vector<std::shared_ptr<IObject>> & objects, sf::Color color = sf::Color::White)
        : IObject(position, size, objects, "Wall",color){}

    ///\brief
    /// Move the wall in a specific direction, if it's possible
    ///\details
    /// The wall gets moved, if and only if the location it moves to does NOT
    /// contain any other IObjects. The direction gets multiplied by the 'speed'
    /// member. If you move the wall 5 in the X direction, the wall moves
    /// 5*speed in the X direction.
    ///@param direction
    /*The direction to move in, which will get multiplied by the object's speed
     * when it moves.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    ///'Teleport' the wall to a specific location.
    ///\details
    /*This function is not affected by the 'speed' member, as it teleports to
     * the specific location.*/
    ///@param target
    /*The new position to put the wall.*/
    void jump(sf::Vector2f target) override;

    ///\brief
    /// Whether or not the wall collides with the object given in the
    /// parameters.
    ///@param obj
    /*The object to check if the wall collides with it.*/
    ///@return
    /*Returns true if the user collides with the object and false if it
     * doesn't.*/
    bool intersect(IObject & obj) override;

    ///\brief
    ///Moves the wall to its previous position, if it collides with anything. 
    ///@param obj
    /*The object that is colliding with the wall.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Draws the wall to the window.
    ///@param window
    /*The sfml renderwindow to draw the object to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Return the boundaries of the wall object.
    ///\details
    /*Returns the rectangle the object is surrounded by.*/
    ///@return
    /*The floatRect the object is surrounded by.*/
    sf::FloatRect getBounds() override;
};

#endif // Wall_hpp