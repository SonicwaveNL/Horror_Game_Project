#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <SFML/Graphics.hpp>

///@file
///\brief
///IObject class.
///\details
/*An abstract class to handle/create SMFL objects.*/
class IObject{
protected:
    sf::Color       color = sf::Color::Black;
    sf::Texture     texture;
    sf::Vector2f    position;
    sf::Sprite      sprite;
    float           speed = 0;

public:

    ///\brief
    ///IObject constructor.
    ///\details
    ///@param color
    /*a SFML sf::Color, this is the color of the texture.*/
    ///@param texture
    /*a SFML sf::Texture, this is the texture for the object*/
    ///@param position
    /*a sf::Vector2f position, this is the position of the object*/
    IObject( sf::Color & color, sf::Texture & texture, sf::Vector2f position ):
        color( color ),
        texture( texture ),
        position( position )

    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
    };

    ///\brief
    ///Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow*/
    virtual void draw( sf::RenderWindow & window ) = 0;

    ///\brief
    ///Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    virtual void move( sf::Vector2f direction ) = 0;

    ///\brief
    ///Check if IObjects are colliding.
    ///\details
    /*Check if an IObject is colliding with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    virtual bool isColliding( IObject & obj ) = 0;
 
    ///\brief
    ///Jump object to given target
    ///\details
    /*Jump an object to the given sf::Vector2f target*/
    ///@param target
    /*sf::Vector2f*/
    virtual void jump( sf::Vector2f target ) = 0;

    ///\brief
    ///Interact with given object
    ///\details
    /*Peform interaction with given IObject*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    virtual bool interact( IObject & obj ) = 0;

    ///\brief
    ///Get IObject GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the IObject.*/
    ///@return
    /*sf::FloatRect*/
    virtual sf::FloatRect getBounds() = 0;

};


#endif // IOBJECT_HPP