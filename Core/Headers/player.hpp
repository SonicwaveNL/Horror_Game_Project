#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iObject.hpp>
#include <iRectangle.hpp>
#include <door.hpp>
#include <wall.hpp>

///@file

///\brief
/// Player class.
///\details
/*Player class, used a playable character.*/
class Player : public IRectangle {
  private:
    bool win = false;
    bool lose = false;

  public:
    ///\brief
    /// Player object constructor.
    Player(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Color color = sf::Color::Transparent, float speed = 4,
           objectType type = objectType::Player)
        : IRectangle(position, objects, color, speed, type) {}

    ///\brief
    /// Player constructor, supports texture.
    Player(sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Texture * texture, sf::Color color = sf::Color::Transparent,
           float speed = 4, objectType type = objectType::Player)
        : IRectangle(position, objects, texture, color, speed, type) {}

    ///\brief
    /// Draw IObject on window.
    ///\details
    /*Draw the IObject on the sf::RenderWindow.*/
    ///@param window
    /*sf::RenderWindow*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Move Player to direction, if possible.
    ///\details
    /*Move Player to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Player intersects.
    ///\details
    /*Check if an Player intersects with given IObject.*/
    ///@param obj
    /*IObject&*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Set the position of the IObject to the given position.
    ///\details
    /*The position to put the IObject.*/
    ///@param position
    /*sf::Vector2f*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;

    ///\brief
    /// IObject collision.
    ///\details
    /*IObject collision.*/
    ///@param obj
    /*IObject&, the object to check collision with.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get Player GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the Player object.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Check the win variable.
    ///@return bool
    bool checkWin();

    ///\brief
    /// Check the lose variable.
    ///@return bool
    bool checkLose();

    ///\brief
    /// Reset the player lose and win vars.
    void reset();

    ///\brief
    /// Makes sure the player is no longer colliding with a wall.
    ///\details
    /*Keeps stepping the player in the direction opposite of what caused it to
     * collide until it no longer collides.*/
    ///@param obj
    /*IObject&, the object we collide with.*/
    ///@param oldDir
    /*sf::Vector2f, the direction we wanted to go when we collided.*/
    void fixMove(IObject & obj, sf::Vector2f oldDir);
};

#endif // PLAYER_HPP