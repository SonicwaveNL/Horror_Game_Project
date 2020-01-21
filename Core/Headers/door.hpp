#ifndef DOOR_HPP
#define DOOR_HPP

#include <SFML/Graphics.hpp>
#include <iRectangle.hpp>

///@file

///\brief
/// Door class.
///\details
/*A Door class, create a door to interact with*/
class Door : public IRectangle {
  private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool open = false;
  public:
    ///\brief
    /// Door object constructor.
    ///\details
    /// The Door constructor parameters are used to create a IObject.
    ///@param texture
    /*a SFML sf::Texture, this is the texture for the object*/
    ///@param position
    /*a sf::Vector2f position, this is the position of the object*/
    ///@param objects
    /*a std::vector<IObject*> vector array, this is a group of all IObjects
     * within*/
    ///@param color
    /*a SFML sf::Color, this is the color of the texture.*/
    Door(sf::Vector2f position, std::vector<std::shared_ptr<IObject>> & objects,
         sf::Color color = sf::Color::White, float speed = 0,
         Type type = Type::Door)
        : IRectangle(position, objects, color, speed, type){};

    void move(sf::Vector2f direction) override;

    void setColor(sf::Color color) override;

    void setOpenState(bool state);
    bool getOpenState();

    ///\brief
    /// Draw IObject on window
    ///\details
    /*Draw the IObject on the sf::RendWindow*/
    ///@param window
    /*sf::RenderWindow*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move Door to direction, if possible.
    ///\details
    /*Move Door to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if Door intersect.
    ///\details
    /*Check if an Door intersect with given iObject.*/
    ///@param obj
    /*IObject*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Jump Door object to given target
    ///\details
    /*Jump Door object to given sf::Vector2f target.*/
    ///@param obj
    /*sf::Vector2f*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Door collision.
    ///\details
    /*Door collision.*/
    ///@param obj
    /*IObject*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get Door GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the Door object.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;
};

#endif // DOOR_HPP