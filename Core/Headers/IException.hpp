#ifndef IEXCEPTION_HPP
#define IEXCEPTION_HPP

#include <exception>
#include <string>
class IException : public std::exception {
private:
    const char* error;
public:
    IException(const char * error) : error(error) {}
    virtual const char* what() const throw()
    {
        return error;
    }
};


#endif //IEXCEPTION_HPP