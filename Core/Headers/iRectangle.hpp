#ifndef IRECTANGLE_HPP
#define IRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

class IRectangle : public IObject {
  protected:
    sf::RectangleShape iRect;

  public:
    IRectangle(sf::Vector2f position,
               std::vector<std::shared_ptr<IObject>> & objects,
               sf::Color color = sf::Color::Transparent, 
               float speed = 0,
               objectType type = objectType::Abstract,
               sf::Vector2f size = sf::Vector2f(20.f, 20.f))
        : IObject(objects, color, speed, type) {
        iRect.setPosition(position);
        iRect.setSize(size);
        setColor(color);
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

    void setColor(sf::Color color) override;

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

    ///\brief
    ///Set the size of the object.
    ///@param size
    /*A vector2f containing the new size of the object.s*/
    void setSize(sf::Vector2f size);
    
    ///\brief
    ///Function to get the position.
    virtual sf::Vector2f getPosition() = 0;

};

#endif