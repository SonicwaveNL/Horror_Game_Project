#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <SFML/Graphics.hpp>
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
    float speed = 5;
    objectType type;

  public:
    ///\brief
    ///IObject constructor
    ///@param objects
    /*The vector of pointers to the game objects.*/
    ///@param color
    /*(Default=Transparent) The color of the object.*/
    ///@param speed
    /*(Default=0) The speed of the object. How fast it moves when it moves*/
    ///@param type
    /* (Default=Type::Abstract) This defines the object type for the system. *THIS HAS TO MATCH THE OBJECT*, if the type doesn't match the object, segmentation faults WILL occur.*/
    IObject(std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Transparent, float speed = 0,
            objectType type = objectType::Abstract)
        : objects(objects), color(color), speed(speed), type(type) {

        }

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
    /// Check if IObjects are colliding.
    ///\details
    /*Check if an IObject is colliding with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return bool
    virtual bool intersect(IObject & obj) = 0;

    ///\brief
    /// Jump object to given target
    ///\details
    /*Jump an object to the given sf::Vector2f target*/
    ///@param target
    /*sf::Vector2f*/
    virtual void setPosition(sf::Vector2f target) = 0;

    ///\brief
    ///Sets the new color of the object.
    ///@param color
    /*The new sf::Color of the object*/
    virtual void setColor(sf::Color color) = 0;

    ///\brief
    /// Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow*/
    virtual void draw(sf::RenderWindow & window) = 0;

    ///\brief
    /// Interact with given object
    ///\details
    /*Perform interaction with given IObject*/
    ///@param obj
    /*IObject*/
    ///@return void
    virtual void collision(IObject & obj) = 0;

    ///\brief
    /// Get IObject GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the IObject.*/
    ///@return sf::FloatRect
    virtual sf::FloatRect getBounds() = 0;

    objectType getType();

};

#endif // IOBJECT_HPP