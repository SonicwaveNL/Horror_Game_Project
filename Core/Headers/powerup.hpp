#ifndef POWERUP_hpp
#define POWERUP_hpp

#include <iRectangle.hpp>
#include <iException.hpp>
#include <support.hpp>
#include <unordered_map>
#include <support.hpp>
#include <ctime>
#include <chrono>

///@file
///\brief
/// The powerup object class.
///\details
/*This object gives the user a specific buff or debuff.*/
class Powerup : public IRectangle {
  private:
    std::unordered_map<BuffType, int> oldValues;
    bool isActive = false;
    BuffType buffType;
    time_t expirationTime = time(NULL);
    int amount;

  public:
    ///\brief
    /// Powerup constructor
    Powerup(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Color color = sf::Color::Yellow, float speed = 0,
            objectType type = objectType::Powerup,
            BuffType buffType = BuffType::PlayerSpeed, int amount = 0)
        : IRectangle(position, objects, color, speed, type), buffType(buffType),
          amount(amount) {}

    ///\brief
    /// Powerup constructor, supports texture.
    Powerup(sf::Vector2f position,
            std::vector<std::shared_ptr<IObject>> & objects,
            sf::Texture * texture, sf::Color color = sf::Color::Transparent,
            float speed = 0, objectType type = objectType::Powerup,
            BuffType buffType = BuffType::PlayerSpeed, int amount = 0)
        : IRectangle(position, objects, texture, color, speed, type),
          buffType(buffType), amount(amount) {}

    ///\brief
    /// Move the Powerup, regardless of what object is in the new location.
    ///\details
    /*The Powerup's move isn't implemented, because we don't want it to move for now.*/
    ///@param direction
    /*sf::Vector2f, the direction the Powerup should move in. Passing a 1 will move the door
     * at its default speed, passing a 2 will move it twice as fast etc.*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Only moves the Powerup if the new location is empty.
    ///\details
    /*The Powerup's moveIfPossible does nothing, because we don't want it to
     * move.*/
    ///@param direction
    /*sf::Vector2f, the direction the Powerup should move in. Passing a 1 will move the door
     * at its default speed, passing a 2 will move it twice as fast etc.*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Whether or not the user intersects with its parameter.
    ///@param obj
    /*IObject&, the object to check if the door interacts with it.*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Set the position of the Powerup to the position.
    ///@param position
    /*sf::Vector2f, contains the new position of the object.*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Draw the object to the given window.
    ///@param window
    /*sf::RenderWindow&, the window the object should be drawn to.*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// What the object does when the user collides or interacts with it.
    ///\details
    /*Should only be called by the action1 keyword. This then flips the
     * Powerup.*/
    ///@param obj
    /*IObject&, the object that is colliding with the Powerup.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Returns the outer boundaries of the Powerup object.
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    ///Uses the buff.
    ///\details
    /*Uses the buff with the supplied magnitude that amplifies the buff.*/
    ///@param magnitude
    /*float = 1, how amplified the buff should be.*/
    void buff(float magnitude = 1);

    ///\brief
    ///Checks if the player has the buff and has to be stopped.
    void checkBuff();

    ///\brief
    ///Stops the buff.
    void stopBuff();

    ///\brief
    ///Gets the amount the player has of this buff.
    ///@return int
    int getAmount();

    ///\brief
    ///Sets the amount the player has of this buff.
    ///@param newAmount
    /*int, sets how many uses the player has of this buff.*/
    void setAmount(int newAmount);
};

#endif // POWERUP_hpp