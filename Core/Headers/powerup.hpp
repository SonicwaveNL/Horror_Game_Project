#ifndef POWERUP_hpp
#define POWERUP_hpp

#include <iRectangle.hpp>

enum class BuffType{
    PlayerSpeed,
    EnemySpeed
};

///@file
///\brief
/// The powerup object class
///\details
/*This object gives the user a specific buff or debuff*/
class Powerup : public IRectangle {
  private:
  public:
    ///\brief
    /// Powerup constructor
    Powerup(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Color color = sf::Color::Yellow, float speed = 0,
           objectType type = objectType::Powerup)
        : IRectangle(position, objects, color, speed, type) {}

    ///\brief
    /// Powerup constructor, supports texture.
    Powerup(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Texture * texture, sf::Color color = sf::Color::Transparent,
           float speed = 0, objectType type = objectType::Powerup)
        : IRectangle(position, objects, texture, color, speed, type) {}


    ///\brief
    /// Move the Powerup, regardless of what object is in the new location.
    ///\details
    /*The Powerup's move isn't implemented, because we don't want it to move.*/
    ///@param direction
    /*The direction the Powerup should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Only moves the Powerup if the new location is empty.
    ///\details
    /*The Powerup's moveIfPossible does nothing, because we don't want it to
     * move.*/
    ///@param direction
    /*The direction the Powerup should move in. Passing a 1 will move the door at
     * its default speed, passing a 2 will move it twice as fast etc.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Whether or not the user intersects with its parameter.
    ///@param obj
    /*The object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Set the position of the Powerup to the target.
    ///@param target
    /*sf::Vector2f containing the new position of the object.*/
    void setPosition(sf::Vector2f target) override;

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*The window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// What the object does when the user collides or interacts with it.
    ///\details
    /*Should only be called by the action1 keyword. This then flips the
     * Powerup.*/
    ///@param obj
    /*The object that is colliding with the Powerup*/
    void collision(IObject & obj) override;

    ///\brief
    /// Returns the outer boundaries of the Powerup object
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    void buff(BuffType type, int magnitude = 0);

};

#endif // POWERUP_hpp