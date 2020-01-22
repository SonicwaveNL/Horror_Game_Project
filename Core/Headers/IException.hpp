#ifndef IEXCEPTION_HPP
#define IEXCEPTION_HPP

#include <exception>
#include <string>

class LoadPlayerError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of player object is present in the object list.";
    }
};

class LoadDoorError : public std::exception {
    virtual const char * what() const throw() {
        return "No instance of door object is present in the object list!\nIs "
               "the map corrupt?";
    }
};

class CorruptFileException : public std::exception {
    virtual const char * what() const throw() {
        return "File does not exist or already exists.";
    }
};

class UnknownTypeException : public std::exception {
    virtual const char * what() const throw() {
        return "Type can not be converted to object.";
    }
};

#endif // IEXCEPTION_HPP