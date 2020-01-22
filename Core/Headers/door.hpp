#ifndef DOOR_HPP
#define DOOR_HPP

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>

///@file

///\brief
/// The door class
///\details
/* Opens when a certain treshold of flipped switches is reached and then
 * finishes the level when a player interacts with it.*/
class Door : public IRectangle {
  private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool isOpen = false;

  public:
    ///\brief
    /// Door object constructor.
    ///\details
    /// The Door constructor parameters are used to create a IObject.
    ///@param position
    /* An sf::Vector2f, which is the coordinate of the top left position of he door.*/
    ///@param objects
    /* A vector of pointers to game objects.*/
    ///@param color
    /* (Default=White) The color of the door object.*/
    ///@param speed
    /* (Default=0) Float of the speed of the door. The door can't move, so this doesn't affect anything.*/
    ///@param type
    /* (Default=Type::Door) This defines the object type for the system. *THIS HAS TO MATCH THE OBJECT*, if the type doesn't match the object, segmentation faults WILL occur.*/
    Door(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Color color = sf::Color::White, float speed = 0,
         objectType type = objectType::Door)
        : IRectangle(position, objects, color, speed, type){};


    ///\brief
    ///Move the object, regardless of other objects in its way.
    ///\details
    /*This is not implemented, as the door can't move yet.*/
    ///@param direction
    /*The direction the door should move in. Passing a 1 will move the door at its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    ///Set the color of the door.
    ///@param color
    /*The color to change the door to.*/
    void setColor(sf::Color color) override;

    ///\brief
    ///Set if the door is open or not. True means it should open, false means it should close.  
    ///\details
    /*If the door is closed, nothing will happen if the user interacts with the player. If it's open, the user will win.*/
    ///@param state
    /*Whether the door should be open or not. True means it should open, false means it should close.*/
    void setOpenState(bool state);

    ///\brief
    ///Whether the door is open or closed.
    ///@return bool 
    bool getOpenState();
    
    ///\brief
    /// Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move Door to direction, if possible.
    ///\details
    /*Move Door to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Door intersect.
    ///\details
    /*Check if an Door intersect with given iObject.*/
    ///@param obj
    /*IObject*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Jump Door object to given target
    ///\details
    /*Jump Door object to given sf::Vector2f target.*/
    ///@param obj
    /*sf::Vector2f*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Door collision.
    ///\details
    /*Door collision.*/
    ///@param obj
    /*IObject by reference*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get Door GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the Door object.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;
    
    ///\brief
    ///Function to get the position.
    sf::Vector2f getPosition() override;
};

#endif // DOOR_HPP