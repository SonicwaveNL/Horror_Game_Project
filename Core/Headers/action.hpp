#ifndef ACTION_HPP
#define ACTION_HPP

#include "support.hpp"
#include <functional>
#include "inputHandler.hpp"
///@file
///\brief
/// Action class to assign a action (work) to a event (condition).
///\details
/*The Action class is used to do work in case a condition is met.
There are several constructors to facilitate different base cases.*/
class Action {
  private:
    std::function<bool()> condition;
    std::function<void()> work;

  public:
    ///\brief
    /// Constructor that expects a conditiona and the work.
    ///@param condition
    /*First parameter condition of type std::function<bool()>,
    store a lambda with return type bool or std::function<bool()>
    which will be the condition for the work to happen.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()>
    when the condition is fullfilled the stored "work" will be done.*/
    Action(std::function<bool()> condition, std::function<void()> work)
      : condition(condition), 
     work(work) {};
    ///\brief
    ///Constructor that expects a actionKeyword and the work
    ///\details
    /*This constructor expects the custom actionKeywords to do the work.*/
    Action(actionKeyword keyword, std::function<void()> work)
      : condition([keyword]() -> bool {InputHandler inputHandler;return inputHandler.checkInput(keyword);}),
      work(work) {};
    ///\brief
    /// Constructor that expects a sf::Keyboard::Key as condition.
    ///@param key
    /*sf::Keyboard::Key the key that has to be pressed for the work to be
     * done.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()>
    when the condition is fullfilled the stored "work" will be done.*/
    Action(sf::Keyboard::Key key, std::function<void()> work)
      : condition([key]() -> bool { return sf::Keyboard::isKeyPressed(key); }),
      work(work) {};
    ///\brief
    /// Constructor that expects a sf::Mouse::Button as condition.
    ///@param button
    /*sf::Mouse::Button the mouse button that has to be pressed for the work to
     * be done.*/
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()>
    when the condition is fullfilled the stored "work" will be done.*/
    Action(sf::Mouse::Button button, std::function<void()> work) 
      : condition([button]() -> bool { return sf::Mouse::isButtonPressed(button); }),
      work(work) {};
    ///\brief
    /// Constructor without a condition.
    ///@param work
    /*Second parameter work of type std::function<void()>,
    store a lambda with void return type or std::function<void()>
    when the Action() is used the stored "work" will be done.*/
    Action(std::function<void()> work)
      : condition([]() -> bool { return true; }), work(work) {};
    ///\brief
    /// Used to "call" the class.
    ///\details
    /*When the class is "called" the condition will be checked,
    if the condition is true the "work" will be done.*/
    void operator()();
};

#endif