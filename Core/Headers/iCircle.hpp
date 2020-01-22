#ifndef ICIRCLE_hpp
#define ICIRCLE_hpp

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

///@file
///\brief
/// ICircle class
///\details
/*class for creating circle using sfml*/
class ICircle : public IObject {
  protected:
    sf::CircleShape iCirc;

  public:
    ICircle(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Transparent, float speed = 0)
        : IObject(objects, color, speed) {
        iCirc.setPosition(position);
        iCirc.setRadius(18);
    }

    ///\brief
    /// setRadius function
    ///\details
    /*This functions sets the radius of the circle to the given float rad*/
    ///@param rad
    /*float*/
    void setRadius(float rad);
};

#endif // ICIRCLE_hpp