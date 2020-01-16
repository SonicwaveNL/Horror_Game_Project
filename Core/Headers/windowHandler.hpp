#ifndef WindowHandler_hpp
#define WindowHandler_hpp

#include <SFML/Graphics.hpp>
#include <iObject.hpp>

///@file
///\brief
/// This class handles the drawing of all objects
class WindowHandler {
  private:
    sf::RenderWindow & window;

  public:
    ///\brief
    /// The WindowHandler constructor.
    ///@param window
    /*An SFML RenderWindow, which this class will draw the game objects on.*/
    WindowHandler(sf::RenderWindow & window) : window(window) {}

    ///\brief
    /// Draws the objects to the window.
    ///\details
    /*This function draws the objects in the 'objects' vector to the SFML
     * RenderWindow.*/
    ///@param objects
    /*The objects in the vector will get drawn to the screen.*/
    void draw(std::vector<IObject *> & objects);
};

#endif // WindowHandler_hpp