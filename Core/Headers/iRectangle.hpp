#ifndef IRECTANGLE_HPP
#define IRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

///@file
///\brief
/// IRectangle class.
///\details
/*Class that creates a rectangle shape using SFML*/
class IRectangle : public IObject {
  protected:
    sf::RectangleShape iRect;
    sf::Texture * texture;
    sf::Sprite sprite;

  public:
    ///\brief
    /// IRectangle constructor.
    IRectangle(sf::Vector2f position,
               std::vector<std::shared_ptr<IObject>> & objects,
               sf::Color color = sf::Color::Transparent, float speed = 0,
               objectType type = objectType::Abstract,
               sf::Vector2f size = sf::Vector2f(16.f, 16.f))
        : IObject(objects, color, speed, type) {
        iRect.setPosition(position);
        iRect.setSize(size);
        setColor(color);
    }

    ///\brief
    /// IRectangle constructor, supports texture.
    IRectangle(sf::Vector2f position,
               std::vector<std::shared_ptr<IObject>> & objects,
               sf::Texture * texture, sf::Color color = sf::Color::Transparent,
               float speed = 0, objectType type = objectType::Abstract,
               sf::Vector2f size = sf::Vector2f(16.f, 16.f))
        : IObject(objects, color, speed, type), texture(texture) {
        iRect.setPosition(position);
        iRect.setSize(size);
        setColor(color);
        sprite.setPosition(position);
        sprite.setTexture(*texture);
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
    sf::Vector2f getPosition() override;

    ///\brief
    /// Sets the color.
    ///@param color
    /*sf::Color*/
    void setColor(sf::Color color) override;

    ///\brief
    /// Draw IObject on window.
    ///\details
    /*Draw the IObject on the sf::RendWindow.*/
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
    /// Set the size of the object.
    ///@param size
    /*A vector2f, containing the size for the IObject.*/
    void setSize(sf::Vector2f size);

    ///\brief
    ///Sets the texture of the IObject.
    ///@param texture
    /*sf::Texture* */
    void setTexture(sf::Texture* texture);
};

#endif