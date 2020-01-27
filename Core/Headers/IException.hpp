#ifndef IEXCEPTION_HPP
#define IEXCEPTION_HPP

#include <exception>
#include <string>

///@file
///\brief
/// loadPlayerError
///\details
/*failure to load player from object list*/
class LoadPlayerError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of player object is present in the object list.";
    }
};

///@file
///\brief
/// loadDoorError
///\details
/*failure to load door from obejct list(s)*/
class LoadDoorError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of door object is present in the object list!\nIs "
               "the map corrupt?";
    }
};

///@file
///\brief
/// corrupFileException
///\details
/*file does not excist*/
class CorruptFileException : public std::exception {
    virtual const char * what() const throw() {
        return "File does not exist or already exists.";
    }
};

///@file///@file
///\brief
/// short description
///\details
/*detailed description*/
class UnknownTypeException : public std::exception {
    virtual const char * what() const throw() {
        return "Type can not be converted to object.";
    }
};

#endif // IEXCEPTION_HPP