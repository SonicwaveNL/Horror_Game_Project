#ifndef SWITCH_hpp
#define SWITCH_hpp

#include <iRectangle.hpp>
#include <player.hpp>

///@file
///\brief
///Switch class.
///\details
/*An object the user has to interact with to open the door object*/
class Switch : public IRectangle {
  private:
    bool active = false;

  public:
    ///\brief
    /// Switch constructor
    Switch(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Color color = sf::Color::Green, float speed = 0,
           objectType type = objectType::Switch)
        : IRectangle(position, objects, color, speed, type) {}

    ///\brief
    /// Switch constructor, supports texture.
    Switch(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Texture * texture, sf::Color color = sf::Color::Green,
           float speed = 0, objectType type = objectType::Switch)
        : IRectangle(position, objects, texture, color, speed, type) {}

    ///\brief
    /// Move the switch, regardless of what object is in the new location.
    ///\details
    /*The switch's move isn't implemented, because we don't want it to move.*/
    ///@param direction
    /*sf::Vector2f, the direction the switch should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Only moves the switch if the new location is empty.
    ///\details
    /*The switch's moveIfPossible does nothing, because we don't want it to
     * move.*/
    ///@param direction
    /*sf::Vector2f, the direction the switch should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Whether or not the user intersects with its parameter.
    ///@param obj
    /*IObject&, the object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Set the position of the switch to the position.
    ///@param position
    /*sf::Vector2f, containing the new position of the object.*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*sf::RenderWindow &, the window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// What the object does when the user collides or interacts with it.
    ///\details
    /*Should only be called by the action1 keyword. This then flips the
     * switch.*/
    ///@param obj
    /*IObject &, the object that is colliding with the switch*/
    void collision(IObject & obj) override;

    ///\brief
    /// Returns the outer boundaries of the switch object
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Whether or not the switch is flipped or not
    ///\details
    /*Returns true if the switch is flipped ON.*/
    ///@return bool
    bool isActive();

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition();
};

#endif // SWITCH_hpp