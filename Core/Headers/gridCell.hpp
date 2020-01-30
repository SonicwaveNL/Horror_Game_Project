#ifndef GRIDCELL_HPP
#define GRIDCELL_HPP

#include <string>
#include <iRectangle.hpp>
#include <support.hpp>

///@file
///\brief
/// Class for cells in a grid based on PIXEL16.
///\details
/*This class represents a cell in the grid or a "tile" in the map editor.
It contains a variable in which it's cell type is stored using the objectType
enum class. It also has a shared pointer that can point to the drawable it is representing.*/
class GridCell : public IRectangle {
  private:
    objectType cellType = objectType::Floor;
  public:
    std::shared_ptr<IObject> myDrawable;    
    int64_t value = 0;
    bool visited = false;

    ///\brief
    /// GridCell constructor.
    GridCell(sf::Vector2f position,
             std::vector<std::shared_ptr<IObject>> & objects,
             sf::Color color = sf::Color::Transparent, float speed = 0,
             objectType type = objectType::GridCell)
        : IRectangle(position, objects, color, speed, type) {
        iRect.setSize(sf::Vector2f(PIXEL16, PIXEL16));
    };

    ///\brief
    /// GridCell constructor, supports texture.
    GridCell(sf::Vector2f position,
             std::vector<std::shared_ptr<IObject>> & objects,
             sf::Texture * texture, sf::Color color = sf::Color::Transparent,
             float speed = 0, objectType type = objectType::GridCell)
        : IRectangle(position, objects, texture, color, speed, type) {
        iRect.setSize(sf::Vector2f(PIXEL16, PIXEL16));
    };

    ///\brief
    /// Draw IObject on window.
    ///\details
    /*Draw the IObject on the sf::RendWindow.*/
    ///@param window
    /*sf::RenderWindow&*/
    void draw(sf::RenderWindow & window) override;

    ///\brief
    /// Move IObject to direction.
    ///\details
    /*Move IObject to given sf::Vector2f direction.*/
    ///@param direction
    /*sf::Vector2f*/
    void move(sf::Vector2f direction) override;

    ///\brief
    /// Move IObject to direction, if possible.
    ///\details
    /*Move IObject to given sf::Vector2f direction, if possible.*/
    ///@param direction
    /*sf::Vector2f*/
    void moveIfPossible(sf::Vector2f direction) override;

    ///\brief
    /// Check if IObject intersect.
    ///\details
    /*Check if an IObject intersect with given IObject.*/
    ///@param objgetMyDrawable
    /*IObject&*/
    ///@return bool
    bool intersect(IObject & obj) override;

    ///\brief
    /// Set the position of the GridCell to the given position.
    ///\details
    /*The position to put the GridCell.*/
    ///@param position
    /*sf::Vector2f*/
    void setPosition(sf::Vector2f position) override;

    ///\brief
    /// Function to get the position.
    ///@return sf::Vector2f
    sf::Vector2f getPosition() override;

    ///\brief
    /// IObject collision.
    ///\details
    /*IObject collision.*/
    ///@param obj
    /*IObject&, the object to check collision with.*/
    void collision(IObject & obj) override;

    ///\brief
    /// Get IObject GlobalBounds.
    ///\details
    /*Get the GlobalBounds of the IObject.*/
    ///@return sf::FloatRect
    sf::FloatRect getBounds() override;

    ///\brief
    /// Sets the type of the GridCell.
    ///@param type
    /*objectType, the type the GridCell will take on.*/
    void setCellType(objectType type);

    ///\brief
    /// Sets the type of the GridCell.
    ///@param type
    /*objectType, the type the GridCell will take on.*/
    ///@param texture
    /*sf::Texture*, a pointer to the texture the GridCell should use.*/
    void setCellType(objectType type, sf::Texture * texture);

    ///\brief
    /// Sets the texture of the GridCell.
    ///@param texture
    /*sf::Texture* */
    void setTexture(sf::Texture * texture);

    ///\brief
    /// Gets the type of the GridCell.
    ///@return objectType
    objectType getCellType();

    ///\brief
    /// Function to check if cell is walkable.
    ///@return bool
    bool isWalkable();

	///\brief
	///Function that returns the myDrawable pointer.
	///@return std::shared_ptr<IObject>
	std::shared_ptr<IObject> getMyDrawable();

	///\brief
	///Function to set the myDrawable pointer.
	///@param iPointer
    ///std::shared_ptr<IObject>
	void setMyDrawable(std::shared_ptr<IObject> iPointer);

    ///\brief
    ///= operator.
    GridCell & operator=(const GridCell & rhs) {
        if (this != &rhs) {
            this->setPosition(rhs.iRect.getPosition());
            this->setColor(rhs.color);
            this->prevPosition = rhs.prevPosition;
            this->speed = rhs.speed;
            this->iRect.setSize(rhs.iRect.getSize());
        }
        return *this;
    }
};

#endif