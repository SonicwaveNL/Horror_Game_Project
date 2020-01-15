#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include "../../SFML-master/include/SFML/Graphics.hpp"
#include <iostream>
#include <vector>

///@file
///\brief
/// IObject class.
///\details
/*An abstract class to handle/create SMFL objects.*/
class IObject {
 protected:
  sf::Color color;
  sf::Texture texture;
  sf::Vector2f position;
  sf::Vector2f prevPosition;
  sf::RectangleShape base;
  sf::Sprite sprite;
  std::vector<IObject*>& objects;
  float speed = 0;

 public:
  ///\brief
  /// IObject constructor.
  ///\details
  ///@param texture
  /*a SFML sf::Texture, this is the texture for the object*/
  ///@param position
  /*a sf::Vector2f position, this is the position of the object*/
  ///@param objects
  /*a std::vector<IObject*> vector array, this is a group of all IObjects within
   * the game*/
  ///@param color
  /*a SFML sf::Color, this is the color of the texture.*/
  IObject(sf::Texture& texture,
          sf::Vector2f position,
          std::vector<IObject*>& objects,
          sf::Color color = sf::Color::White)
      : texture(texture),
        position(position),
        objects(objects),
        color(color)

  {
    sprite.setTexture(texture);
    sprite.setPosition(position);
  };

  ///\brief
  /// IObject constructor.
  ///\details
  ///@param base
  /*a SFML sf::RectangleShape, this is a rectangle shaped object*/
  ///@param position
  /*a sf::Vector2f position, this is the position of the object*/
  ///@param objects
  /*a std::vector<IObject*> vector array, this is a group of all IObjects within
   * the game*/
  ///@param color
  /*a SFML sf::Color, this is the color of the texture.*/
  IObject(sf::Vector2f position,
          sf::Vector2f size,
          std::vector<IObject*>& objects,
          sf::Color color = sf::Color::White)
      : color(color),
        base(size),
        position(position),
        objects(objects)

  {
    base.setFillColor(color);
    base.setPosition(position);
  };

  ///\brief
  /// Draw IObject on window
  ///\details
  /*Draw the IObject on the sf::RendWindow*/
  ///@param window
  /*sf::RenderWindow*/
  virtual void draw(sf::RenderWindow& window) = 0;

  ///\brief
  /// Move IObject to direction, if possible.
  ///\details
  /*Move IObject to given sf::Vector2f direction, if possible.*/
  ///@param direction
  /*sf::Vector2f*/
  virtual void moveIfPossible(sf::Vector2f direction) = 0;

  ///\brief
  /// Move IObject to direction.
  ///\details
  /*Move IObject to given sf::Vector2f direction.*/
  ///@param direction
  /*sf::Vector2f*/
  void move(sf::Vector2f direction);

  ///\brief
  /// Check if IObjects are colliding.
  ///\details
  /*Check if an IObject is colliding with given IObject.*/
  ///@param obj
  /*IObject*/
  ///@return
  /*bool*/
  virtual bool intersect(IObject& obj) = 0;

  ///\brief
  /// Jump object to given target
  ///\details
  /*Jump an object to the given sf::Vector2f target*/
  ///@param target
  /*sf::Vector2f*/
  virtual void jump(sf::Vector2f target) = 0;

  ///\brief
  /// Interact with given object
  ///\details
  /*Peform interaction with given IObject*/
  ///@param obj
  /*IObject*/
  ///@return
  /*void*/
  virtual void collision(IObject& obj) = 0;

  ///\brief
  /// Get IObject GlobalBounds.
  ///\details
  /*Get the GlobalBounds of the IObject.*/
  ///@return
  /*sf::FloatRect*/
  virtual sf::FloatRect getBounds() = 0;
};

#endif  // IOBJECT_HPP