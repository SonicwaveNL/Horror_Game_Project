#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iObject.hpp>
#include <iCircle.hpp>
#include <door.hpp>
#include <wall.hpp>

///@file

///\brief
/// Player class.
///\details
/*A Player class, create a playable character*/
class Player : public IRect {
  private:
    bool win = false;
    sf::Texture texture;

  public:
    ///\brief
    /// Player object constructor.
    ///\details
    /// The Player constructor parameters are used to create a IObject.
    ///@param texture
    /*a SFML sf::Texture, this is the texture for the object*/
    ///@param position
    /*a sf::Vector2f position, this is the position of the object*/
    ///@param objects
    /*a std::vector<IObject*> vector array, this is a group of all IObjects
     * within*/
    ///@param color
    /*a SFML sf::Color, this is the color of the texture.*/
    Player(sf::Texture & texture, sf::Vector2f position,
           std::vector<std::shared_ptr<IObject>> & objects,
           sf::Color color = sf::Color(255, 98, 0), float speed = 5)
        : ICircle(position, objects, color, speed), texture(texture) {}

    ///\brief
    /// Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RenderWindow*/
    ///@param window
    /*sf::RenderWindow*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move Player to direction, if possible.
    ///\details
    /*Move Player to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Player intersect.
    ///\details
    /*Check if an Player intersect with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Jump Player object to given target
    ///\details
    /*Jump Player object to given sf::Vector2f target.*/
    ///@param obj
    /*sf::Vector2f*/
    void jump(sf::Vector2f target) override;

    ///\brief
    /// Player collision.
    ///\details
    /*Player collision.*/
    ///@param obj
    /*IObject*/
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
};

#endif // PLAYER_HPP