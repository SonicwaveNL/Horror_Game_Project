#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include "../../SFML-master/include/SFML/Graphics.hpp"
#include <functional>

///@file
///\brief
///Action class to assign a action (work) to a event (condition).
///\details
/*The Action class is used to do work in case a condition is met.
There are several constructors to facilitate different base cases.*/
class Action {
  private:
    std::function<bool()> condition;
    std::function<void()> work;

  public:
    ///\brief
    ///Constructor that expects a conditiona and the work.
    ///@param condition
    /*First parameter condition of type std::function<bool()>, 
    store a lambda with return type bool or std::function<bool()> 
    which will be the condition for the work to happen.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()> 
    when the condition is fullfilled the stored "work" will be done.*/
    Action(std::function<bool()> condition, std::function<void()> work);
    ///\brief
    ///Constructor that expects a sf::Keyboard::Key as condition.
    ///@param key
    /*sf::Keyboard::Key the key that has to be pressed for the work to be done.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()> 
    when the condition is fullfilled the stored "work" will be done.*/
    Action(sf::Keyboard::Key key, std::function<void()> work);
    ///\brief
    ///Constructor that expects a sf::Mouse::Button as condition.
    ///@param button
    /*sf::Mouse::Button the mouse button that has to be pressed for the work to be done.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()> 
    when the condition is fullfilled the stored "work" will be done.*/
    Action(sf::Mouse::Button button, std::function<void()> work);
    ///\brief
    ///Constructor without a condition.
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()> 
    when the Action() is used the stored "work" will be done.*/
    Action(std::function<void()> work);
    ///\brief
    ///Used to "call" the class.
    ///\details
    /*When the class is "called" the condition will be checked,
    if the condition is true the "work" will be done.*/
    void operator()();
};

///\brief
///Enum class that contains input types.
enum class inputType {
    keyboard,
    controller
};

///\brief
///Enum class that contains keywords representing actions.
enum class actionKeyword{
    escape,
    select,
    left,
    up,
    right,
    down,
    //Reserved action keywords, usage depends on game state.
    action1,
    action2,
    action3,
    action4
};

#endif