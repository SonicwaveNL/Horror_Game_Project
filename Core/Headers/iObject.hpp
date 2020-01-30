#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>
#include <support.hpp>
///@file
///\brief
/// IObject class.
///\details
/*An abstract class to handle/create SMFL objects.*/
class IObject {
  protected:
    sf::Color color;
    sf::Vector2f prevPosition;
    std::vector<std::shared_ptr<IObject>> & objects;
    objectType type;
    float speed = 5;
    bool ableToDraw = false;

  public:
    ///\brief
    /// IObject constructor.
    IObject(std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Transparent, float speed = 0,
            objectType type = objectType::Abstract)
        : objects(objects), color(color), speed(speed), type(type) {}

    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    virtual void move(sf::Vector2f direction) = 0;
    
    ///\brief
    /// Move IObject to direction, if possible.
    ///\details
    /*Move IObject to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    virtual void moveIfPossible(sf::Vector2f direction) = 0;

    ///\brief
    /// Check if IObjects are intersecting.
    ///\details
    /*Check if an IObject is intersecting with given IObject.*/
    ///@param obj
    /*IObject&*/
    ///@return bool
    virtual bool intersect(IObject & obj) = 0;

    ///\brief
    /// Set the position of the IObject to the given position.
    ///\details
    /*The position to put the IObject.*/
    ///@param position
    /*sf::Vector2f*/
    virtual void setPosition(sf::Vector2f position) = 0;

    ///\brief
    ///Gets the position of the IObject.
    ///@return sf::Vector2f
    virtual sf::Vector2f getPosition() = 0;

    ///\brief
    /// Sets the color of the IObject.
    ///@param color
    /*The sf::Color of the IObject.*/
    virtual void setColor(sf::Color color) = 0;

    ///\brief
    /// Draw IObject on window.
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow&*/
    virtual void draw(sf::RenderWindow & window) = 0;

     ///\brief
    /// IObject collision.
    ///\details
    /*IObject collision.*/
    ///@param obj
    /*IObject&, the object to check collision with.*/
    virtual void collision(IObject & obj) =0;

    ///\brief
    /// Get IObject GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the IObject.*/
    ///@return sf::FloatRect
    virtual sf::FloatRect getBounds() = 0;

    ///\brief
    /// Gets the type of the IObject.
    ///@return objectType
    objectType getType();

    ///\brief
    /// Function to change the speed.
    ///@param newSpeed
    /*float*/
    virtual void setSpeed(float newSpeed);

    ///\brief
    ///Get the speed.
    ///@return float
    float getSpeed();
};

#endif // IOBJECT_HPP