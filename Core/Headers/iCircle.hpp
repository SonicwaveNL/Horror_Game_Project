#ifndef ICIRCLE_hpp
#define ICIRCLE_hpp

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

///@file
///\brief
/// ICircle class.
///\details
/*Class for creating a circle using SFML.*/
class ICircle : public IObject {
  protected:
    sf::CircleShape iCirc;

  public:
    ///\brief
    ///Constructor for ICirlce.
    ICircle(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Transparent, float speed = 0)
        : IObject(objects, color, speed) {
        iCirc.setPosition(position);
        iCirc.setRadius(18);
    }

    ///\brief
    ///Sets the radius of the circle shape.
    ///@param rad
    /*float*/
    void setRadius(float rad);
};

#endif // ICIRCLE_hpp