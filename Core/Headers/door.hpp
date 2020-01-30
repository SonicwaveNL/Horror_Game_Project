#ifndef DOOR_HPP
#define DOOR_HPP

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>

///@file

///\brief
/// The door class.
///\details
/* Opens when a certain treshold of flipped switches is reached and then
 * finishes the level when a player interacts with it.*/
class Door : public IRectangle {
  private:
    bool isOpen = false;

  public:
    ///\brief
    /// Door object constructor.
    ///\details
    /// The Door constructor parameters are used to create a IObject.
    Door(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Color color = sf::Color::Cyan, float speed = 0,
         objectType type = objectType::Door)
        : IRectangle(position, objects, color, speed, type){};

    ///\brief
    /// Door object constructor, with texture.
    ///\details
    /// The Door constructor parameters are used to create a IObject with textures.
    Door(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Texture * texture, sf::Color color = sf::Color::White,
         float speed = 0, objectType type = objectType::Door)
        : IRectangle(position, objects, texture, color, speed, type){};

    ///\brief
    /// Move the object, regardless of other objects in its way.
    ///\details
    /*This is not implemented, as the door can't move yet.*/
    ///@param direction
    /*sf::Vector2f, The direction the door should move in. Passing a 1 will move the door at
     * it's default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Set if the door is open or not. True means it should open, false means
    /// it should close. 
    ///\details
    /*If the door is closed, nothing will happen if the user interacts with the
     * player. If it's open, the user will win.*/
    ///@param state
    /*Bool, Whether the door should be open or not. True means it should open, false
     * means it should close.*/
    void setOpenState(bool state);

    ///\brief
    /// Whether the door is open or closed.
    ///@return bool
    bool getOpenState();

    ///\brief
    /// Draw IObject on window.
    ///\details
    /*Draw the IObject on the sf::RendWindow.*/
    ///@param window
    /*sf::RenderWindow&*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move Door to direction, if possible.
    ///\details
    /*Move Door to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f, the direction to try to move in.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Door intersect.
    ///\details
    /*Check if an Door intersect with given iObject.*/
    ///@param obj
    /*IObject&*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    ///Set the position of the Door to the given position.
    ///@param position
    /*sf::Vector2f, the position to set for the Door.*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Door collision, does nothing.
    ///@param obj
    /*IObject&*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get the Doors GlobalBounds.
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;
};

#endif // DOOR_HPP