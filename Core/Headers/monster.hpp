#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iRectangle.hpp>
#include <door.hpp>
#include <wall.hpp>
#include <player.hpp>
#include <gridCell.hpp>
///@file

///\brief
/// Monster class.
///\details
/*Monster class, this is the monster who follows the player.*/
class Monster : public IRectangle {
  private:
    sf::Vector2f oldDirection = {1, 1};

  public:
    ///\brief
    /// Monster object constructor.
    Monster(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Transparent, float speed = 2,
            objectType type = objectType::Monster)
        : IRectangle(position, objects, color, speed, type){};


    ///\brief
    /// Monster constructor, supports texture.
    Monster(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Texture * texture, sf::Color color = sf::Color::Transparent,
            float speed = 2, objectType type = objectType::Monster)
        : IRectangle(position, objects, texture, color, speed, type){};

    ///\brief
    /// Draw IRectangle on window
    ///\details
    /*Draw the IRectangle on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow&*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    
    ///\brief
    /// Moves the monster in the direction it was going.
    void moveOld();

    ///\brief
    /// Move Monster to direction, if possible.
    ///\details
    /*Move Monster to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Monster intersects with IObject.
    ///\details
    /*Checks if an Monster intersects with given IObject.*/
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
    /// IObject collision.
    ///\details
    /*IObject collision.*/
    ///@param obj
    /*IObject&, the object to check collision with.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get Monster GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the Monster object.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;
};
#endif