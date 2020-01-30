#ifndef IEXCEPTION_HPP
#define IEXCEPTION_HPP

#include <exception>
#include <string>

///@file
///\brief
/// loadPlayerError
///\details
/*Failure to load player from object list.*/
class LoadPlayerError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of player object is present in the object list.";
    }
};

///\brief
/// loadDoorError
///\details
/*Failure to load door from object list.*/
class LoadDoorError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of door object is present in the object list!\nIs "
               "the map corrupt?";
    }
};

///\brief
/// corruptFileException
///\details
/*File does not exist.*/
class CorruptFileException : public std::exception {
    virtual const char * what() const throw() {
        return "File does not exist or already exists.";
    }
};

///\brief
/// unknownTypeException    
///\details
/*Unknown type.*/
class UnknownTypeException : public std::exception {
  private:
    const char * msg;

  public:
    UnknownTypeException(const char * msg = "ndef") : msg(msg){};
    virtual const char * what() const throw() { return msg; }
};

#endif // IEXCEPTION_HPP