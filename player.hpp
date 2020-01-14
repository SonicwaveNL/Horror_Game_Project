#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "IObject.hpp"

///@file
///\brief
///Player class.
///\details
/*A Player class, create a playable character*/
class Player : public IObject  {
public:

    ///\brief
    ///Player object constructor.
    ///\details
    ///The Player constructor parameters are used to create a IObject.
    ///@param color
    /*a SFML sf::Color, this is the color of the texture.*/
    ///@param texture
    /*a SFML sf::Texture, this is the texture for the object*/
    ///@param position
    /*a sf::Vector2f position, this is the position of the object*/
    Player( sf::Color & color, sf::Texture & texture, sf::Vector2f position ):
        IObject( color, texture, position )

    {};

    ///\brief
    ///Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow*/
    void draw( sf::RenderWindow & window ) override;

    ///\brief
    ///Move Player object.
    ///\details
    /*Move Player object to given direction.*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    void move( sf::Vector2f direction ) override;

    ///\brief
    ///Check if Player is colliding.
    ///\details
    /*Check if an Player is colliding with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    bool isColliding( IObject & obj ) override;

    ///\brief
    ///Jump Player object to given target
    ///\details
    /*Check if an IObject is colliding with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    void jump( sf::Vector2f target ) override;

    ///\brief
    ///Player interaction.
    ///\details
    /*Perform an Player interaction with given IObject.*/
    ///@param obj
    /*IObject*/
    ///@return
    /*bool*/
    bool interact( IObject & obj ) override;

    ///\brief
    ///Get Player GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the Player object.*/
    ///@return
    /*sf::FloatRect*/
    sf::FloatRect getBounds() override;

};


#endif // PLAYER_HPP