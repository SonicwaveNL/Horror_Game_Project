#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <door.hpp>
#include <iRectangle.hpp>
#include <wall.hpp>

///@file

///\brief
/// Monster class.
///\details
/*A Monster class, this is the monster who follows the player*/
class Monster : public IRectangle {
 private:
  sf::Texture texture;
  sf::Sprite sprite;

 public:
  ///\brief
  /// Monster object constructor.
  ///\details
  /// The Monster constructor parameters are used to create a IRectangle.
  ///@param texture
  /*a SFML sf::Texture, this is the texture for the object*/
  ///@param position
  /*a sf::Vector2f position, this is the position of the object*/
  ///@param objects
  /*a std::vector<IObject> vector array, this is a group of all IObjects
   * within*/
  ///@param color
  /*a SFML sf::Color, this is the color of the texture.*/
  ///@param speed
  /*The walking speed of the monster*/
  Monster(sf::Vector2f position,
          std::vector<std::shared_ptr<IObject>>& objects,
          sf::Color color = sf::Color::Blue,
          float speed = 5, objectType type = objectType::Monster)
      : IRectangle(position, objects, color, speed, type){};

  ///\brief
  /// Draw IRectangle on window
  ///\details
  /*Draw the IRectangle on the sf::RendWindow*/
  ///@param window
  /*sf::RenderWindow*/
  void draw(sf::RenderWindow& window) override;

  ///\brief
  /// Move IObject to direction.
  ///\details
  /*Move IObject to given sf::Vector2f direction.*/
  ///@param direction
  /*sf::Vector2f*/
  void move(sf::Vector2f possition) override;

  ///\brief
  ///Set the color of the object.
  ///@param color
  /*The new color of the object.*/
  void setColor(sf::Color color) override;

  ///\brief
  /// Move Monster to direction, if possible.
  ///\details
  /*Move Monster to given sf::Vector2f direction, if possible.*/
  ///@param direction
  /*sf::Vector2f*/
  void moveIfPossible(sf::Vector2f direction) override;

  ///\brief
  /// Check if Monster intersect.
  ///\details
  /*Check if an Monster intersect with given IObject.*/
  ///@param obj
  /*IObject*/
  ///@return bool
  bool intersect(IObject& obj) override;

  ///\brief
  /// Jump Monster object to given target
  ///\details
  /*Jump Monster object to given sf::Vector2f target.*/
  ///@param obj
  /*sf::Vector2f*/
  void setPosition(sf::Vector2f target) override;

  ///\brief
  /// Monster collision.
  ///\details
  /*Monster collision.*/
  ///@param obj
  /*IObject*/
  void collision(IObject& obj) override;

  ///\brief
  /// Get Monster GlobalBounds.
  ///\details
  /*Get the GlobalBounds of the Monster object.*/
  ///@return sf::FloatRect
  sf::FloatRect getBounds() override;
  ///\brief
  /// Function to get the position.
  sf::Vector2f getPosition() override;
};

#endif  // MONSTER_HPP